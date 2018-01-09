#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "GasPrice.h"


using namespace std;

void calc(int start, int end);

int main(int argc, char* argv[]) {

  int max = 15226;
  //max=1;

  GasPrice* a = new GasPrice(100);


  struct tm tm;
  strptime("2017-09-21 18:05:06+02;", "%Y-%m-%d %H:%M:%S", &tm);
  cout<<a->getPriceAtTime(mktime(&tm))<<endl;


  struct tm t;
  strptime("2017-09-22 01:05:06+02", "%Y-%m-%d %H:%M:%S", &t);


  cout<<a->getPriceAtTime(mktime(&t))<<endl;


return 0;
}
