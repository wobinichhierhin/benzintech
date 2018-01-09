#include "Station.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;


Station::Station(string data)
{
  firstPreisAtTime = 1;

  string h[9];
  int hx=0;
  for(int x=0;x<data.length();x++)
  {
    if(data[x]!=';')h[hx]+=data[x];
    else hx++;
  }

   id = atoi( h[0].c_str() );
   name = h[1];
   marke = h[2];
   street = h[3];
   housenumber = atoi( h[4].c_str() );
   plz = atoi( h[5].c_str() );
   ort = h[6];
   longitude = strtold(h[7].c_str(),NULL);//achtung rundungsfehler
   latitude = strtold(h[8].c_str(),NULL);//achtung rundungsfehler

}

Station::~Station()
{

}

int Station::getPreisatTime(int time)
{
  if(firstPreisAtTime)
  {
    preis = new int[30];
    date = new int[30];
    string link = "Aufgabenbeschreibung/";
    int x2 = id;
    string zahl="";
    do
    {
      zahl=(char)((x2%10)+48)+zahl;
      x2/=10;
    }while(x2);
    link+=zahl+".csv";

    string read="";
    int counter=0;
    fstream f;
    f.open(link.c_str(), ios::in);
    if(f.good())
    {
      while (!f.eof())
      {
       string dataLine = "";
       getline(f, dataLine);
       if(dataLine != "")
       {
         string preish="";
         string dateh="";
         bool h=1;
         for(int x=0; x<dataLine.length();x++)
         {
           if(dataLine[x]!=';')
           {
             if(h)preish += dataLine[x];
             else dateh += dataLine[x];
           }
           else h=0;
         }
         preis[counter] =  atoi( preish.c_str() );
         date[counter] = 0;
         counter++;
       }

      }
    }
    f.close();



    firstPreisAtTime = 0;
  }

  return 1339;
}
