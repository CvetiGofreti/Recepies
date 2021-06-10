#include"Users.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>

Users::Users() {
}

Users::Users(std::vector<User*> userList) {
	for (User* user : userList) {
		_userList.push_back(user);
	}
}

Users::Users(const Users& other) : Users(other._userList) {
}

Users& Users:: operator=(const Users& other) {
	if (this != &other) {
		for (User* user : _userList) {
			delete user;
		}
		_userList.clear();
		for (User* user : other._userList) {
			_userList.push_back(user);
		}
	}
	return *this;
}

User* Users::operator[](int index) const {
	if (index >= _userList.size() || index < 0) {
		return nullptr;
	}
	return _userList[index];
}

User* Users::getUserById(int id) const {
	for (int i = 0; i < _userList.size(); i++) {
		if (_userList[i]->getId() == id) {
			return _userList[i];
		}
	}
	return nullptr;
}

void Users::load(const char* filename) {
	std::ifstream iFile;
	iFile.open(filename, std::ios::binary | std::ios::in);
	if (!iFile.is_open()) {
		std::cout <<  "Users database is empty!" << std::endl;
		return;
	}
	int usernameLength = 0;
	int hashLength = 0;
	iFile.seekg(0, std::ios::beg);
	while (!iFile.eof()) {
		iFile.read((char*)&usernameLength, sizeof(usernameLength));
		if (iFile.eof())break;
		char* usernameTemp = new char[usernameLength + 1];
		iFile.read(usernameTemp, usernameLength);
		usernameTemp[usernameLength] = 0;
		std::string username = usernameTemp;
		delete[] usernameTemp;
		iFile.read((char*)&hashLength, sizeof(hashLength));
		char* hashTemp = new char[hashLength + 1];
		iFile.read(hashTemp, hashLength);
		hashTemp[hashLength] = 0;
		std::string hash = hashTemp;
		delete[] hashTemp;
		User* toAdd = new User(username, hash);
		this->addUser(toAdd);
	}
	iFile.close();
}

void Users::addUser(User* user) {
	_userList.push_back(user);
}

int Users::getSize()const {
	return _userList.size();
}

bool Users::isEmpty() const{
	return _userList.size() == 0;
}

Users::~Users() {
	for (User* user : _userList) {
		delete user;
	}
}