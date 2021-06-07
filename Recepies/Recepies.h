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
	Recepie* operator[](int index);
	Recepie* getRecepieById(int id);
	int getSize();
	void print() const;
	std::vector<Recepie*> getRecepieList();
	bool isEmpty() const;
	~Recepies();
};

