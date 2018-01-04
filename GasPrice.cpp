#include "GasPrice.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;


GasPrice::GasPrice(string data, int id)
{
  this->id = id;
  length = 0;
  int x=0;
  while(data[x])
  {
    if(data[x]=='\n')length++;
    x++;
  }
  price = new int[length];
  zeit = new time_t[length];
  day = new int[12*31];
      for(int x=0; x<(12*31);x++)day[x]=0;

  int counter=0;
  x=0;
  string line="";

  while(data[x])
  {
    if(data[x] != '\n')line += data[x];
    else
    {
      line += ';';
      string linePrice="";
      string lineTime="";
      int z=0;
      while(line[z]!=';')
      {
        lineTime += line[z];
        z++;
      }
      z++;
      while(line[z]!=';')
      {
        linePrice += line[z];
        z++;
      }

      price[counter] = atoi(linePrice.c_str());
      struct tm tm;
      strptime(lineTime.c_str(), "%Y-%m-%d %H:%M:%S", &tm);
      zeit[counter] = mktime(&tm);

      string m = "";
      m += lineTime[5];
      m += lineTime[6];
      string d = "";
      d += lineTime[8];
      d += lineTime[9];
      int mont = atoi(m.c_str())-1;
      int dayH = atoi(d.c_str())-1;

      day[(mont*31)+dayH] += atoi(linePrice.c_str());
      day[(mont*31)+dayH] /= 2;

      line = "";
      counter++;
    }
    x++;
  }

  string zahl="";
  int x2=id;
  do
  {
    zahl=(char)((x2%10)+48)+zahl;
    x2/=10;
  }while(x2);
  string link = "Ausgabedaten/"+zahl+".csv";

  fstream dat;
  dat.open(link.c_str(), ios::out);
    dayFuture = new int[30];
    int date = ((9*31)+21)-30;
    int end = 30;
    for(int y=0; y<end; y++)
    {
      if(day[date + y])
      {
        dat<< day[date + y]<<";\n";
      }
      else end++;
    }
  dat.close();

}

GasPrice::~GasPrice()
{
  delete[] price;
  delete[] day;
  delete[] zeit;
  delete[] dayFuture;

}
