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
}

void Recepies::addRecepie(Recepie* recepie) {
	_recepieList.push_back(recepie);
}

Recepie* Recepies::operator[](unsigned int index) {
	if (index >= _recepieList.size()) {
		throw std::exception("Invalid index");
	}
	return _recepieList[index];
}

Recepie* Recepies::getRecepieById(unsigned int id) {
	for (int i = 0; i < _recepieList.size(); i++) {
		if (_recepieList[i]->getId() == id) {
			return _recepieList[i];
		}
	}
	throw std::exception("No user with this id");
	return nullptr;
}

int Recepies::getSize() {
	return _recepieList.size();
}

Recepies::~Recepies() {
	for (Recepie* recepie : _recepieList) {
		delete recepie;
	}
}


