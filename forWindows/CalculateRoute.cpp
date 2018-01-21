	#define _USE_MATH_DEFINES
#include "CalculateRoute.h"
#include "Station.h"
#include "DriveRoute.h"
#include <iostream>
#include <stdlib.h>
//#include <math.h>
	#include <cmath>
#include <fstream>
	#include <sstream>
	#include <time.h>

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

  delete[]price;
  delete[]timeStation;
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

string* CalculateRoute::getTime()
{
  timeStation =new string[lengthListStation];
  for(int x=0; x<lengthListStation; x++)
  {
    char buffer [80];
    struct tm* h;
    h = localtime(&listOfTime[x]);
    strftime(buffer,80,"%Y-%m-%d %H:%M:%S",h);
    timeStation[x]=buffer;

  }
  return timeStation;
}

int* CalculateRoute::getListStation()
{
  return listStation;
}

int* CalculateRoute::getPice()
{
  price = new int[lengthListStation];
  for(int x=0; x<lengthListStation; x++)
  {
    price[x] = allStation[listStation[x]-1]->getPreisatTime(listOfTime[x]-1);
  }

  return price;
}

int CalculateRoute::getLength()
{
  return lengthListStation;
}


void CalculateRoute::save()
{
  string* line = route->oneLine;
    string out = "Ausgabedaten/Tankstrategien/"+linkName;
    fstream dat;
    dat.open(out.c_str(), ios::out);
    for(int x=0; x<lengthListStation; x++)
    {
			ostringstream stream1;
			ostringstream stream2;
			stream1<<allStation[listStation[x]-1]->getPreisatTime(listOfTime[x]-1);
			stream2<<toRefuel[x];
      string lineh = line[x]+";"+stream1.str()+";"+stream2.str()+"\n";
    //  cout<<lineh<<endl;
      dat<<lineh;

    }
    dat.close();
}
