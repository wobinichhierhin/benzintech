#include <stdlib.h>
#include <iostream>

#ifndef GasPrice_h
#define GasPrice_h

using namespace std;

class GasPrice
{
  private:
    int id;//id der Tankstelle
    string data; // Die .csv Datei als ein String
    int length;// laenge der Array / anzahl der Zeilen der .csv Datei
    int* price;// Price einer Zeile
    time_t* zeit;// Dazum einer Zeile

    int* day; // Array für die Mittelung 12*31 groß. 



  public:

    GasPrice( int id);//id der Tankstelle 1 -15226
    ~GasPrice();

    /*
    gibt den Preis einer Tankstelle zum Zeitpunkt x zurück.
    Liegt der Preis innerhalb der gegebene Datensatzes, dann wird der Nächstgütige Preis gewält.
    Liegt der Peis auserhalb des gegebenen Datensatzes, dann wird der gemittelte Preis für den Tag zurückgegeben
    */
    int getPreis(time_t t);


  };

  #endif
