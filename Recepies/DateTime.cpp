#define _CRT_SECURE_NO_WARNINGS
#include "DateTime.h"
#include <iostream>
using namespace std;

void printMonth(int _month) {
	switch (_month)
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
	this->year = 1900 + ltm->tm_year;
	this->month = 1 + ltm->tm_mon;
	this->day = ltm->tm_mday;
	this->hour =ltm->tm_hour;
	this->min = ltm->tm_min;
	this->sec = ltm->tm_sec;
}
DateTime::DateTime(int _day, int _month, int _year, int _hour, int _min,int _sec) {
	this->year = _year;
	this->month = _month;
	this->day = _day;
	this->hour = _hour;
	this->min = _min;
	this->sec = _sec;
}
DateTime::DateTime() {
	//time(0)
	
	this->year = 1900;
	this->month = 1;
	this->day = 1;
	this->hour = 0;
	this->min = 0;
	this->sec = 0;
}
void DateTime::print(){
	cout << this->day << " ";
	printMonth(this->month);
	cout << " " << this->year << ", " << this->hour << ":" << this->min << ":" << this->sec << endl;
}
int DateTime::getYear()const {
	return this->year;
}
int DateTime::getMonth()const {
	return this->month;
}
int DateTime::getDay()const {
	return this->day;
}
int DateTime::getHour()const {
	return this->hour;
}
int DateTime::getMin()const {
	return this->min;
}
int DateTime::getSec()const {
	return this->sec;
}
