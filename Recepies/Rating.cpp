#include "Rating.h"

Rating::Rating(int value, int recipeId, int userId) {
	_value = value;
	_recipeId = recipeId;
	_userId = userId;
	_deleted = false;
}

int Rating::getValue() const {
	return _value;
}

int Rating::getUserId() const {
	return _userId;
}

int Rating::getRecipeId() const {
	return _recipeId;
}

void Rating::serizalize(std::ofstream& oFile) const {
	oFile.write((const char*)&_recipeId, sizeof(_recipeId));
	oFile.write((const char*)&_userId, sizeof(_userId));
	oFile.write((const char*)&_value, sizeof(_value));
}

bool Rating::isDeleted() const {
	return _deleted;
}

void Rating::deleteRating() {
	_deleted = true;
}
