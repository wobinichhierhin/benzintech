#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "GasPrice.h"

#include <thread>

using namespace std;

void calc(int start, int end);

int main(int argc, char* argv[]) {

  int max = 15226;
  //max=1;

  int teiler = 1;
  if (argc > 1) teiler = atoi(argv[1]) ;
  int step = max/teiler;

  thread a[teiler+1];
cout<<step<<endl<<endl;
  for(int x=0;x<=teiler; x++)
  {
    int start = x*step+1;
    int end= (x+1)*step;
    if(end >max) end=max;
    a[x] = thread(calc, start, end);
  }

  for(int x=0;x<=teiler; x++)
  {
    a[x].join();
  }
/*
  thread a(calc, 1, 4000);
  thread b(calc, 4001, 8000);
  thread c(calc, 80001, 1200);
  thread d(calc, 12001, 15226);

   a.join();
   b.join();
   c.join();
   d.join();
*/


return 0;
}

void calc(int start, int end)
{
  for(int x=start; x<=end;x++)
  {
      string link="Eingabedaten/Benzinpreise/";
      string zahl="";
      int x2=x;
      do
      {
        zahl=(char)((x2%10)+48)+zahl;
        x2/=10;
      }while(x2);
      link+=zahl+".csv";

      string read="";
      fstream data;
      data.open(link.c_str(), ios::in);
      if(data.good())
      {
        while (!data.eof())
        {
         string dataLine;
         getline(data, dataLine);
         if(dataLine != "") read = read + dataLine +"\n";
        }

        GasPrice* station = new GasPrice(read, x);
        cout<<link<<endl;
        delete station;

      }
      data.close();
  }

}
