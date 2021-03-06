#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "Station.h"
#include "DriveRoute.h"
#include "CalculateRoute.h"
#include "GasPrice.h"
#include "toJson.h"

#include <stdio.h>
#include <unistd.h>
#include <winsock.h>
//#include <netinet/in.h>
#include <time.h>
#include <sys/types.h>  
#include <sys/timeb.h>  

	#include <time.h>
	#include "ToTime.h"

using namespace std;


Station* allStation[15226];
int numberOfStation;


void init();

void readAllStation();
DriveRoute* readDriveRoute(string route);

string calcRoute(string linkName);

string calc(string date);




string menue(string income);

void errorabruch(const char *msg)
{
    perror(msg);
    exit(1);
}
void error(const char *msg)
{
    perror(msg);
  //  exit(1);
}

int main(int argc, char* argv[]) {
/*
   if (argc < 2)
   {
     cout<<"missing port number"<<endl;
     exit(1);
   }
   */

    init();

	 WSADATA wsa;
	 SOCKET sockfd, newsockfd;     
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
	  if (WSAStartup(MAKEWORD(2,2),&wsa) != 0) errorabruch("Failed. Error Code :");

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
	 if(sockfd == INVALID_SOCKET)  errorabruch("ERROR opening socket");
   
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     //serv_addr.sin_port = htons(atoi(argv[1]));
	 serv_addr.sin_port = htons(8080);
	  if( bind(sockfd ,(struct sockaddr *)&serv_addr , sizeof(serv_addr)) == SOCKET_ERROR)  errorabruch("ERROR on binding");
   
     listen(sockfd,5);
	 
	n = sizeof(struct sockaddr_in);
	
	 while(1)
     {
		 memset(buffer, 0, 256);
		newsockfd = accept(sockfd , (struct sockaddr *)&cli_addr, &n);
		if (newsockfd == INVALID_SOCKET)error("ERROR on accept");
		int res = recv(newsockfd,buffer,256, 0);

		string income = buffer;
		string out="";
		out = menue(income);

		send(newsockfd, out.c_str(),out.length(),0);
       
       close(newsockfd);
     }
     close(sockfd);
	 WSACleanup();





return 0;
}

string menue(string income)
{
  string selection="";
  string data="";
  for(int x=0;x<5;x++)selection+=income[x];
  for(int x=6;x<income.length();x++)data+=income[x];


  if( selection == "route")
  {
      return calcRoute(data);
  }
  else
  {
    if( selection == "price")
    {
      return calc(data);
    }
  }

  return "wrong command";

}

void init()
{
  numberOfStation=0;
  readAllStation();
}

string calcRoute(string linkName)
{
  DriveRoute* route = readDriveRoute(linkName);
  if(route == NULL) return "error file";
  CalculateRoute* calc= new CalculateRoute(allStation, route, linkName);

  ToJson* json = new ToJson();
  return json->toJsonFromRoute(calc->getTime(), calc->getListStation(), calc->getPice(), calc->getToReful(), calc->getLength());

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
  else return NULL;
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

string calc(string date)
{
  string sid="";
  string stime="";
  bool flag=1;
  for(int x=0; x<date.length();x++)
  {
    if(date[x]!=';')
    {
      if(flag)sid += date[x];
      else stime += date[x];
    }
    else flag=0;
  }

  int id =atoi( sid.c_str() );
  if( id < 1 || id > 15226) return "error id";

  GasPrice* a = new GasPrice(id);

  struct tm tm = toTime(stime);
  //strftime((char*)stime.c_str(),stime.length(), "%Y-%m-%d %H:%M:%S", &tm);
  time_t zeit = mktime(&tm);

	
 
  time_t dayzeit =  86400; // one day
  string t[30];
  int p[30];
  for(int x=0; x<30; x++)
  {
    int preis = a->getPreis(zeit);

    char buffer [80];
    struct tm* h;
    h = localtime(&zeit);
    strftime(buffer,80,"%Y-%m-%d %H:%M:%S",h);
    t[x]=buffer;
    p[x]=preis;

    zeit+=dayzeit;
  }

  ToJson* json = new ToJson();
  return json->toJsonFromPrice(t, p);
}
