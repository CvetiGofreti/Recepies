#include "User.h"
#include <fstream>
unsigned int User::nextId = 0;

User::User(std::string name, std::string hash) {
	_id = ++nextId;
	_name = name;
	_hash = hash;
}

unsigned int User::getId() const {
	return _id;
}

std::string User::getName() const {
	return _name;
}

std::string User::getHash() const {
	return _hash;
}

void User::printInfo() const {
	std::cout << "Username: " << _name << std::endl
		<< "Id: " << _id << std::endl;
}

void User::serizalize() const {
	std::ofstream oFile;
	oFile.open("users.db", std::ios::binary | std::ios::out | std::ios::app);
	if (!oFile.is_open()) {
		throw std::exception("Could not open file");
	}
	unsigned int usernameLength = _name.size();
	unsigned int hashLength = _hash.size();
	oFile.write((const char*)&usernameLength, sizeof(usernameLength));
	oFile.write((const char*)_name.data(), usernameLength);
	oFile.write((const char*)&hashLength, sizeof(hashLength));
	oFile.write((const char*)_hash.data(), hashLength);
	oFile.close();
}