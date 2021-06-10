#include "Recepies.h"

Recepies::Recepies() {
}

Recepies::Recepies(std::vector<Recepie*> recepieList) {
	for (Recepie* recepie : recepieList) {
		_recepieList.push_back(recepie);
	}
}

Recepies::Recepies(const Recepies& other) : Recepies(other._recepieList) {
}

Recepies& Recepies::operator=(const Recepies& other) {
	if (this != &other) {
		for (Recepie* recepie : _recepieList) {
			delete recepie;
		}
		_recepieList.clear();
		for (Recepie* recepie : other._recepieList) {
			_recepieList.push_back(recepie);
		}
	}
	return *this;
}

void Recepies::load(const char* filename) {
	std::ifstream iFile;
	iFile.open(filename, std::ios::binary | std::ios::in);
	if (!iFile.is_open()) {
		std::cout << "Recepies database is empty!" << std::endl;
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

		Recepie* toAddRecepie = new Recepie(title, foodGroup, timeToMake, products, algorithm, links, ownerId, id);
		toAddRecepie->setVisits(timesVisited);
		toAddRecepie->setAddTime(addTime);
		this->addRecepie(toAddRecepie);
		products.clear();
		links.clear();
	}
	iFile.close();
}

void Recepies::addRecepie(Recepie* recepie) {
	_recepieList.push_back(recepie);
}

Recepie* Recepies::operator[](int index) {
	if (index >= _recepieList.size() || index < 0 || _recepieList[index]->isDeleted()) {
		return nullptr;
	}
	return _recepieList[index];
}

Recepie* Recepies::getRecepieById(int id) {
	for (int i = 0; i < _recepieList.size(); i++) {
		if (_recepieList[i]->getId() == id && !_recepieList[i]->isDeleted()) {
			return _recepieList[i];
		}
	}
	return nullptr;
}

int Recepies::getSize() {
	return _recepieList.size();
}

void Recepies::print() const { 
	int place = 1;
	std::cout << "Recepies list: " << std::endl;
	for (Recepie* recepie : _recepieList) {
		if (!(recepie->isDeleted())) {
			std::cout << place << ". " << recepie->getTitle() << " Id: " << recepie->getId() << std::endl;
			place++;
		}
	}
}

std::vector<Recepie*> Recepies::getRecepieList() {
	return _recepieList;
}

bool Recepies::isEmpty() const {
	
	for (Recepie* recepie : _recepieList) {
		if (!recepie->isDeleted()) {
			return false;
		}
	}
	return true;
}

Recepies::~Recepies() {
	for (Recepie* recepie : _recepieList) {
		delete recepie;
	}
}


