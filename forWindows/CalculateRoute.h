#include <stdlib.h>
#include <iostream>
#include "Station.h"
#include "DriveRoute.h"

#ifndef CalculateRoute_h
#define CalculateRoute_h

using namespace std;

class CalculateRoute
{
  private:

    string linkName;// name der Route.csv Datei

    Station** allStation;//alle 15226 Stationen in einem Array
    DriveRoute* route; // die zu berechnende Route

    int* listStation;   // liste der Stationen der Route
    time_t* listOfTime;// liste der Zeiten der Route
    int lengthListStation;// lenge der Arrays

    int* orderList; //Hilfsarray für die Berechnung der zu tenkende Litter
    double* toRefuel; // Array wie viel gedankt werden soll, in reienhvolge wie listStation

    int* price;// Hilfsarray Price der Tankstops
    string* timeStation;// Hilfsarray der Zeiten der Stops als string form

    void calculate(int von, int to);//Rekursiver Teil unseres Algorithmus zu Berechnung der zu tankenden Litter

    double distanceVonAToB(int a, int b); // berechnet die Entfernung 2er Tankstellen, in dem auch die ZwischenTankstellen mit einbezogen werden
                                          //z.b. von A nach C = A nach B + B nach C
    double distance(Station* a, Station* b);// berechnet via Großkreisformel die entfernung 2er Tankstellen

    void save();//speichert die Route in /Ausgabedaten/Tankstrategien/

  public:
                    // liste aller Stationen 1-15226    // Route    // Namen der Route.csv
    CalculateRoute(Station** allStation, DriveRoute* route, string linkName);
    ~CalculateRoute();

    double* getToReful();// gibt zu tanken Array zurück
    string* getTime(); // gibt die Zeiten der Route zurück
    int* getListStation();// gibt das Array der Station zurück
    int* getPice();// gibt ein Arry von den Preisen die zu tanken sind zurück
    int getLength();// laenge der Arrays


  };

  #endif
