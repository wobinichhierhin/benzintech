#include "DriveRoute.h"
#include <iostream>
#include <stdlib.h>


using namespace std;


DriveRoute::DriveRoute(string data)
{

  length=0;
  for(int x=0; x<data.length();x++)if(data[x]=='\n')length++;
  length--; //wegen der ersten zeile, die kein inhalt hat

  listOfStation = new int[length];
  arriavelAtTime = new int[length];
  oneLine = new string[length];


  int x=0;
  bool first=0;
  int counter=0;
  string line="";
  while(data[x])
  {
    if(data[x]!='\n')line+=data[x];
    else
    {
      if(first)
      {
        string avTime="";
        string id="";
        bool split=1;
        for(int y=0; y<line.length();y++)
        {
          if(split)
          {
            if(line[y]!= ';') avTime += line[y];
            else split = 0;

          }
          else id += line[y];
        }
        listOfStation[counter] =atoi( id.c_str() );
        arriavelAtTime[counter] =0;

        oneLine[counter]=line;

        counter++;
      }
      else first = 1;
      line="";
    }
    x++;
  }

}

DriveRoute::~DriveRoute()
{
  delete[] listOfStation;
  delete[] arriavelAtTime;
  delete[] oneLine;

}
