#pragma once
#include <ctime>

class DateTime
{
private:
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;

public:
	DateTime();
	DateTime(time_t now);
	DateTime(int _day, int _month, int _year, int _hour, int _min, int _sec);
	void print();
	int getYear()const;
	int getMonth()const;
	int getDay()const;
	int getHour()const;
	int getMin()const;
	int getSec()const;
};
