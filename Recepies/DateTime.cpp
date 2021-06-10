#define _CRT_SECURE_NO_WARNINGS
#include "DateTime.h"
#include <iostream>
using namespace std;

void printMonth(int month) {
	switch (month)
	{
	case 1:
		cout << "JAN";
		break;
	case 2:
		cout << "FEB";
		break;
	case 3:
		cout << "MAR";
		break;
	case 4:
		cout << "APR";
		break;
	case 5:
		cout << "MAY";
		break;
	case 6:
		cout << "JUN";
		break;
	case 7:
		cout << "JUL";
		break;
	case 8:
		cout << "AUG";
		break;
	case 9:
		cout << "SEP";
		break;
	case 10:
		cout << "OCT";
		break;
	case 11:
		cout << "NOV";
		break;
	case 12:
		cout << "DEC";
		break;
	}
}
DateTime::DateTime(time_t now) {
	//time(0)
	tm* ltm = localtime(&now);
	this->_year = 1900 + ltm->tm_year;
	this->_month = 1 + ltm->tm_mon;
	this->_day = ltm->tm_mday;
	this->_hour =ltm->tm_hour;
	this->_min = ltm->tm_min;
	this->_sec = ltm->tm_sec;
}
DateTime::DateTime(int day, int month, int year, int hour, int min,int sec) {
	this->_year = year;
	this->_month = month;
	this->_day = day;
	this->_hour = hour;
	this->_min = min;
	this->_sec = sec;
}
DateTime::DateTime() {
	//time(0)
	
	this->_year = 1900;
	this->_month = 1;
	this->_day = 1;
	this->_hour = 0;
	this->_min = 0;
	this->_sec = 0;
}
void DateTime::print() const{
	cout << this->_day << " ";
	printMonth(this->_month);
	cout << " " << this->_year << ", " << this->_hour << ":" << this->_min << ":" << this->_sec << endl;
}
void DateTime::printNE() const {
	cout << this->_day << " ";
	printMonth(this->_month);
	cout << " " << this->_year << ", " << this->_hour << ":" << this->_min << ":" << this->_sec;
}
int DateTime::getYear()const {
	return this->_year;
}
int DateTime::getMonth()const {
	return this->_month;
}
int DateTime::getDay()const {
	return this->_day;
}
int DateTime::getHour()const {
	return this->_hour;
}
int DateTime::getMin()const {
	return this->_min;
}
int DateTime::getSec()const {
	return this->_sec;
}

bool DateTime::operator<(const DateTime& other) const {
	return ((_year < other._year) ||
		(_year == other._year && _month < other._month) ||
		(_year == other._year && _month == other._month && _day < other._day) ||
		(_year == other._year && _month == other._month && _day == other._day && _hour < other._hour) ||
		(_year == other._year && _month == other._month && _day == other._day && _hour == other._hour && _min < other._min) ||
		(_year == other._year && _month == other._month && _day == other._day && _hour == other._hour && _min == other._min && _sec < other._sec));
}

bool DateTime::operator>(const DateTime& other) const {
	return !(*this < other) && !(*this == other);
}

bool DateTime::operator==(const DateTime& other) const {
	return (_year == other._year && _month == other._month && _day == other._day && _hour == other._hour && _min == other._min && _sec == other._sec);
}

void DateTime::serizalize(std::ofstream& oFile) const {
	oFile.write((const char*)&_day, sizeof(_day));
	oFile.write((const char*)&_month, sizeof(_month));
	oFile.write((const char*)&_year, sizeof(_year));
	oFile.write((const char*)&_hour, sizeof(_hour));
	oFile.write((const char*)&_min, sizeof(_min));
	oFile.write((const char*)&_sec, sizeof(_sec));
}
