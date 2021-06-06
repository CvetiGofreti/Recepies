#pragma once
#include <fstream>
class Rating
{
public:
	Rating(int value, int recepieId, int userId);
	int getValue() const;
	int getUserId() const;
	int getRecepieId() const;
	void serizalize(std::ofstream& oFile) const;
private:
	int _value;
	int _recepieId;
	int _userId;
};
