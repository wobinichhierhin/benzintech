#include "CalculateRoute.h"
#include "Station.h"
#include "DriveRoute.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>

using namespace std;


CalculateRoute::CalculateRoute(Station** allStation, DriveRoute* route,  string linkName)
{
  this->linkName = linkName;

  this->allStation = allStation;
  this->route = route;

  listStation = this->route->listOfStation;
  listOfTime = this->route->arriavelAtTime;
  lengthListStation = this->route->length;

  orderList = new int[route->length-1];
  toRefuel = new double[route->length-1];
  calculate(0, route->length-2);

  double litterAvailabel = 0.0;
  for(int x=0; x<route->length-1;x++)
  {
    double litter = (distanceVonAToB(x, orderList[x])/100)*5.6;
    if(litter > 3.0)litter = 3.0;
    if(litter < litterAvailabel)
    {
      litterAvailabel -= litter;
      toRefuel[x] = 0.0;
    }
    else
    {
      toRefuel[x] = litter - litterAvailabel;
      litterAvailabel = litter -((distanceVonAToB(x,x+1)/100)*5.6);
    }
  }

  save();

}

CalculateRoute::~CalculateRoute()
{
  delete[] listStation;
  delete[] orderList;
  delete[] listOfTime;
}


void CalculateRoute::calculate(int von, int to)
{
  if(von <= to && von != route->length-1)
  {
    int min = von;
    for(int x=min+1; x<=to;x++)
    {
      if(allStation[listStation[x]-1]->getPreisatTime(listOfTime[x]-1) < allStation[listStation[min]-1]->getPreisatTime(listOfTime[x]-1))
      {
        min = x;
      }
    }
    orderList[min] = to+1;

    calculate(von, min-1);
    calculate(min+1, to);
  }
}


double CalculateRoute::distanceVonAToB(int a, int b)
{
  double ent = distance(allStation[listStation[a]-1],allStation[listStation[b]-1]);

  for(int x=a+1; x<b-1; x++)
  {
    ent += distance(allStation[listStation[x]-1],allStation[listStation[x+1]-1]);
  }

  return ent;
}

double CalculateRoute::distance(Station* a, Station* b)
{
  double entf =  6378.388 * acos((sin(a->latitude)*sin(b->latitude)) +(cos(a->latitude)*cos(b->latitude)*cos(b->longitude - a->longitude)));
    return entf*M_PI/180;
}

double* CalculateRoute::getToReful()
{
  return toRefuel;
}


void CalculateRoute::save()
{
  string* line = route->oneLine;
    string out = "Ausgabedaten/Tankstrategien/"+linkName;
    fstream dat;
    dat.open(out.c_str(), ios::out);
    for(int x=0; x<lengthListStation; x++)
    {
      string lineh = line[x]+";"+to_string(allStation[listStation[x]-1]->getPreisatTime(listOfTime[x]-1))+";"+to_string(toRefuel[x])+"\n";
    //  cout<<lineh<<endl;
      dat<<lineh;

    }
    dat.close();
}
