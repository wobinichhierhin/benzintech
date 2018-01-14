#include <iostream>
#include <stdlib.h>
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
    erg+="\"Laenge\": 30\n";

    erg+="\"Time\": [";
    erg+="\""+t[0]+"\"";
    for(int x=1;x<30;x++)
    {
      erg+=", \""+t[x]+"\"";
    }
    erg+="],\n";

    erg+="\"Preis\": [";
    erg+=to_string(p[0]);
    for(int x=1;x<30;x++)
    {
      erg+=", "+to_string(p[x]);
    }
    erg+="]\n";

      erg+="}";
    return erg;
}

string ToJson::toJsonFromRoute(string* t, int* id, int* p, double* l, int length)
{
  string erg="";
  erg="{\n";
  erg+="\"Laenge\": " +to_string(length)+"\n";

  erg+="\"Time\": [";
  erg+="\""+t[0]+"\"";
  for(int x=1;x<length;x++)
  {
    erg+=", \""+t[x]+"\"";
  }
  erg+="],\n";


  erg+="\"ID\": [";
  erg+=to_string(id[0]);
  for(int x=1;x<length;x++)
  {
    erg+=", "+to_string(id[x])+"";
  }
  erg+="],\n";



  erg+="\"Preis\": [";
  erg+=to_string(p[0]);
  for(int x=1;x<length;x++)
  {
    erg+=", "+to_string(p[x]);
  }
  erg+="],\n";


  erg+="\"Litter\": [";
  erg+=to_string(l[0]);
  for(int x=1;x<length;x++)
  {
    erg+=", "+to_string(l[x]);
  }
  erg+="]\n";


  erg+="}";
  return erg;
}
