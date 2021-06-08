#include "Recepie.h"
#include <ctime>
#include <fstream>
int Recepie::nextIdRecepie = 0;

Recepie::Recepie(std::string title, int foodGroup, int timeToMake, std::vector<ProductWithVolume> products, std::string algorithm, std::vector<Link> links, int ownerId) {
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
	_id = ++nextIdRecepie;
	_ownerId = ownerId;
	_deleted = false;
	_timesVisited = 0;
}

int Recepie::getId() const {
	return _id;
}

int Recepie::getTimesVisited() const {
	return _timesVisited;
}

void Recepie::visit() {
	_timesVisited++;
}

void Recepie::setVisits(int visits) {
	_timesVisited = visits;
}

void Recepie::setTitle(std::string newTitle) {
	_title = newTitle;
}

void Recepie::setAlgorithm(std::string newAlgorithm) {
	_algorithm = newAlgorithm;
}

void Recepie::setAddTime(const DateTime& other) {
	_addTime = other;
}

void Recepie::addLink(Link& link) {
	_links.push_back(link);
}


int Recepie::getFoodGroup()const {
	return _foodGroup;
}

void Recepie::addFoodGroup(int foodGroupIndex) {
	int result = 1;
	for (int i = 0; i < foodGroupIndex - 1; i++) {
		result *= 2;
	}
	_foodGroup = _foodGroup + result;
}

void Recepie::removeLink(int linkIndex) {
	_links[linkIndex].deleteLink();
}

void Recepie::removeFoodGroup(int foodGroupIndex) {
	int result = 1;
	for (int i = 0; i < foodGroupIndex - 1; i++) {
		result *= 2;
	}
	_foodGroup = _foodGroup - result;
}

void Recepie::printAllInfo() const {
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

	std::cout << "Time to make: " << _timeToMake << std::endl;
	std::cout << "Products: " << std::endl;
	for (ProductWithVolume product : _products) {
		product.printInfo();
	}
	std::cout << "Algorithm: " << _algorithm << std::endl;
	std::cout << "Links: " << std::endl;
	for (Link link : _links) {
		link.print();
	}
	std::cout << "Added at: ";
	_addTime.print();
	std::cout << std::endl;
	std::cout << "Rating: " << _rating << std::endl
		<< "Id: " << _id << std::endl
		<< "Owner Id: " << _ownerId << std::endl
		<< "Times visited: " << _timesVisited << std::endl;
}

void Recepie::addProduct(ProductWithVolume& product){
	_products.push_back(product);
}

std::vector<ProductWithVolume> Recepie::getProductList() const {
	return _products;
}

std::vector<Link> Recepie::getLinksList() const {
	return _links;
}


void Recepie::deleteProduct(int index) {
	_products[index].deleteProduct();
}

DateTime Recepie::getAddTime() const{
	return _addTime;
}

double Recepie::getRating() const{
	return _rating;
}

void Recepie::setFoodGroup(int newGroup) {
	_foodGroup -= newGroup;
}

void Recepie::setTimeToMake(int newTimeToMake) {
	_timeToMake = newTimeToMake;
}

int Recepie::getOwnerId() const {
	return _ownerId;
}

void Recepie::serizalize(std::ofstream& oFile) const {
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

bool Recepie::isDeleted() const {
	return _deleted;
}

void Recepie::deleteRecepie(){
	_deleted = true;
}

std::string Recepie::getTitle() const {
	return _title;
}

void Recepie::printTitle() const {
	std::cout << "Recepie Title: " << _title << std::endl;
}

void Recepie::calculateRating(Ratings& myRatingList) {
	int counter = 0;
	int sumOfRatings = 0;
	for (int i = 0; i < myRatingList.getSize(); i++) {
		if (myRatingList[i]->getRecepieId() == _id) {
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
