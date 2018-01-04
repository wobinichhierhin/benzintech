#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "Station.h"
#include "DriveRoute.h"
#include "CalculateRoute.h"

using namespace std;


Station* allStation[15226];
int numberOfStation;



void readAllStation();
DriveRoute* readDriveRoute(string route);

int main(int argc, char* argv[]) {

  numberOfStation=0;
  readAllStation();

  DriveRoute* route = readDriveRoute("Bertha Benz Memorial Route.csv");

  CalculateRoute* calc= new CalculateRoute(allStation, route, "Bertha Benz Memorial Route.csv");

  double* t = calc->getToReful();

  for(int x=0; x<route->length-1;x++)cout<<x<<"  "<<t[x]<<endl;





return 0;
}


DriveRoute* readDriveRoute(string route)
{
  string data="";
  string link="Eingabedaten/Fahrzeugrouten/"+route;
  fstream dataIn;
  dataIn.open(link.c_str(), ios::in);
  if(dataIn.good())
  {
    while(!dataIn.eof())
    {
      string line="";
      getline(dataIn, line);
      if(line != "")
      {
        data += line +'\n';
      }
    }
  }
  dataIn.close();

  DriveRoute* a = new DriveRoute(data);

  return a;
}



void readAllStation()
{
  char link[]="Eingabedaten/Tankstellen.csv";

  string data="";

  fstream dataIn;
  dataIn.open(link, ios::in);
  if(dataIn.good())
  {
    while(!dataIn.eof())
    {
      string line="";
      getline(dataIn, line);
      if(line != "")
      {
        data += line +'\n';
        numberOfStation++;
      }
    }
  }
  dataIn.close();

//  allStation = new Station[numberOfStation];
  int x=0;
  int y=0;
  string lineStation="";
  while(data[x])
  {
    if(data[x]!='\n')lineStation += data[x];
    else
    {
      allStation[y] = new Station(lineStation);
      y++;
      lineStation="";
    }
    x++;
  }


}
