#include "Recipes.h"

Recipes::Recipes() {
}

Recipes::Recipes(std::vector<Recipe*> recipeList) {
	for (Recipe* recipe : recipeList) {
		_recipeList.push_back(recipe);
	}
}

void Recipes::load(const char* filename) {
	std::ifstream iFile;
	iFile.open(filename, std::ios::binary | std::ios::in);
	if (!iFile.is_open()) {
		std::cout << "Recipes database is empty!" << std::endl;
		return;
	}
	
	int titleLength;
	std::string title;

	int foodGroup;

	int timeToMake;

	int numberOfProducts;
	int productLength;
	std::string product;
	int unitLength;
	std::string unit;
	double volume;
	std::vector<ProductWithVolume> products;

	int algorithmLength;
	std::string algorithm;

	int numberOfLinks;
	int linkLength;
	std::string link;
	std::vector<Link> links;


	DateTime addTime;
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;

	double rating;
	int id;
	int ownerId;
	int timesVisited;

	iFile.seekg(0, std::ios::beg);
	while (!iFile.eof()) {
		iFile.read((char*)&titleLength, sizeof(titleLength));
		if (iFile.eof()) { 
			break; 
		}
		char* titleTemp = new char[titleLength + 1];
		iFile.read(titleTemp, titleLength);
		titleTemp[titleLength] = 0;
		title = titleTemp;
		delete[] titleTemp;

		iFile.read((char*)&foodGroup, sizeof(foodGroup));

		iFile.read((char*)&timeToMake, sizeof(timeToMake));

		iFile.read((char*)&numberOfLinks, sizeof(numberOfLinks));
		for (int i = 0; i < numberOfLinks; i++) {
			iFile.read((char*)&linkLength, sizeof(linkLength));
			char* linkTemp = new char[linkLength + 1];
			iFile.read(linkTemp, linkLength);
			linkTemp[linkLength] = 0;
			link = linkTemp;
			delete[] linkTemp;
			links.push_back(link);
		}

		iFile.read((char*)&algorithmLength, sizeof(algorithmLength));
		char* algorithmTemp = new char[algorithmLength + 1];
		iFile.read(algorithmTemp, algorithmLength);
		algorithmTemp[algorithmLength] = 0;
		algorithm = algorithmTemp;
		delete[] algorithmTemp;

		iFile.read((char*)&numberOfProducts, sizeof(numberOfProducts));
		for (int i = 0; i < numberOfProducts; i++) {
			iFile.read((char*)&volume, sizeof(volume));


			iFile.read((char*)&productLength, sizeof(productLength));
			char* productTemp = new char[productLength + 1];
			iFile.read(productTemp, productLength);
			productTemp[productLength] = 0;
			product = productTemp;
			delete[] productTemp;

			iFile.read((char*)&unitLength, sizeof(unitLength));
			char* unitTemp = new char[unitLength + 1];
			iFile.read(unitTemp, unitLength);
			unitTemp[unitLength] = 0;
			unit = unitTemp;
			delete[] unitTemp;
			products.push_back(ProductWithVolume(product, volume, unit));
		}

		iFile.read((char*)&day, sizeof(day));
		iFile.read((char*)&month, sizeof(month));
		iFile.read((char*)&year, sizeof(year));
		iFile.read((char*)&hour, sizeof(hour));
		iFile.read((char*)&min, sizeof(min));
		iFile.read((char*)&sec, sizeof(sec));
		addTime = DateTime(day, month, year, hour, min, sec);

		iFile.read((char*)&rating, sizeof(rating));
		iFile.read((char*)&id, sizeof(id));
		iFile.read((char*)&ownerId, sizeof(ownerId));
		iFile.read((char*)&timesVisited, sizeof(timesVisited));

		Recipe* toAddRecipe = new Recipe(title, foodGroup, timeToMake, products, algorithm, links, ownerId, id);
		toAddRecipe->setVisits(timesVisited);
		toAddRecipe->setAddTime(addTime);
		this->addRecipe(toAddRecipe);
		products.clear();
		links.clear();
	}
	iFile.close();
}

void Recipes::addRecipe(Recipe* recipe) {
	_recipeList.push_back(recipe);
}

Recipe* Recipes::operator[](int index) {
	if (index >= _recipeList.size() || index < 0 || _recipeList[index]->isDeleted()) {
		return nullptr;
	}
	return _recipeList[index];
}

Recipe* Recipes::getRecipeById(int id) {
	for (int i = 0; i < _recipeList.size(); i++) {
		if (_recipeList[i]->getId() == id && !_recipeList[i]->isDeleted()) {
			return _recipeList[i];
		}
	}
	return nullptr;
}

int Recipes::getSize() {
	return _recipeList.size();
}

void Recipes::print() const {
	int place = 1;
	std::cout << "Recipes list: " << std::endl;
	for (Recipe* recipe : _recipeList) {
		if (!(recipe->isDeleted())) {
			std::cout << place << ". " << recipe->getTitle() << " Id: " << recipe->getId() << std::endl;
			place++;
		}
	}
}

std::vector<Recipe*> Recipes::getRecipeList() {
	return _recipeList;
}

bool Recipes::isEmpty() const {
	
	for (Recipe* recipe : _recipeList) {
		if (!recipe->isDeleted()) {
			return false;
		}
	}
	return true;
}

Recipes::~Recipes() {
	for (Recipe* recipe : _recipeList) {
		delete recipe;
	}
}


