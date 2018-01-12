#include <stdlib.h>
#include <iostream>
#include "GasPrice.h"

#ifndef Station_h
#define Station_h

using namespace std;

class Station
{
  private:

  public:

    Station(string data);// data = eine zeile aus der Tankstellen.csv
    ~Station();

    int id;// id der tankstelle
    string name;
    string marke;
    string street;
    int housenumber;
    int plz;
    string ort;
    double latitude;    //achtung fehler durch Rundung
    double longitude;   //achtung fehler durch Rundung

    bool firstPreisAtTime; // variable für die einmalige initialisierung des preis
    GasPrice* preis;

    /*
    ruft von GasPrice getPreis(time_t t) auf und gibt den Preis zu einem Zeitpunk X zurück
    wird die funktion zum ersten mal aufgerufen, dann wird der preis initialiesiert.
    Danach wird einfach nur noch die Funktion getPreis(time_t t) aufgerufen
    */
    int getPreisatTime(time_t time);




  };

  #endif
