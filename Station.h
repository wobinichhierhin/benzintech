#include <stdlib.h>
#include <iostream>

#ifndef Station_h
#define Station_h

using namespace std;

class Station
{
  private:

  public:

    Station(string data);
    ~Station();

    int id;
    string name;
    string marke;
    string street;
    int housenumber;
    int plz;
    string ort;
    double latitude;    //achtung fehler durch Rundung
    double longitude;   //achtung fehler durch Rundung

    int getPreisatTime(int time);




  };

  #endif
