from flask import Flask, render_template, url_for, jsonify, request, session, g
from wtforms import Form, StringField, SelectField, SubmitField, HiddenField
from wtforms.fields.html5 import DateField
from wtforms.ext.sqlalchemy.fields import QuerySelectField
import datetime
import os
from wtforms.validators import ValidationError
from babel import Locale
from flask_babel import Babel, gettext, ngettext, refresh
from sqlite3 import dbapi2 as sqlite
from geopy import distance
import matplotlib.pyplot as plt
from uuid import uuid4
import socket
import json
import matplotlib.dates as mdates


app = Flask(__name__)
LOCALE_LANG = 'de_DE'

from sqlalchemy import Column, ForeignKey, Integer, String, create_engine, Float, DateTime, or_
from sqlalchemy.orm import sessionmaker
from sqlalchemy.ext.declarative import declarative_base
Base = declarative_base()

class Routen(Base):
    __tablename__ = 'Routen'
    RoutenID = Column(Integer, primary_key=True)
    RoutenName = Column(String(250), nullable=False)

class Routendaten(Base):
    __tablename__ = 'Routendaten'
    Zeitpunkt = Column(DateTime)
    TankstellenID = Column(Integer)
    Preis = Column(Integer)
    Tankmenge = Column(Float)
    RoutenID = Column(Integer)
    RoutendatenID = Column(Integer, primary_key=True)

class Tankstellen(Base):
    __tablename__ = 'Tankstellen'
    ID = Column(Integer, primary_key=True)
    Name = Column(String)
    Betreiber = Column(String)
    Strasse = Column(String)
    Hausnummer = Column(String)
    PLZ = Column(Integer)
    Ort = Column(String)
    Lat = Column(Float)
    Lon = Column(Float)

class Tankstellendaten(Base):
    __tablename__ = 'Tankstellendaten'
    DatenID = Column(Integer, primary_key=True)
    TankstellenID = Column(Integer)
    Preis = Column(Float)
    Zeitpunkt = Column(DateTime)


def get_hour_price(weekdict, day, hour):
    if day not in weekdict:
        if day == 0:
            newday = 6
        else:
            newday = day - 1
        return get_hour_price(weekdict, newday, hour)
    else:
        if hour not in weekdict[day]:
            if hour == 0:
                newhour = 23
            else:
                newhour = hour - 1
            return get_hour_price(weekdict, day, newhour)
        else:
            return weekdict[day][hour]



engine = create_engine('sqlite:///./data/benzin.db')
Base.metadata.bind = engine

DBSession = sessionmaker(bind=engine)
app.config['BABEL_DEFAULT_LOCALE'] = LOCALE_LANG
app.config['BABEL_DEFAULT_TIMEZONE'] = 'CET'
babel = Babel(app)

class TestForm(Form):
    today = datetime.datetime.date(datetime.datetime.now())
    in30 = today+datetime.timedelta(days=30)
    date = DateField(default=today)
    start = datetime.datetime.strptime('2015-01-01 00:00:00', '%Y-%m-%d %H:%M:%S')
    starttank = StringField("start")
    zieltank = StringField("ende")
    submit_route = SubmitField()
    submit_price = SubmitField()

def RoutenAuswahlFactory():
    db_session = DBSession()
    data = db_session.query(Routen).order_by(Routen.RoutenName.asc())
    db_session.close()
    return data

def TankstellenAuswahlFactory():
    db_session = DBSession()
    data = db_session.query(Tankstellen).order_by(Tankstellen.ID.asc())
    db_session.close()
    return data

class RouteForm(Form):
    today = datetime.datetime.date(datetime.datetime.now())
    in30 = today+datetime.timedelta(days=30)
    date = DateField(default=today)
    start = datetime.datetime.strptime('2015-01-01 00:00:00', '%Y-%m-%d %H:%M:%S')
    submit_route = SubmitField()
    submit_price = SubmitField()
    routenauswahl = QuerySelectField('Route', query_factory=RoutenAuswahlFactory,
                           get_pk=lambda a: a.RoutenID, get_label=lambda a: a.RoutenName)
    zieltank = StringField("ende")
    tankid = HiddenField()
    #tankauswahl = QuerySelectField('Tankstelle', query_factory=TankstellenAuswahlFactory, get_pk=lambda a: a.ID, get_label=lambda a: a.Name)

#if word.lower() in (s.lower() for s in <listenname>)
#08.09.2017

@app.route("/searchtank", methods=["GET"])
def searchtank():
    search = request.args.get("word")
    db_session = DBSession()
    name_list = db_session.query(Tankstellen).filter(or_(Tankstellen.Name.like("%" + search + "%"),
                                                         Tankstellen.Ort.like("%" + search + "%"),
                                                         Tankstellen.Strasse.like("%" + search + "%"))).all()
    matching = []
    for entry in name_list:
        matching.append([entry.ID, entry.Name + ' ' + str(entry.Strasse) + ' ' + str(entry.Hausnummer) + ', ' +
                         str(entry.PLZ) + ' ' + str(entry.Ort)])
    db_session.close()
    return jsonify(matching=matching)

@app.route("/karte")
def karte():
    global LOCALE_LANG
    if not 'locale' in session:
        session['locale'] = LOCALE_LANG
    form=TestForm()
    today = datetime.datetime.date(datetime.datetime.now())
    return render_template("karte.html", form=form, today=form.start, in30=form.in30, locale=session['locale'])

