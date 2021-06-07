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

User* Users::operator[](int index) {
	if (index >= _userList.size() || index < 0) {
		throw std::exception("Invalid index");
	}
	
	return _userList[index];
}

User* Users::getUserById(int id) {
	for (int i = 0; i < _userList.size(); i++) {
		if (_userList[i]->getId() == id) {
			return _userList[i];
		}
	}
	//throw std::exception("No user with this id");
	return nullptr;
}

void Users::load(const char* filename) {
	std::ifstream iFile;
	iFile.open(filename, std::ios::binary | std::ios::in);
	if (!iFile.is_open()) {
		std::cout <<  "Database is empty!" << std::endl;
		return;
	}
	int usernameLength = 0;
	int hashLength = 0;
	iFile.seekg(0, std::ios::beg);
	while (!iFile.eof()) {
		iFile.read((char*)&usernameLength, sizeof(usernameLength));
		if (iFile.eof())break;
		//std::cout << "length: " << usernameLength << std::endl;
		char* usernameTemp = new char[usernameLength + 1];
		iFile.read(usernameTemp, usernameLength);
		usernameTemp[usernameLength] = 0;
		std::string username = usernameTemp;
		//std::cout << "name: " << username << std::endl;
		delete[] usernameTemp;


		iFile.read((char*)&hashLength, sizeof(hashLength));
		//std::cout << "hash length: " << hashLength << std::endl;
		char* hashTemp = new char[hashLength + 1];
		iFile.read(hashTemp, hashLength);
		hashTemp[hashLength] = 0;
		std::string hash = hashTemp;
		delete[] hashTemp;
		//std::cout << "hash: " << hash << std::endl;
		User* toAdd = new User(username, hash);
		this->addUser(toAdd);
	}
	iFile.close();
}

void Users::addUser(User* user) {
	_userList.push_back(user);
}

int Users::getSize() {
	return _userList.size();
}

Users::~Users()
{
	for (User* user : _userList) {
		delete user;
	}
}