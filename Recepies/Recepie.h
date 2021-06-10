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
	Recepie(std::string title, int foodGroup, int timeToMake, std::vector<ProductWithVolume> products, std::string algorithm, std::vector<Link> links, int ownerId, int id);

	int getId() const;
	int getOwnerId() const;
	void serizalize(std::ofstream &oFile) const;
	bool isDeleted() const;
	void deleteRecepie();
	std::string getTitle() const;
	void printTitle() const;
	void calculateRating(Ratings& myRatingList);
	int getTimesVisited() const;
	void visit();
	void setVisits(int visits);
	void setTitle(std::string newTitle);
	void setAlgorithm(std::string newAlgorithm);
	void setTimeToMake(int newTimeToMake);
	int getFoodGroup() const;
	void addFoodGroup(int foodGroupIndex);
	void addLink(Link& link);
	void removeFoodGroup(int foodGroupIndex);
	void removeLink(int linkIndex);
	void setFoodGroup(int newGroup);
	double getRating() const;
	DateTime getAddTime() const;
	void setAddTime(const DateTime& other);
	void printAllInfo() const;
	std::vector<ProductWithVolume> getProductList() const;
	std::vector<Link> getLinksList() const;

	void addProduct(ProductWithVolume& product);
	void deleteProduct(int index);
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
	int _timesVisited;
protected:
	static int nextIdRecepie;
};
