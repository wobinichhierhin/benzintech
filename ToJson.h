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

    //formatiert Preisdaten zu einer Json String
    string toJsonFromPrice(string* t, int* p);

    // formatiert Routendaten zu einer Json String
    string toJsonFromRoute(string* t, int* id, int* p, double* l, int length);


  };

  #endif
