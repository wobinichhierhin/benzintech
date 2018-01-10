#include "GasPrice.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;


GasPrice::GasPrice( int id)
{
  this->id = id;
  length=0;
  data="";

  string link="Eingabedaten/Benzinpreise/";
  string zahl="";
  int x2=id;
  do
  {
    zahl=(char)((x2%10)+48)+zahl;
    x2/=10;
  }while(x2);
  link+=zahl+".csv";

  fstream datei;
  datei.open(link.c_str(), ios::in);
  if(datei.good())
  {
    while (!datei.eof())
    {
      string dataLine;
      getline(datei, dataLine);
      if(dataLine != "")
      {
        data += dataLine +"\n";
        length++;
      }
    }
  }

  price = new int[length];
  zeit = new time_t[length];
  day = new int[12*31];
      for(int x=0; x<(12*31);x++)day[x]=0;

  int x=0;
  int counter=0;
  string line="";
  while(data[x])
  {
    if(data[x] != '\n')line +=data[x];
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

  datei.close();
}

GasPrice::~GasPrice()
{
  delete[] zeit;
  delete[] price;
  delete[] day;
}

int GasPrice::getPreis(time_t t)
{
  if(t < zeit[0] || t > zeit[length-1])
  {
    struct tm *tm = localtime(&t);
    int h = (tm->tm_mon*31)+tm->tm_wday;
    return day[h];
  }

    for(int x=0; x<length; x++)
    {
      if(zeit[x] > t)return price[x-1];
    }
    return price[length-1];
}


int* GasPrice::getAllPreis()
{
  return price;
}
time_t* GasPrice::getAllTime()
{
  return zeit;
}
int GasPrice::getLength()
{
  return length;
}
