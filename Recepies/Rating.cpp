#include "Rating.h"

Rating::Rating(int value, int recepieId, int userId) {
	_value = value;
	_recepieId = recepieId;
	_userId = userId;
}

int Rating::getValue() const {
	return _value;
}

int Rating::getUserId() const {
	return _userId;
}

int Rating::getRecepieId() const {
	return _recepieId;
}

void Rating::serizalize(std::ofstream& oFile) const {
	oFile.write((const char*)&_recepieId, sizeof(_recepieId));
	oFile.write((const char*)&_userId, sizeof(_userId));
	oFile.write((const char*)&_value, sizeof(_value));
}
