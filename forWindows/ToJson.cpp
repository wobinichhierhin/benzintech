#include <iostream>
#include <stdlib.h>
	#include <sstream>
#include "ToJson.h"

using namespace std;


ToJson::ToJson()
{

}

ToJson::~ToJson()
{

}


string ToJson::toJsonFromPrice(string* t, int* p)
{

    string erg="";
    erg="{\n";
    erg+="\"Laenge\": 30,\n";

    erg+="\"Time\": [";
    erg+="\""+t[0]+"\"";
    for(int x=1;x<30;x++)
    {
      erg+=", \""+t[x]+"\"";
    }
    erg+="],\n";

    erg+="\"Preis\": [";
	ostringstream stream;
	stream<<p[0];
    erg+=stream.str();
    for(int x=1;x<30;x++)
    {
		ostringstream stream2;
		stream2<<p[x];
      erg+=", "+stream2.str();
    }
    erg+="]\n";

      erg+="}";
    return erg;
}

string ToJson::toJsonFromRoute(string* t, int* id, int* p, double* l, int length)
{
  string erg="";
  erg="{\n";
ostringstream stream3;
  stream3<<length;
  erg+="\"Laenge\": " +stream3.str()+",\n";

  erg+="\"Time\": [";
  erg+="\""+t[0]+"\"";
  for(int x=1;x<length;x++)
  {
    erg+=", \""+t[x]+"\"";
  }
  erg+="],\n";


  erg+="\"ID\": [";
	ostringstream stream4;
  stream4<<id[0];
  erg+=stream4.str();
  for(int x=1;x<length;x++)
  {
		ostringstream stream5;
	  stream5<<id[x];
    erg+=", "+stream5.str()+"";
  }
  erg+="],\n";



  erg+="\"Preis\": [";
ostringstream stream;
  stream<<p[0];
  erg+=stream.str();
  for(int x=1;x<length;x++)
  {
	ostringstream stream2;
	  stream2<<p[x];
    erg+=", "+stream2.str();
  }
  erg+="],\n";


  erg+="\"Litter\": [";
	ostringstream stream6;
  stream6<<l[0];
  erg+=stream6.str();
  for(int x=1;x<length;x++)
  {
	ostringstream stream7;
	if(x == length-1)stream7<<0.0;
	 else stream7<<l[x];
    erg+=", "+stream7.str();
  }
  erg+="]\n";


  erg+="}";
  return erg;
}
