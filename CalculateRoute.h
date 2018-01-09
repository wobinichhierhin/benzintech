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

    string linkName;

    Station** allStation;
    DriveRoute* route;

    int* listStation;
    time_t* listOfTime;
    int lengthListStation;

    int* orderList;
    double* toRefuel;

    void calculate(int von, int to);

    double distanceVonAToB(int a, int b);
    double distance(Station* a, Station* b);

    void save();

  public:

    CalculateRoute(Station** allStation, DriveRoute* route, string linkName);
    ~CalculateRoute();

    double* getToReful();


  };

  #endif
