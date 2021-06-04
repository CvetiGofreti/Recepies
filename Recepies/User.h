#pragma once
#include <string>
#include <iostream>
class User
{
public:
	User(std::string name, std::string hash);
	void serizalize() const;
	unsigned int getId() const;
	std::string getName() const;
	std::string getHash() const;
	void printInfo() const;
private:
	std::string _name;
	std::string _hash;
	unsigned int _id;
protected:
	static unsigned int nextId;
};
