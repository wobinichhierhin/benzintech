#include "Station.h"
#include <iostream>
#include <stdlib.h>
#include "GasPrice.h"

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
  delete preis;
}

int Station::getPreisatTime(time_t time)
{
  if(firstPreisAtTime)
  {
    preis = new GasPrice(id);
    firstPreisAtTime = 0;
  }

  return preis->getPreis(time);
}
