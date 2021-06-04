#pragma once
#include <iostream>
#include "Users.h"
#include "C:\Users\Cveti\source\repos\Recepies\Recepies\libbcrypt\include\bcrypt\BCrypt.hpp"
#include <stdlib.h>

unsigned int CURR_LOGGED_USER = 0;

void registerUser(Users& myUsersList) {
	std::cout << "Enter username , email and password!" << std::endl;
	int mySize = myUsersList.getSize();
	std::string regName;
	std::cin >> regName;
	for (int i = 0; i < mySize; i++) {
		if (myUsersList[i]->getName() == regName) {
			std::cout << "This user already exists." << std::endl;
			return;
		}
	}
	std::string regPass;
	std::cin >> regPass;
	std::string regHash = BCrypt::generateHash(regPass);
	//std::cout << "hash :" << regHash << std::endl;
	User* regUser = new User(regName, regHash);
	regUser->serizalize();
	myUsersList.addUser(regUser);
	std::cout << "User saved!" << std::endl;
}

void loginUser(Users& myUsersList) {
	int mySize = myUsersList.getSize();
	std::cout << "Enter username and password:" << std::endl;
	std::string loginName;
	std::cin >> loginName;
	for (int i = 0; i < mySize; i++) {
		if (myUsersList[i]->getName() == loginName) {
			std::cout << "enter password:" << std::endl;
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