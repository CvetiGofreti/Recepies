#include "Recipe.h"
#include <ctime>
#include <fstream>
#include <iomanip>

int Recipe::nextIdRecipe = 0;

Recipe::Recipe(std::string title, int foodGroup, int timeToMake, std::vector<ProductWithVolume> products, std::string algorithm, std::vector<Link> links, int ownerId) {
	_title = title;
	_foodGroup = foodGroup;
	_timeToMake = timeToMake;
	for (ProductWithVolume product : products) {
		_products.push_back(ProductWithVolume(product));
	}
	_algorithm = algorithm;
	for (Link link : links) {
		_links.push_back(Link(link));
	}
	_addTime = DateTime(time(0));
	_rating = 3;
	_id = ++nextIdRecipe;
	_ownerId = ownerId;
	_deleted = false;
	_timesVisited = 0;
}

Recipe::Recipe(std::string title, int foodGroup, int timeToMake, std::vector<ProductWithVolume> products, std::string algorithm, std::vector<Link> links, int ownerId, int id){
	_title = title;
	_foodGroup = foodGroup;
	_timeToMake = timeToMake;
	for (ProductWithVolume product : products) {
		_products.push_back(ProductWithVolume(product));
	}
	_algorithm = algorithm;
	for (Link link : links) {
		_links.push_back(Link(link));
	}
	_addTime = DateTime(time(0));
	_rating = 3;
	_id = id;
	_ownerId = ownerId;
	_deleted = false;
	_timesVisited = 0;
	nextIdRecipe = id;
}

int Recipe::getId() const {
	return _id;
}

int Recipe::getTimesVisited() const {
	return _timesVisited;
}

void Recipe::visit() {
	_timesVisited++;
}

void Recipe::setVisits(int visits) {
	_timesVisited = visits;
}

void Recipe::setTitle(std::string newTitle) {
	_title = newTitle;
}

void Recipe::setAlgorithm(std::string newAlgorithm) {
	_algorithm = newAlgorithm;
}

void Recipe::setAddTime(const DateTime& other) {
	_addTime = other;
}

void Recipe::addLink(Link& link) {
	_links.push_back(link);
}


int Recipe::getFoodGroup()const {
	return _foodGroup;
}

void Recipe::addFoodGroup(int foodGroupIndex) {
	int result = 1;
	for (int i = 0; i < foodGroupIndex - 1; i++) {
		result *= 2;
	}
	_foodGroup = _foodGroup + result;
}

void Recipe::removeLink(int linkIndex) {
	_links[linkIndex].deleteLink();
}

void Recipe::removeFoodGroup(int foodGroupIndex) {
	int result = 1;
	for (int i = 0; i < foodGroupIndex - 1; i++) {
		result *= 2;
	}
	_foodGroup = _foodGroup - result;
}

void Recipe::printAllInfo() const {
	std::cout << "=======Recipe=======" << std::endl;
	std::cout << "Title: " << _title << std::endl;
	std::cout << "FoodGroups: " << std::endl;

	int numberOfFoodGroups = 1;
	if ((_foodGroup & 1) != 0) {
		std::cout  << numberOfFoodGroups<< ". vegetables" << std::endl;
		numberOfFoodGroups++;
	}
	if ((_foodGroup & 2) != 0) {
		std::cout << numberOfFoodGroups << ". fruits" << std::endl;
		numberOfFoodGroups++;
	}
	if ((_foodGroup & 4) != 0) {
		std::cout << numberOfFoodGroups << ". cereals" << std::endl;
		numberOfFoodGroups++;
	}
	if ((_foodGroup & 8) != 0) {
		std::cout << numberOfFoodGroups << ". meat" << std::endl;
		numberOfFoodGroups++;
	}
	if ((_foodGroup & 16) != 0) {
		std::cout << numberOfFoodGroups << ". seafood" << std::endl;
		numberOfFoodGroups++;
	}
	if ((_foodGroup & 32) != 0) {
		std::cout << numberOfFoodGroups << ". dairy" << std::endl;
		numberOfFoodGroups++;
	}
	if ((_foodGroup & 64) != 0) {
		std::cout << numberOfFoodGroups << ". eggs" << std::endl;
	}

	std::cout << "Time to make: " << _timeToMake << " minutes"<< std::endl;
	std::cout << "Products: " << std::endl;
	int numberOfProducts = 1;
	for (ProductWithVolume product : _products) {
		std::cout << numberOfProducts << ". ";
		product.printInfo();
		numberOfProducts++;
	}
	std::cout << "Algorithm: " << _algorithm << std::endl;
	std::cout << "Links: " << std::endl;
	int numberOfLinks = 1;
	for (Link link : _links) {
		std::cout << numberOfLinks << ". ";
		link.print();
		numberOfLinks++;
	}
	std::cout << "Added at: ";
	_addTime.print();
	std::cout << "Rating: " << std::setprecision(2) << std::fixed << _rating  << "/5"<< std::endl
		<< "Id: " << _id << std::endl
		<< "Owner Id: " << _ownerId << std::endl
		<< "Times visited: " << _timesVisited << std::endl;
	std::cout << "=====================" << std::endl;
}

