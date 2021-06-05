#pragma once
#include <iostream>
#include "Users.h"
#include "C:\Users\Cveti\source\repos\Recepies\Recepies\libbcrypt\include\bcrypt\BCrypt.hpp"
#include <stdlib.h>
#include <cctype>
#include <string>
#include "FoodGroup.h"
#include "ProductWithVolume.h"
#include "Recepies.h"
#include <fstream>
unsigned int CURR_LOGGED_USER = 0;

int intPow(int a, int b) {
	int result = 1;
	for (int i = 0; i < b; i++) {
		result *= a;
	}
	return result;
}

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
		|| areEqualCaseInsesitiveWords(command, "logout")
		|| areEqualCaseInsesitiveWords(command, "addrecepie")
		|| areEqualCaseInsesitiveWords(command, "changeRecepie")
		|| areEqualCaseInsesitiveWords(command, "deleteRecepie")
		|| areEqualCaseInsesitiveWords(command, "previewRecepie")
		|| areEqualCaseInsesitiveWords(command, "searchRecepie")
		|| areEqualCaseInsesitiveWords(command, "doRecepieReview")
		|| areEqualCaseInsesitiveWords(command, "getTopChart")
		|| areEqualCaseInsesitiveWords(command, "myProfil")
		|| areEqualCaseInsesitiveWords(command, "myRecepies")
		|| areEqualCaseInsesitiveWords(command, "myReviews");
		
}
//register = 0
//login = 1
//logout = 2
//addRecepie = 3
//changeRecepie = 4
//deleteRecepie = 5
//pregled = 6
//tyrsene = 7
//ocenka = 8
//spisyk = 9
//pregled na profil = 10
//pregled na recepti = 11
//pregled na ocenki = 12
//exit = 13
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
	if (areEqualCaseInsesitiveWords(command, "addRecepie")) {
		return 3;
	}
	if (areEqualCaseInsesitiveWords(command, "changeRecepie")) {
		return 4;
	}
	if (areEqualCaseInsesitiveWords(command, "deleteRecepie")) {
		return 5;
	}
	if (areEqualCaseInsesitiveWords(command, "previewRecepie")) {
		return 6;
	}
	if (areEqualCaseInsesitiveWords(command, "searchRecepie")) {
		return 7;
	}
	if (areEqualCaseInsesitiveWords(command, "doRecepieReview")) {
		return 8;
	}
	if (areEqualCaseInsesitiveWords(command, "getTopChart")) {
		return 9;
	}
	if (areEqualCaseInsesitiveWords(command, "myProfil")) {
		return 10;
	}
	if (areEqualCaseInsesitiveWords(command, "myRecepies")) {
		return 11;
	}
	if (areEqualCaseInsesitiveWords(command, "myReviews")) {
		return 12;
	}
	if (areEqualCaseInsesitiveWords(command, "exit")) {
		return 13;
	}
}

bool alreadyExistsUser(Users& myUsersList, std::string regName) {
	for (int i = 0; i < myUsersList.getSize(); i++) {
		if (myUsersList[i]->getName() == regName) {
			return true;
		}
	}
	return false;
}

