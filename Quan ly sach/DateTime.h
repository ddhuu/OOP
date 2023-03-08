#pragma once
#include<iostream>
#include<string>
#include<iomanip>
#include<ctime>
#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>
using namespace std;
 

class DateTime {
private:
	int day, month, year, hour, minute, second;
public:
	//Constructor
	DateTime();
	DateTime(time_t time);
	DateTime(int day, int month, int year, int hour, int minute, int second);
	//Getter
	int getYear() const { return year; }
	int getMonth() const { return month; }
	int getDay() const { return day; }
	int getHour() const { return hour; }
	int getMinute() const { return minute; }
	int getSecond() const { return second; }
	// Utility function
    static DateTime now();
	static DateTime fromString(const string& str);
	// I/O stream
	friend ostream& operator<<(ostream& os, const DateTime& dt);
	friend istream& operator>> (istream& is,  DateTime& dt);
};