#include <stdlib.h>
#include <iostream>

#ifndef DriveRoute_h
#define DriveRoute_h

using namespace std;

class DriveRoute
{
  private:

  public:

    DriveRoute(string data);
    ~DriveRoute();

    int* listOfStation;
    time_t* arriavelAtTime; 
    int length;
    string* oneLine;

  };

  #endif
