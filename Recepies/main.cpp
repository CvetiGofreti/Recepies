#include "C:\Users\Cveti\source\repos\Recepies\Recepies\libbcrypt\include\bcrypt\BCrypt.hpp"
#include <stdlib.h>
#include <string>
#include "User.h"
#include "Users.h"
#include "Commands.h"



bool isValidUsername(std::string name) {
	bool areAllValid = true;
	for (char symbol : name) {
		if (!((symbol >= 'A' && symbol <= 'Z') || (symbol >= 'a' && symbol <= 'z') || symbol == '-' || symbol == '.' || symbol == '_')) {
			areAllValid = false;
		}
	}
	return areAllValid;
}

bool containsCapitalLetter(std::string word) {
	bool contains = false;
	for (char symbol : word) {
		if ((symbol >= 'A' && symbol <= 'Z')) {
			contains = true;
		}
	}
	return contains;
}

bool containsSmalllLetter(std::string word) {
	bool contains = false;
	for (char symbol : word) {
		if ((symbol >= 'a' && symbol <= 'z')) {
			contains = true;
		}
	}
	return contains;
}

int main() {
	Users myUserList;
	myUserList.load("users.db");
	registerUser(myUserList);
	loginUser(myUserList);
	registerUser(myUserList);
	loginUser(myUserList);
	registerUser(myUserList);
	loginUser(myUserList);
}

//BCrypt::validatePassword