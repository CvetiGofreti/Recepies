#include "Ratings.h"
#include <iostream>
Ratings::Ratings(std::vector<Rating*>& ratings) {
	for (Rating* rating : ratings) {
		_ratings.push_back(rating);
	}
}



Ratings::Ratings(const Ratings& other) {
}

Ratings& Ratings::operator=(const Ratings& other) {
	if(this != &other){

	}
	return *this;
}

void Ratings::load(const char* filename) {
	std::ifstream iFile;
	iFile.open(filename, std::ios::binary | std::ios::in);
	if (!iFile.is_open()) {
		std::cout << "Ratings database is empty!" << std::endl;
		return;
	}
	int value = 0;
	int userId = 0;
	int recepieId = 0;
	iFile.seekg(0, std::ios::beg);
	while (!iFile.eof()) {
		iFile.read((char*)&recepieId, sizeof(recepieId));
		if (iFile.eof())break;
		iFile.read((char*)&userId, sizeof(userId));
		iFile.read((char*)&value, sizeof(value));

		Rating* toAdd = new Rating(value, recepieId, userId);
		this->addRating(toAdd);
	}
	iFile.close();
}

void Ratings::addRating(Rating* user) {
	_ratings.push_back(user);
}

Rating* Ratings::operator[](int index) {
	if (index >= _ratings.size() || index < 0) {
		throw std::exception("Invalid index");
	}
	return _ratings[index];
}

int Ratings::getSize() const {
	return _ratings.size();
}

bool Ratings::existRating(int userId, int recepieId) const {
	for (Rating* rating : _ratings) {
		if (userId == rating->getUserId() && recepieId == rating->getRecepieId()) {
			return true;
		}
	}
	return false;
}


Ratings::~Ratings() {
	for (Rating* rating : _ratings) {
		delete rating;
	}
}
