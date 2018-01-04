#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "GasPrice.h"


using namespace std;



int main(int argc, char* argv[]) {

  int max = 15226;
  max=1;



  for(int x=1; x<=max;x++)
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

      }
      data.close();


  }





return 0;
}
