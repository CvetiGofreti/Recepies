#pragma once
#include <string>
#include <fstream>
class ProductWithVolume
{
public:
	ProductWithVolume(std::string product, double volume);
	std::string getProduct();
	double getVolume();
	void serizalize(std::ofstream& oFile) const;
private:
	double _volume;
	std::string _product;
};
