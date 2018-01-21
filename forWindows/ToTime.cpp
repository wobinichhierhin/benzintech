#include<ctime>
#include <iostream>
#include <stdlib.h>
#include "ToTime.h"

using namespace std;

struct tm toTime(string time)
{
string jahr = time.substr (0,4);
string monat = time.substr (5,2);
string tag = time.substr (8,2);

string stunde = time.substr (11,2);
string minute = time.substr (14,2);
string secunde = time.substr (17,2);

struct tm erg;
	erg.tm_year = atoi(jahr.c_str()) -1900;
	erg.tm_mon = atoi(monat.c_str())-1;
	erg.tm_mday = atoi(tag.c_str());

	erg.tm_hour = atoi(stunde.c_str());
	erg.tm_min = atoi(minute.c_str());
	erg.tm_sec = atoi(secunde.c_str());

return erg;
}