bool alreadyExistsRecepie(Recepies& myRecepieList, std::string title) {
	for (int i = 0; i < myRecepieList.getSize(); i++) {
		if (myRecepieList[i]->getTitle() == title) {
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
		if (isValidUsername(regName) && !alreadyExistsUser(myUsersList, regName)) {
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
	std::ofstream oFile;
	oFile.open("users.db", std::ios::binary | std::ios::out | std::ios::app);
	regUser->serizalize(oFile);
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

int strToInt(std::string numberStr) {
	double number = 0;
	for (int i = 0; i < numberStr.size(); i++) {
		number += intPow(numberStr[i] - '0', numberStr.size() - i);
	}
	return number;
}

void addRecepie(Recepies& myRecepieList) {

	if (CURR_LOGGED_USER == 0) {
		std::cout << "You must log in to add recepie!" << std::endl;
		return;
	}
	std::string title;
	int foodGroup = 0;
	int timeToMake;
	std::vector<ProductWithVolume> products;
	std::string algorithm;
	std::string link;
	unsigned int numberOfFoodGroups;
	int foodGroupIndex;
	std::vector<Link> links;

	std::string product;
	std::string volumeStr;
	double volume;
	std::string unit;
	char space;
	unsigned int numberOfProducts;
	unsigned int numberOfLinks;

	std::cout << "Enter title: " << std::endl;
	
	while (true) {
		std::cin >> std::ws;
		std::getline(std::cin, title);
		if (!alreadyExistsRecepie(myRecepieList, title)) {
			break;
		}
		else {
			std::cout << "The title already exists.Enter again: " << std::endl;
		}
	}

	std::cout << "Enter how many groups of food will the recepie contain. Here is the list of groups: " << std::endl << "1. Vegetables" << std::endl << "2. Fruits" << std::endl << "3. Cereals" << std::endl << "4. Meat" << std::endl << "5. Seafood" << std::endl << "6. Dairy" << std::endl << "7. Eggs" << std::endl;
	while (true)
	{
		std::cin >> numberOfFoodGroups;
		if (numberOfFoodGroups < 8 && numberOfFoodGroups > 0) {
			break;
		}
		std::cout << "Invalid number of food groups. Enter again: " << std::endl;
	}
	
	for (int i = 0; i < numberOfFoodGroups; i++) {
		std::cout << "Enter index of food group you would like to add: " << std::endl;
		std::cin >> foodGroupIndex;
		if (foodGroupIndex > 7 || foodGroupIndex <= 0) {
			std::cout << "Invalid index." << std::endl;
			i--;
			continue;
		}
		if ((foodGroup & intPow(2, foodGroupIndex - 1)) != 0) {
			std::cout << "Group is already added." << std::endl;
			i--;
			continue;
		}
		foodGroup = foodGroup + intPow(2, foodGroupIndex);
	}
	
	std::cout << "Enter time to make: " << std::endl;
	while (true)
	{
		std::cin >> timeToMake;
		if (timeToMake > 0) {
			break;
		}
		std::cout << "Time must be positive.Eneter again: " << std::endl;
	}
	

	std::cout << "Enter number of products you would like to add: " << std::endl;
	
	while (true)
	{
		std::cin >> numberOfProducts;
		if (numberOfProducts > 0) {
			break;
		}
		std::cout << "Number of products must be positive.Eneter again: " << std::endl;
	}

	for (int i = 0; i < numberOfProducts; i++) {
		std::cout << "Enter products, volume and unit of measure in this format <name of product>, <volume>, <unit> :" << std::endl;
		std::cin >> std::ws;
		std::getline(std::cin, product, ',');
		std::cin >> std::ws;
		std::getline(std::cin, volumeStr, ',');
		std::cin >> unit;
		volume = std::stod(volumeStr);
		products.push_back(ProductWithVolume(product, volume, unit));
	}
	std::cout << "Enter algorithm with maximum 10000 symbols and at the end write '~': " << std::endl;
	std::cin >> std::ws;
	std::getline(std::cin, algorithm,'~');
	if (algorithm.length() > 10000) {
		algorithm.resize(10000);
	}

	std::cout << "Enter number of links you would like to add: " << std::endl;
	std::cin >> numberOfLinks;

	for (int i = 0; i < numberOfLinks; i++) {
		std::cout << "Enter link: " << std::endl;
		std::cin >> link;
		links.push_back(Link(link));
	}

	Recepie* toAddRecepie = new Recepie(title, foodGroup, timeToMake, products, algorithm, links, CURR_LOGGED_USER);
	std::ofstream oFile;
	oFile.open("recepies.db", std::ios::binary | std::ios::out | std::ios::app);
	toAddRecepie->serizalize(oFile);
	myRecepieList.addRecepie(toAddRecepie);
	std::cout << "Recepie added!";

}

void save(Recepies& myRecepieList) {
	std::ofstream oFile;
	oFile.open("recepies.db", std::ios::binary | std::ios::out);

	for (int i = 0; i < myRecepieList.getSize(); i++) {
		if (!myRecepieList[i]->isDeleted()) {
			myRecepieList[i]->serizalize(oFile);
		}
	}
}

void myProfil(Users& myUsersList) {
	if (CURR_LOGGED_USER == 0) {
		std::cout << "You must log in to view profil info";
		return;
	}
	myUsersList.getUserById(CURR_LOGGED_USER)->printInfo();
}

void myRecepies(Recepies& myRecepieList) {
	if (CURR_LOGGED_USER == 0) {
		std::cout << "You must log in to view profil info";
		return;
	}
	int recepieCounter = 1;
	for (int i = 0; i < myRecepieList.getSize(); i++) {
		if (myRecepieList[i]->getOwnerId() == CURR_LOGGED_USER) {
			std::cout << recepieCounter << ". " << myRecepieList[i]->getTitle() << std::endl;
			recepieCounter++;
		}
	}
}