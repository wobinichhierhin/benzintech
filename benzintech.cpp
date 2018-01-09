#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "Station.h"
#include "DriveRoute.h"
#include "CalculateRoute.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<string.h>


using namespace std;


Station* allStation[15226];
int numberOfStation;


void init();

void readAllStation();
DriveRoute* readDriveRoute(string route);

void calcRoute(string linkName);

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char* argv[]) {

  init();



  int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) error("ERROR opening socket");
     
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(8080);
     int b = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
     if (b < 0) error("ERROR on binding");

     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     while(1)
     {
       newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
       if (newsockfd < 0)
            error("ERROR on accept");
       bzero(buffer,256);
       n = read(newsockfd,buffer,256);
       if (n < 0) error("ERROR reading from socket");

      string income = buffer;
      calcRoute(income);
      income = "ready "+income;

      n = write(newsockfd,income.c_str(),income.length());
       if (n < 0) error("ERROR writing to socket");
       close(newsockfd);
     }
     close(sockfd);





return 0;
}

void init()
{
  numberOfStation=0;
  readAllStation();
}

void calcRoute(string linkName)
{
  DriveRoute* route = readDriveRoute(linkName);

  CalculateRoute* calc= new CalculateRoute(allStation, route, linkName);

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
