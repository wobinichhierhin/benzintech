from flask import Flask, render_template
from wtforms import Form
from wtforms.fields.html5 import DateField
import datetime
import os

app = Flask(__name__)

class TestForm(Form):
    today = datetime.datetime.date(datetime.datetime.now())
    in30 = today+datetime.timedelta(days=30)
    date = DateField(default=today)
    start = datetime.datetime.strptime('2015-01-01 00:00:00+02', '%Y-%m-%d %H:%M:%S+%z')

@app.route("/")
def hello():
    form=TestForm()
    return render_template("test.html", form=form, today=form.today, in30=form.in30)

if __name__ == '__main__':
    app.secret_key = os.urandom(24)
    app.run()
