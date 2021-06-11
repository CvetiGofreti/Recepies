#pragma once
#include <fstream>
class Rating
{
public:
	Rating(int value, int recipeId, int userId);
	int getValue() const;
	int getUserId() const;
	int getRecipeId() const;
	void serizalize(std::ofstream& oFile) const;
	bool isDeleted() const;
	void deleteRating();
private:
	int _value;
	int _recipeId;
	int _userId;
	bool _deleted;
};
