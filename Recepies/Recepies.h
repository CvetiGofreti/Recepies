#pragma once
#include "Recepie.h"
#include <vector>

class Recepies
{
private:
	std::vector<Recepie*> _recepieList;
public:
	Recepies();
	Recepies(std::vector<Recepie*> recepieList);
	Recepies(const Recepies& other);
	Recepies& operator=(const Recepies& other);
	void load(const char* filename);
	void addRecepie(Recepie* recepie);
	Recepie* operator[](unsigned int index);
	Recepie* getRecepieById(unsigned int id);
	int getSize();
	~Recepies();
};

