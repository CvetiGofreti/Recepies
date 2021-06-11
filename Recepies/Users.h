#pragma once
#include "User.h"
#include <vector>

class Users
{
private:
	std::vector<User*> _userList;
	Users(const Users& other) = default;
	Users& operator=(const Users& other) = default;
public:
	Users();
	Users(std::vector<User*> userList);
	void load(const char* filename);
	void addUser(User* user);
	User* operator[](int index) const;
	User* getUserById(int id) const;
	int getSize() const;
	bool isEmpty() const;
	~Users();
};

