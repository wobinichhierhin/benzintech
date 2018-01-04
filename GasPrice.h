#include <stdlib.h>
#include <iostream>

#ifndef GasPrice_h
#define GasPrice_h

using namespace std;

class GasPrice
{
  private:
    int id;
    int length;
    int* price;
    time_t* zeit;
    int* day;

    int* dayFuture;

  public:

    GasPrice(string data, int id);
    ~GasPrice();


  };

  #endif
