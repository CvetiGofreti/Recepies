#pragma once
#include <string>
#include <fstream>
class ProductWithVolume
{
public:
	ProductWithVolume(std::string product, double volume, std::string unit);
	std::string getProduct();
	double getVolume();
	void serizalize(std::ofstream& oFile) const;
	bool isDeleted() const;
	void deleteProduct();
private:
	double _volume;
	std::string _product;
	std::string _unit;
	bool deleted;
};
