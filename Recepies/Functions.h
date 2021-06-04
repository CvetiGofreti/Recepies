#pragma once
#include <iostream>
#include "Users.h"
#include "C:\Users\Cveti\source\repos\Recepies\Recepies\libbcrypt\include\bcrypt\BCrypt.hpp"
#include <stdlib.h>
#include <cctype>
#include <string>

unsigned int CURR_LOGGED_USER = 0;



bool areEqualCaseInsesitiveWords(std::string word1, std::string word2) {
	if (word1.length() != word2.length()) {
		return false;
	}
	for (int i = 0; i < word1.length(); i++) {
		if (tolower(word1[i]) != tolower(word2[i])) {
			return false;
		}
	}
	return true;
}
//https://stackoverflow.com/questions/11635/case-insensitive-string-comparison-in-c
//https://www.cplusplus.com/reference/cctype/tolower/

bool isValidCommand(std::string command) {
	return areEqualCaseInsesitiveWords(command, "login")
		|| areEqualCaseInsesitiveWords(command, "register")
		|| areEqualCaseInsesitiveWords(command, "exit")
		|| areEqualCaseInsesitiveWords(command, "logout");
		
}
//register = 0
//login = 1
//logout = 2
//addRecepie = 4
//changeRecepie = 5
//deleteRecepie = 6
//pregled = 7
//tyrsene 8
//ocenka9
//spisyk10
//pregled na profil11
//pregled na recepti12
//pregled na ocenki13
//exit 14
int indexOfCommandfunc(std::string command) {
	if (areEqualCaseInsesitiveWords(command, "register")) {
		return 0;
	}
	if (areEqualCaseInsesitiveWords(command, "login")) {
		return 1;
	}
	if (areEqualCaseInsesitiveWords(command, "logout")) {
		return 2;
	}
	if (areEqualCaseInsesitiveWords(command, "exit")) {
		return 14;
	}
}

bool alreadyExists(Users& myUsersList, std::string regName) {
	for (int i = 0; i < myUsersList.getSize(); i++) {
		if (myUsersList[i]->getName() == regName) {
			return true;
		}
	}
	return false;
}

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

bool containsNumber(std::string word) {
	bool contains = false;
	for (char symbol : word) {
		if ((symbol >= '0' && symbol <= '9')) {
			contains = true;
		}
	}
	return contains;
}

bool isValidPassword(std::string password) {
	return containsNumber(password) && containsCapitalLetter(password) && containsNumber(password);
}

void registerUser(Users& myUsersList) {
	if (CURR_LOGGED_USER != 0) {
		std::cout << "User " << myUsersList.getUserById(CURR_LOGGED_USER)->getName() << " is logged in at the moment.Log out to register user. " << std::endl;
		return;
	}
	std::string regName;
	std::cout << "Enter username: " << std::endl;
	while (true) {
		std::cin >> regName;
		if (isValidUsername(regName) && !alreadyExists(myUsersList, regName)) {
			break;
		}
		else {
			std::cout << "The name is invalid or it already exists.Enter again: " << std::endl;
		}
	}
	std::cout << "Enter password: " << std::endl;
	std::string regPass;
	while (true) {
		std::cin >> regPass;
		if (isValidPassword(regPass)) {
			break;
		}
		else {
			std::cout << "The password is invalid.Enter again: " << std::endl;
		}
	}
	std::string regHash = BCrypt::generateHash(regPass);
	//std::cout << "hash :" << regHash << std::endl;
	User* regUser = new User(regName, regHash);
	regUser->serizalize();
	myUsersList.addUser(regUser);
	std::cout << "User saved!" << std::endl;
}

void loginUser(Users& myUsersList) {
	if (CURR_LOGGED_USER != 0) {
		std::cout << "User " << myUsersList.getUserById(CURR_LOGGED_USER)->getName() << " is logged in at the moment.Log out to login another user. " << std::endl;
		return;
	}
	int mySize = myUsersList.getSize();
	std::cout << "Enter username:" << std::endl;
	std::string loginName;
	std::cin >> loginName;
	for (int i = 0; i < mySize; i++) {
		if (myUsersList[i]->getName() == loginName) {
			std::cout << "Enter password:" << std::endl;
			std::string loginPass;
			std::cin >> loginPass;
			if (BCrypt::validatePassword(loginPass, myUsersList[i]->getHash())) {
				std::cout << "Login succesful!" << std::endl;
				CURR_LOGGED_USER = myUsersList[i]->getId();
			}
			else {
				std::cout << "Wrong Password!" << std::endl;
			}
			return;
		}
	}
	std::cout << "This user is not registered." << std::endl;
}

void logoutUser() {
	if (CURR_LOGGED_USER == 0) {
		std::cout << "No user is currently logged in." << std::endl;
		return;
	}
	CURR_LOGGED_USER = 0;
	std::cout << "Logout succesfull!" << std::endl;
}