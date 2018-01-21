import csv, sqlite3

con = sqlite3.connect("benzin.db")
cur = con.cursor()
cur.execute("CREATE TABLE Tankstellen (ID, Name, Betreiber, Strasse, Hausnummer, PLZ, Ort, Lat, Lon);") # use your column names here

with open('./data/Tankstellen.csv','rt') as fin: # `with` statement available in 2.5+
    # csv.DictReader uses first line in file for column headings by default
    dr = csv.DictReader(fin, delimiter=";") # comma is default delimiter
    to_db = [(i['ID'], i['Name'], i["Betreiber"], i["Strasse"], i["Hausnummer"],
              i["PLZ"], i["Ort"], i["Lat"], i["Lon"]) for i in dr]

cur.executemany("INSERT INTO Tankstellen (ID, Name, Betreiber, Strasse, Hausnummer, PLZ, Ort, Lat, Lon) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);", to_db)
con.commit()
con.close()