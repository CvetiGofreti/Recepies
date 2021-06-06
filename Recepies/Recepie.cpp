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
}

int Recepie::getId() const {
	return _id;
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

}

bool Recepie::isDeleted() const {
	return _deleted;
}

void Recepie::deleteProduct(){
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
