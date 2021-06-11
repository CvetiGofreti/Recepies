#pragma once
#include <string>
#include <fstream>
#include<iostream>
class ProductWithVolume
{
public:
	ProductWithVolume(std::string product, double volume, std::string unit);
	std::string getProduct();
	double getVolume();
	std::string getUnit();
	void serizalize(std::ofstream& oFile) const;
	bool isDeleted() const;
	void deleteProduct();
	void printInfo() const;
private:
	double _volume;
	std::string _product;
	std::string _unit;
	bool _deleted;
};
