
#include"DateTime.h"
DateTime::DateTime(int day, int month, int year, int hour, int minute, int second) {
	this->day = day;
	this->month = month;
	this->year = year;
	this->hour = hour;
	this->second = second;
	this->minute = minute;

}

DateTime ::DateTime(time_t time) {
	tm timeinfo = {};
	localtime_s(&timeinfo, &time);

	year = timeinfo.tm_year + 1900;
	month = timeinfo.tm_mon + 1;
	day = timeinfo.tm_mday;
	hour = timeinfo.tm_hour;
	minute = timeinfo.tm_min;
	second = timeinfo.tm_sec;


}
DateTime::DateTime()
{

		time_t now = time(nullptr);
		//tm* time_info = localtime(&now);
		tm time_info = {};
		localtime_s(&time_info, &now);

		year = time_info.tm_year + 1900;
		month = time_info.tm_mon + 1;
		day = time_info.tm_mday;
		hour = time_info.tm_hour;
		minute = time_info.tm_min;
		second = time_info.tm_sec;
}
//Utility function

DateTime DateTime:: now()
{
	return  DateTime();

}
DateTime DateTime:: fromString(const string& str) {
	stringstream ss(str);
	tm tm_time = {};
	ss >> get_time(&tm_time, "%Y-%m-%d %H:%M:%S");
	time_t time = mktime(&tm_time);
	return DateTime(time);
}

ostream& operator<<(ostream& os, const DateTime& dt) {
	os<< setfill('0');
	os << setw(2) << dt.year << "-";
	os << setw(2) << dt.month << "-";
	os << setw(2) << dt.day << " ";
	os << setw(2) << dt.hour << ":";
	os << setw(2) << dt.minute << ":";
	os << setw(2) << dt.second ;
	
	return os;
	

}
istream& operator>> (istream& is, DateTime& dt) {
	char c;
	is >> dt.day >> c >> dt.month >> c >> dt.year >> c >> dt.hour >> c >> dt.minute >> c >> dt.second;
	return is;
}

