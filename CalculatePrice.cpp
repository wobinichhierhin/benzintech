#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "GasPrice.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<string.h>


using namespace std;



string calc(string date);
string toString(int a);

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char* argv[]) {


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
     serv_addr.sin_port = htons(8087);
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

      income = calc(income);

      n = write(newsockfd,income.c_str(),income.length());
       if (n < 0) error("ERROR writing to socket");
       close(newsockfd);
     }
     close(sockfd);

return 0;
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


  string datareturn="";
  struct tm tm;
  strptime(stime.c_str(), "%Y-%m-%d %H:%M:%S", &tm);
  time_t zeit = mktime(&tm);

  struct tm day;
  strptime("1970-01-01", "%Y-%m-%d", &day);
  time_t dayzeit = mktime(&day);
  cout<<dayzeit<<endl;
  for(int x=0; x<30; x++)
  {

    int preis = a->getPreis(zeit);

    char buffer [80];
    struct tm* h;
    h = localtime(&zeit);
    strftime(buffer,80,"%Y-%m-%d %H:%M:%S",h);

    string szeit = buffer;
    datareturn +=  szeit+";"+toString(preis)+"\n";

    zeit+=dayzeit;
  }

  return datareturn;
}

string toString(int a)
{
  string zahl="";
  int x2=a;
  do
  {
    zahl=(char)((x2%10)+48)+zahl;
    x2/=10;
  }while(x2);
  return zahl;
}
