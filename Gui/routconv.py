import csv, sqlite3
from os import listdir
from os.path import isfile, join

con = sqlite3.connect("./data/benzin.db")
cur = con.cursor()
onlyfiles = [f for f in listdir("./data/routes")]
print(onlyfiles)
for entry in onlyfiles:
    cur.execute("SELECT RoutenName FROM Routen WHERE RoutenName = ?", (entry[:-4],))
    data=cur.fetchall()
    print(data)
    print(entry)
    if len(data)==0:
        cur.execute("INSERT INTO Routen (RoutenName) VALUES (?)", (entry[:-4],))
    else:
        break
    con.commit()
    cur.execute("SELECT * FROM Routen WHERE RoutenName = ?", (entry[:-4],))
    data=cur.fetchall()
    insid = data[0][0]
    with open("./data/routes/" + entry, 'rt') as csvfile:
        dr = csv.DictReader(csvfile, delimiter=";", fieldnames=['Zeitpunkt', 'Ort', 'Preis', 'Menge'])
        to_db = [(i['Zeitpunkt'], i['Ort'], i['Preis'], i['Menge'], insid) for i in dr]
    cur.executemany("INSERT INTO Routendaten (Zeitpunkt, TankstellenID, Preis, Tankmenge, RoutenID) VALUES (?, ?, ?, ?, ?);", to_db)
    con.commit()
con.close()