void Recipe::addProduct(ProductWithVolume& product){
	_products.push_back(product);
}

std::vector<ProductWithVolume> Recipe::getProductList() const {
	return _products;
}

std::vector<Link> Recipe::getLinksList() const {
	return _links;
}


void Recipe::deleteProduct(int index) {
	_products[index].deleteProduct();
}

DateTime Recipe::getAddTime() const{
	return _addTime;
}

double Recipe::getRating() const{
	return _rating;
}

void Recipe::setFoodGroup(int newGroup) {
	_foodGroup -= newGroup;
}

void Recipe::setTimeToMake(int newTimeToMake) {
	_timeToMake = newTimeToMake;
}

int Recipe::getOwnerId() const {
	return _ownerId;
}

void Recipe::serizalize(std::ofstream& oFile) const {
	if (!oFile.is_open()) {
		throw std::exception("Could not open file");
	}
	int titleLength = _title.size();
	int algorithmLength = _algorithm.size();
	
	int numberOfProducts = 0;
	int numberOfLinks = 0;
	for (ProductWithVolume prodWithV : _products) {
		if (!prodWithV.isDeleted()) {
			numberOfProducts++;
		}
	}
	for (Link link : _links) {
		if (!(link.isDeleted())) {
			numberOfLinks++;
		}
	}

	oFile.write((const char*)&titleLength, sizeof(titleLength));
	oFile.write((const char*)_title.data(), titleLength);

	oFile.write((const char*)&_foodGroup, sizeof(_foodGroup));

	oFile.write((const char*)&_timeToMake, sizeof(_timeToMake));

	oFile.write((const char*)&numberOfLinks, sizeof(numberOfLinks));
	for (Link link : _links) {
		if (!link.isDeleted()) {
			link.serizalize(oFile);
		}
	}

	oFile.write((const char*)&algorithmLength, sizeof(algorithmLength));
	oFile.write((const char*)_algorithm.data(), algorithmLength);

	oFile.write((const char*)&numberOfProducts, sizeof(numberOfProducts));
	for(ProductWithVolume prodWithV : _products){
		if (!prodWithV.isDeleted()) {
				prodWithV.serizalize(oFile);
		}
	}

	_addTime.serizalize(oFile);

	oFile.write((const char*)&_rating, sizeof(_rating));

	oFile.write((const char*)&_id, sizeof(_id));

	oFile.write((const char*)&_ownerId, sizeof(_ownerId));

	oFile.write((const char*)&_timesVisited, sizeof(_timesVisited));
}

bool Recipe::isDeleted() const {
	return _deleted;
}

void Recipe::deleteRecipe(){
	_deleted = true;
}

std::string Recipe::getTitle() const {
	return _title;
}

void Recipe::printTitle() const {
	std::cout << _title << std::endl;
}

void Recipe::calculateRating(Ratings& myRatingList) {
	double counter = 0;
	double sumOfRatings = 0;
	for (int i = 0; i < myRatingList.getSize(); i++) {
		if (myRatingList[i]->getRecipeId() == _id) {
			counter++;
			sumOfRatings += (myRatingList[i]->getValue());
		}
	}
	if (counter == 0) {
		_rating = 3;
	}
	else {
		_rating = sumOfRatings / counter;
	}
}
