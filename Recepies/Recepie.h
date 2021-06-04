#pragma once
#include <string>
#include "FoodGroup.h"
#include "DateTime.h"
#include "ProductWithVolume.h"
#include <vector>
#include "User.h"

class Recepie
{
public:
	Recepie(std::string title, FoodGrup foodGroup, unsigned int time, std::vector<ProductWithVolume> products,	std::string algorithm,	std::string link);
	unsigned int getId() const;
	void serizalize() const;

private:
	std::string _title;
	FoodGrup _foodGroup;
	unsigned int _timeToMake;
	std::vector<ProductWithVolume> _products;
	std::string _algorithm;
	std::string _link;
	DateTime _addTime;
	double _rating;
	unsigned int _id;
	User* _owner;
protected:
	static unsigned int nextIdRecepie;
};
