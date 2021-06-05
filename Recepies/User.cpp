#include "User.h"
#include <fstream>
int User::nextId = 0;

User::User(std::string name, std::string hash) {
	_id = ++nextId;
	_name = name;
	_hash = hash;
}

int User::getId() const {
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

void User::serizalize(std::ofstream &oFile) const {

	if (!oFile.is_open()) {
		throw std::exception("Could not open file");
	}
	int usernameLength = _name.size();
	int hashLength = _hash.size();
	oFile.write((const char*)&usernameLength, sizeof(usernameLength));
	oFile.write((const char*)_name.data(), usernameLength);
	oFile.write((const char*)&hashLength, sizeof(hashLength));
	oFile.write((const char*)_hash.data(), hashLength);
	oFile.close();
}