#include "Recepie.h"
#include <ctime>
#include <fstream>
unsigned int Recepie::nextIdRecepie = 0;

Recepie::Recepie(std::string title, FoodGrup foodGroup, unsigned int timeToMake, std::vector<ProductWithVolume> products, std::string algorithm, std::string link) {
	_title = title;
	_foodGroup = foodGroup;
	_timeToMake = timeToMake;
	for (ProductWithVolume product : products) {
		_products.push_back(ProductWithVolume(product));
	}
	_algorithm = algorithm;
	_link = link;
	_addTime = DateTime(time(0));
	_rating = 3;
	_id = ++nextIdRecepie;
}

unsigned int Recepie::getId() const {
	return _id;
}

void Recepie::serizalize() const {
	std::ofstream oFile;
	oFile.open("recepies.db", std::ios::binary | std::ios::out | std::ios::app);
	if (!oFile.is_open()) {
		throw std::exception("Could not open file");
	}
	unsigned int titleLength = _title.size();
	unsigned int algorithmLength = _algorithm.size();
	unsigned int linkLength = _link.size();
	unsigned int productLength = groups[static_cast<int>(_foodGroup)].size();

	oFile.write((const char*)&productLength, sizeof(productLength));
	oFile.write((const char*)groups[static_cast<int>(_foodGroup)].data(), productLength);

	oFile.write((const char*)&titleLength, sizeof(titleLength));
	oFile.write((const char*)_title.data(), titleLength);

	oFile.write((const char*)&_timeToMake, sizeof(_timeToMake));

	for(ProductWithVolume prodWithV : _products){
		prodWithV.serizalize(oFile);
	}

	oFile.write((const char*)&algorithmLength, sizeof(algorithmLength));
	oFile.write((const char*)_algorithm.data(), algorithmLength);

	oFile.write((const char*)&linkLength, sizeof(linkLength));
	oFile.write((const char*)_link.data(), linkLength);

	_addTime.serizalize(oFile);

	oFile.write((const char*)&_rating, sizeof(_rating));

	oFile.write((const char*)&_id, sizeof(_id));

	unsigned int ownerId = _owner->getId();
	oFile.write((const char*)&ownerId, sizeof(ownerId));

	oFile.close();

}
