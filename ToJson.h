#include <stdlib.h>
#include <iostream>

#ifndef ToJson_h
#define ToJson_h

using namespace std;

class ToJson
{
  private:

  public:

    ToJson();
    ~ToJson();

    string toJsonFromPrice(string* t, int* p);
    string toJsonFromRoute(string* t, int* id, int* p, double* l, int length);


  };

  #endif
