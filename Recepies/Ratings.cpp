#include "Ratings.h"
#include <iostream>
Ratings::Ratings(std::vector<Rating*>& ratings) {
	for (Rating* rating : ratings) {
		_ratings.push_back(rating);
	}
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
	int recipeId = 0;
	iFile.seekg(0, std::ios::beg);
	while (!iFile.eof()) {
		iFile.read((char*)&recipeId, sizeof(recipeId));
		if (iFile.eof())break;
		iFile.read((char*)&userId, sizeof(userId));
		iFile.read((char*)&value, sizeof(value));

		Rating* toAdd = new Rating(value, recipeId, userId);
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

bool Ratings::existRating(int userId, int recipeId) const {
	for (Rating* rating : _ratings) {
		if (userId == rating->getUserId() && recipeId == rating->getRecipeId()) {
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
