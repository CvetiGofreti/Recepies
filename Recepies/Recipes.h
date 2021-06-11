#pragma once
#include "Recipe.h"
#include <vector>
class Recipes
{
private:
	std::vector<Recipe*> _recipeList;
	Recipes(const Recipes& other) = default;
	Recipes& operator=(const Recipes& other) = default;
public:
	Recipes();
	Recipes(std::vector<Recipe*> recipeList);
	
	void load(const char* filename);
	void addRecipe(Recipe* recipe);
	Recipe* operator[](int index);
	Recipe* getRecipeById(int id);
	int getSize();
	void print() const;
	std::vector<Recipe*> getRecipeList();
	bool isEmpty() const;
	~Recipes();
};

