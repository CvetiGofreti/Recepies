#pragma once
#include <string>
#include "FoodGroup.h"
#include "DateTime.h"
#include "ProductWithVolume.h"
#include <vector>
#include "User.h"
#include "Link.h"
#include "Ratings.h"

class Recepie
{
public:
	Recepie(std::string title, int foodGroup, int timeToMake, std::vector<ProductWithVolume> products, std::string algorithm, std::vector<Link> links, int ownerId);
	int getId() const;
	int getOwnerId() const;
	void serizalize(std::ofstream &oFile) const;
	bool isDeleted() const;
	void deleteProduct();
	std::string getTitle() const;
	void printTitle() const;
	void calculateRating(Ratings& myRatingList);

private:
	std::string _title;
	int _foodGroup;
	int _timeToMake;
	std::vector<ProductWithVolume> _products;
	std::string _algorithm;
	std::vector<Link> _links;
	DateTime _addTime;
	double _rating;
	int _id;
	int _ownerId;
	bool _deleted;
protected:
	static int nextIdRecepie;
};