@app.route("/", methods=['GET', 'POST'])
def route():
    global LOCALE_LANG
    if not 'locale' in session:
        session['locale'] = LOCALE_LANG
    form = RouteForm()
    print(request.form)
    dataarray = {}
    if request.method == 'POST' and "submit_route" in request.form:
        db_session = DBSession()
        routenname_data = db_session.query(Routen).filter_by(RoutenID=request.form["routenauswahl"]).first()
        print(routenname_data)
        dataarray["routenname"] = routenname_data.RoutenName
        print(dataarray["routenname"])
        print("Hole Routendaten")
        data = db_session.query(Routendaten).filter_by(RoutenID=request.form["routenauswahl"]).order_by(Routendaten.Zeitpunkt.asc()).all()
        print("Routendaten geladen")
        stoplist = []
        plotlist_x = []
        plotlist_y = []
        print("Setting Plot")
        plt.plot(plotlist_x, plotlist_y)
        print("Clearing Plot")
        plt.clf()
        print("Clearing Axes")
        plt.cla()

        distance.EARTH_RADIUS = 6378.388
        print("Berechne Daten")
        for data_i in range(len(data)):
            tankstellen_daten = db_session.query(Tankstellen).filter_by(ID=data[data_i].TankstellenID).first()
            tankstellen_daten_prev = db_session.query(Tankstellen).filter_by(ID=data[data_i-1].TankstellenID).first()
            stoplist.append([tankstellen_daten.ID, tankstellen_daten.Name, data[data_i].Zeitpunkt,
                             data[data_i].Tankmenge, data[data_i].Preis])
            dist = distance.great_circle((tankstellen_daten_prev.Lat, tankstellen_daten_prev.Lon),
                                         (tankstellen_daten.Lat, tankstellen_daten.Lon))
            benzinverbrauch = float(dist.kilometers)*float(5.6/100)
            if len(plotlist_y) == 0:
                plotlist_x.append(data[data_i].Zeitpunkt)
                plotlist_y.append(data[data_i].Tankmenge)
                print("Getankt:" + str(data[data_i].Tankmenge))
                print("Tankinhalt:" + str(data[data_i].Tankmenge))
            else:
                plotlist_x.append(data[data_i].Zeitpunkt)
                plotlist_y.append(plotlist_y[-1]-benzinverbrauch)
                print("Verbraucht:" + str(benzinverbrauch))
                plotlist_x.append(data[data_i].Zeitpunkt)
                plotlist_y.append(plotlist_y[-1]+data[data_i].Tankmenge)
                print("Getankt:" + str(data[data_i].Tankmenge))
                print("Tankinhalt:" + str(plotlist_y[-1]))
        print("Setze Filename")
        filename = uuid4().hex
        print(plotlist_x[0])
        print(plotlist_x[-1])
        ax = plt.axes()
        days = mdates.DayLocator()
        hours = mdates.HourLocator()
        ax.xaxis.set_major_locator(days)
        ax.xaxis.set_minor_locator(hours)
        plt.plot(plotlist_x, plotlist_y)
        plt.savefig('./static/images/' + filename + '.png')
        dataarray['imagename'] = filename
        dataarray['stoplist'] = stoplist
        return render_template("route.html", form=form, today=form.start, in30=form.in30, locale=session['locale'],
                               dataarray=dataarray)
    elif request.method == 'POST' and "submit_price" in request.form:
        print(request.form)
        db_session = DBSession()
        tankstelle = db_session.query(Tankstellen).filter_by(ID=request.form["tankid"]).first()
        tankstellen_daten = db_session.query(Tankstellendaten).filter_by(TankstellenID=request.form["tankid"]).all()
        week_dict = {}
        #: TODO: Prediction -> Monats und Wochentagsbasiert
        #for entry in tankstellen_daten:
         #   week_dict[str(entry.Zeitpunkt.weekday())] = {}
          #  week_dict[str(entry.Zeitpunkt.weekday())][str(entry.Zeitpunkt.hour)] = entry.Preis
        #print(week_dict)

        #for i in range(7):
            

        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect(('127.0.0.1', 8080))
            s.sendall(str("price " + str(request.form["tankid"]) + ";" + str(request.form["date"]) + " 00:00:00+00").encode())
            data = s.recv(1024)
        data_json = json.loads(data.decode("ascii"))
        data_x = data_json["Time"]
        data_y = data_json["Preis"]
        filename = uuid4().hex
        plt.clf()
        plt.cla()

        ax = plt.axes()
        month = mdates.MonthLocator()
        days = mdates.DayLocator()
        ax.xaxis.set_major_locator(month)
        ax.xaxis.set_minor_locator(days)
        plt.plot(data_x, data_y)
        plt.savefig('./static/images/' + filename + '.png')
        dataarray['imagename'] = filename

    return render_template("route.html", form=form, today=form.start, in30=form.in30, locale=session['locale'], dataarray=dataarray)

@app.route("/change_locale")
def change_locale():
    with app.app_context():
        if request.args.get('locale') == "de":
            session['locale'] = "de_DE"
            g.locale = "de_DE"
        elif request.args.get('locale') == "en":
            session['locale'] = "en_US"
            g.locale = "en_US"
        print(session['locale'])
        print(g.locale)
        refresh()
        return jsonify(success=True)

@babel.localeselector
def get_locale():
    print(session['locale'])
    try:
        print(g.locale)
        return g.locale
    except:
        return "de_DE"

if __name__ == '__main__':
    app.secret_key = os.urandom(24)

    app.run(host="0.0.0.0", port=80)


