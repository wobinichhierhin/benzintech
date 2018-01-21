import csv, sqlite3
from os import listdir
from os.path import isfile, join

con = sqlite3.connect("./data/benzin.db")
cur = con.cursor()
onlyfiles = [f for f in listdir("./data/tankstellen")]
print(onlyfiles)
for entry in onlyfiles:
    cur.execute("SELECT * FROM Tankstellen WHERE ID = ?", (entry[:-4],))
    data=cur.fetchall()
    insid = data[0][0]
    with open("./data/tankstellen/" + entry, 'rt') as csvfile:
        dr = csv.DictReader(csvfile, delimiter=";", fieldnames=['Zeitpunkt', 'Preis'])
        to_db = [(i['Zeitpunkt'], float(float(i['Preis'])/float(1000)), entry[:-4]) for i in dr]
    cur.executemany("INSERT INTO Tankstellendaten (Zeitpunkt, Preis, TankstellenID) VALUES (?, ?, ?);", to_db)
    con.commit()
con.close()
