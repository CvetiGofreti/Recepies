#pragma once
#include <ctime>
#include <fstream>
class DateTime
{
private:
	int _year;
	int _month;
	int _day;
	int _hour;
	int _min;
	int _sec;

public:
	DateTime();
	DateTime(time_t now);
	DateTime(int day, int month, int year, int hour, int min, int sec);
	void print()const ;
	void printNE() const;
	int getYear()const;
	int getMonth()const;
	int getDay()const;
	int getHour()const;
	int getMin()const;
	int getSec()const;

	bool operator<(const DateTime& other)const;
	bool operator>(const DateTime& other)const;
	bool operator==(const DateTime& other)const;

	void serizalize(std::ofstream& oFile) const;

};
