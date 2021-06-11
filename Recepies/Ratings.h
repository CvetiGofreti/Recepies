#pragma once
#include "Rating.h"
#include <vector>
class Ratings
{
public:
	Ratings() {
	};
	Ratings(std::vector<Rating*>& ratings);
	
	void load(const char* filename);
	void addRating(Rating* user);
	Rating* operator[](int index);
	int getSize() const;
	bool existRating(int userId, int recipeId) const;
	~Ratings();
private:
	std::vector<Rating*> _ratings;
	Ratings(const Ratings& other) = default;
	Ratings& operator=(const Ratings& other) = default;
};
