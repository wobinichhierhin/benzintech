#include <stdlib.h>
#include <iostream>

#ifndef DriveRoute_h
#define DriveRoute_h

using namespace std;

class DriveRoute
{
  private:

  public:

    DriveRoute(string data);// die Route.csv als ein String
    ~DriveRoute();

    int* listOfStation;// liste der Station in geordneter Form, wie sie in der Datei vor kamen
    time_t* arriavelAtTime; // liste der Zeiten zu den Station
    int length;// lenge der Arrays
    string* oneLine; // Array der Route.csv bestehend aus den einzelnen Zeilen

  };

  #endif
