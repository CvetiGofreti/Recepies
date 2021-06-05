#pragma once
#include "User.h"
#include <vector>

class Users
{
private:
	std::vector<User*> _userList;
public:
	Users();
	Users(std::vector<User*> userList);
	Users(const Users& other);
	Users& operator=(const Users& other);
	void load(const char* filename);
	void addUser(User* user);
	User* operator[](int index);
	User* getUserById(int id);
	int getSize();
	~Users();
};

