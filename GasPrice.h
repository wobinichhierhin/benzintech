#include <stdlib.h>
#include <iostream>

#ifndef GasPrice_h
#define GasPrice_h

using namespace std;

class GasPrice
{
  private:
    int id;
    string data;
    int length;
    int* price;
    time_t* zeit;

    int* day;



  public:

    GasPrice( int id);
    ~GasPrice();

    int getPreis(time_t t);
    int*getAllPreis();
    time_t* getAllTime();
    int getLength();


  };

  #endif
