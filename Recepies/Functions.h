#pragma once
#include "C:\Users\Cveti\source\repos\Recepies\Recepies\libbcrypt\include\bcrypt\BCrypt.hpp"
#include <iostream>
#include <stdlib.h>
#include <cctype>
#include <string>
#include <fstream>
#include "Users.h"
#include "FoodGroup.h"
#include "ProductWithVolume.h"
#include "Recepies.h"
#include "Ratings.h"

unsigned int CURR_LOGGED_USER = 0;

int intPow(int a, int b) {
	int result = 1;
	for (int i = 0; i < b; i++) {
		result *= a;
	}
	return result;
}

std::string toLowerLetters(std::string str) {
	std::string lower = "";
	for (char sign : str) {
		lower += tolower(sign);
	}
	return lower;
}
//https://www.cplusplus.com/reference/cctype/tolower/

bool areEqualCaseInsesitiveWords(std::string word1, std::string word2) {
	return toLowerLetters(word1) == toLowerLetters(word2);
}

bool containsString(std::string main, std::string check) {
	if (main.find(check) != std::string::npos) {
		return true;
	}
	return false;
}
//https://en.cppreference.com/w/cpp/string/basic_string/find

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
		|| areEqualCaseInsesitiveWords(command, "viewProfil")
		|| areEqualCaseInsesitiveWords(command, "myRecepies")
		|| areEqualCaseInsesitiveWords(command, "myReviews");
}

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
	if (areEqualCaseInsesitiveWords(command, "viewProfil")) {
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
	return -1;
}

bool alreadyExistsUser(Users& myUsersList, std::string regName) {
	for (int i = 0; i < myUsersList.getSize(); i++) {
		if (myUsersList[i]->getName() == regName) {
			return true;
		}
	}
	return false;
}

//da go mahna?
bool alreadyExistsRecepie(Recepies& myRecepieList, std::string title) {
	for (int i = 0; i < myRecepieList.getSize(); i++) {
		if (myRecepieList[i]->getTitle() == title) {
			return true;
		}
	}
	return false;
}

bool isValidUsername(std::string name) {
	for (char symbol : name) {
		if (!((symbol >= 'A' && symbol <= 'Z') || (symbol >= 'a' && symbol <= 'z') || symbol == '-' || symbol == '.' || symbol == '_')) {
			return false;
		}
	}
	return true;
}

bool containsCapitalLetter(std::string word) {
	for (char symbol : word) {
		if ((symbol >= 'A' && symbol <= 'Z')) {
			return true;
		}
	}
	return false;
}

//


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
		foodGroup = foodGroup + intPow(2, foodGroupIndex - 1);
	}
	
	std::cout << "Enter time to make in minutes: " << std::endl;
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
	std::getline(std::cin, algorithm, '~');
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
	std::cout << "Recepie added!" << std::endl;
	oFile.close();
}

void save(Recepies& myRecepieList) {
	std::ofstream oFile;
	oFile.open("recepies.db", std::ios::binary | std::ios::out);

	for (int i = 0; i < myRecepieList.getSize(); i++) {
		if (!myRecepieList[i]->isDeleted()) {
			myRecepieList[i]->serizalize(oFile);
		}
	}
	oFile.close();
}

void myProfil(Users& myUsersList) {
	if (CURR_LOGGED_USER == 0) {
		std::cout << "You must log in to view profil info" << std::endl;
		return;
	}
	myUsersList.getUserById(CURR_LOGGED_USER)->printInfo();
}

bool myRecepies(Recepies& myRecepieList) {
	if (CURR_LOGGED_USER == 0) {
		std::cout << "You must log in to view recepies." << std::endl;
		return false;
	}
	int recepieCounter = 1;
	for (int i = 0; i < myRecepieList.getSize(); i++) {
		if (myRecepieList[i]->getOwnerId() == CURR_LOGGED_USER && !myRecepieList[i]->isDeleted()) {
			std::cout << recepieCounter << ". " << myRecepieList[i]->getTitle() << " Id: " << myRecepieList[i]->getId() << std::endl;
			recepieCounter++;
		}
	}
	if (recepieCounter == 1) {
		std::cout << "No recepies to show!" << std::endl;
		return false;
	}
	return true;
}

void rateRecepie(Recepies& myRecepieList, Ratings& myRatingsList) {
	if (CURR_LOGGED_USER == 0) {
		std::cout << "You must log in to rate recepie!" << std::endl;
		return;
	}
	bool hasRecepiesToRate = false;
	for (int i = 0; i < myRecepieList.getSize(); i++) {
		if (!myRecepieList[i]->isDeleted() && myRecepieList[i]->getOwnerId() != CURR_LOGGED_USER) {
			hasRecepiesToRate = true;
		}
	}
	if (!hasRecepiesToRate) {
		std::cout << "There are no recepies you can review" << std::endl;
		return;
	}
	myRecepieList.print();
	std::cout << "Enter recepie Id you would like to rate: " << std::endl;
	int recepieId;
	
	while (true) {
		std::cin >> recepieId;
		if (!myRecepieList.getRecepieById(recepieId)) {
			std::cout << "Recepie doesn't exist. Enter again: " << std::endl;
			continue;
		}
		if (myRecepieList.getRecepieById(recepieId)->isDeleted()) {
			std::cout << "Recepie is deleted. Enter again: " << std::endl;
			continue;
		}
		if (myRecepieList.getRecepieById(recepieId)->getOwnerId() == CURR_LOGGED_USER) {
			std::cout << "Cant rate own recepie. Enter again: " << std::endl;
			continue;
		}
		if (myRatingsList.existRating(CURR_LOGGED_USER, recepieId)) {
			std::cout << "Cant rate recepie twice. Enter again: " << std::endl;
			continue;
		}
		break;
	}
	std::cout << "Enter rate value between [1, 5]: " << std::endl;
	int value;
	
	while (true) {
		std::cin >> value;
		if (value > 0 && value < 6) {
			break;
		}
		else {
			std::cout << "Invalid rating value. Enter again: " << std::endl;
		}
	}

	Rating* toAdd = new Rating(value, recepieId, CURR_LOGGED_USER);
	myRatingsList.addRating(toAdd);


	std::ofstream oFile;
	oFile.open("ratings.db", std::ios::binary | std::ios::out | std::ios::app);
	toAdd->serizalize(oFile);
	std::cout << "Rating added!" << std::endl;
	myRecepieList.getRecepieById(recepieId)->calculateRating(myRatingsList);
	oFile.close();
}

void printUserRatings(int userId, Recepies& myRecepiesList, Ratings& myRatingList) {
	if (CURR_LOGGED_USER == 0) {
		std::cout << "You must log in to see your reviews." << std::endl;
		return;
	}
	int index = 1;
	for (int i = 0; i < myRatingList.getSize(); i++) {
		if (myRatingList[i]->getUserId() == userId) {
			std::cout << index << ". " << myRecepiesList.getRecepieById(myRatingList[i]->getRecepieId())->getTitle() << std::endl << "Rating value: " << myRatingList[i]->getValue() << std::endl << "Recepie id: " << myRatingList[i]->getRecepieId() << std::endl;
			index++;
		}
	}
	if (index == 1) {
		std::cout << "No Reviews to show!" << std::endl;
	}
}

void searchByName(Recepies& myRecepiesList) {
	int counter = 1;
	std::string searchedName;
	std::cout << "Enter search: " << std::endl;
	std::cin >> std::ws;
	std::getline(std::cin, searchedName, '\n');
	std::vector<Recepie*> tempVec;
	for (int i = 0; i < myRecepiesList.getSize(); i++) {
		if (!myRecepiesList[i]->isDeleted() && containsString(toLowerLetters(myRecepiesList[i]->getTitle()), toLowerLetters(searchedName))) {
			std::cout << counter << ". " << myRecepiesList[i]->getTitle() << " Id: " << myRecepiesList[i]->getId() << std::endl;
			counter++;
			tempVec.push_back(myRecepiesList[i]);
		}
	}
	if (counter == 1) {
		std::cout << "No recepies match this search. " << std::endl;
		return;
	}
	int searchId;
	std::cout << "Enter Id of recepie you would like to view: " << std::endl;
	while (true) {
		std::cin >> searchId;
		bool valid = false;
		for (int i = 0; i < tempVec.size(); i++) {
			if (searchId == tempVec[i]->getId()) {
				tempVec[i]->printAllInfo();
				myRecepiesList.getRecepieById(tempVec[i]->getId())->visit();
				return;
			}
		}
		std::cout << "Invalid Id. Enter again: " << std::endl;
	}
	
}

void viewProfil(Users& myUsersList, Recepies& myRecepieList) {
	int searchedId;
	int counter = 1;
	for (int i = 0; i < myUsersList.getSize(); i++) {
		std::cout << counter << ". " << myUsersList[i]->getName() << "  Id: " << myUsersList[i]->getId() << std::endl;
		counter++;
	}
	std::cout << "Enter Id of user you want to see info about." << std::endl;
	while (true) {
		std::cin >> searchedId;
		if (!myUsersList.getUserById(searchedId)) {
			std::cout << "No user with this id exists.Enter again: " << std::endl;
			continue;
		}
		break;
	}


	myUsersList.getUserById(searchedId)->printInfo();
	bool hasRecepies = false;
	for (int i = 0; i < myRecepieList.getSize(); i++) {
		
		if (myRecepieList[i]->getOwnerId() == searchedId) {
			if (!hasRecepies) {
				std::cout << "Recepies: " << std::endl;
				hasRecepies = true;
			}
			myRecepieList[i]->printTitle();
		}
	}
	if (!hasRecepies) {
		std::cout << "No recepies to show." << std::endl;
	}
}

void deleteRecepie(Recepies& myRecepieList) {
	int idToDelete;
	if (CURR_LOGGED_USER == 0) {
		std::cout << "You must login to delete recepie." << std::endl;
		return;
	}
	if (!myRecepies(myRecepieList)) {
		return;
	}
	std::cout << "Enter Id of recepie you would like to delete: " << std::endl;
	while (true) {
		std::cin >> idToDelete;
		if (!myRecepieList.getRecepieById(idToDelete)) {
			std::cout << "Recepie doesn't exist. Enter again: " << std::endl;
			continue;
		}
		if (myRecepieList.getRecepieById(idToDelete)->isDeleted() || myRecepieList.getRecepieById(idToDelete)->getOwnerId() != CURR_LOGGED_USER) {
			std::cout << "Recepie doesn't exist or it doesn't belong to you. Enter again: " << std::endl;
			continue;
		}
		break;
	}
	myRecepieList.getRecepieById(idToDelete)->deleteRecepie();
	std::cout << "Recepie deleted! " << std::endl;

}

void changeFoodGroup(int groups, int numberOfFoodGroups, int foodGroupIndex, Recepies& myRecepieList, int idToChange) {
	std::vector<int> currGroups;
	std::cout << "Current groups are: " << std::endl;
	if ((groups & 1) != 0) {
		std::cout << numberOfFoodGroups << ". Vegetables" << std::endl;
		numberOfFoodGroups++;
		currGroups.push_back(1);
	}
	if ((groups & 2) != 0) {
		std::cout << numberOfFoodGroups << ". Fruits" << std::endl;
		numberOfFoodGroups++;
		currGroups.push_back(2);

	}
	if ((groups & 4) != 0) {
		std::cout << numberOfFoodGroups << ". Cereals" << std::endl;
		numberOfFoodGroups++;
		currGroups.push_back(4);

	}
	if ((groups & 8) != 0) {
		std::cout << numberOfFoodGroups << ". Meat" << std::endl;
		numberOfFoodGroups++;
		currGroups.push_back(8);

	}
	if ((groups & 16) != 0) {
		std::cout << numberOfFoodGroups << ". Seafood" << std::endl;
		numberOfFoodGroups++;
		currGroups.push_back(16);

	}
	if ((groups & 32) != 0) {
		std::cout << numberOfFoodGroups << ". Dairy" << std::endl;
		numberOfFoodGroups++;
		currGroups.push_back(32);

	}
	if ((groups & 64) != 0) {
		std::cout << numberOfFoodGroups << ". Eggs" << std::endl;
		numberOfFoodGroups++;
		currGroups.push_back(64);

	}
	if (numberOfFoodGroups == 2) {
		std::cout << "List of groups: " << std::endl
			<< "1. Vegetables" << std::endl
			<< "2. Fruits" << std::endl
			<< "3. Cereals" << std::endl
			<< "4. Meat" << std::endl
			<< "5. Seafood" << std::endl
			<< "6. Dairy" << std::endl
			<< "7. Eggs" << std::endl;

		std::cout << "Enter index of food group you would like to add: " << std::endl;

		while (true) {
			std::cin >> foodGroupIndex;
			if (foodGroupIndex > 7 || foodGroupIndex <= 0) {
				std::cout << "Invalid index. Enter again: " << std::endl;
				continue;
			}
			if ((groups & intPow(2, foodGroupIndex - 1)) != 0) {
				std::cout << "Group is already added. Enter again: " << std::endl;
				continue;
			}
			break;
		}
		myRecepieList.getRecepieById(idToChange)->addFoodGroup(foodGroupIndex);
		return;
	}

	if (numberOfFoodGroups == 8) {
		std::cout << "List of groups: " << std::endl
			<< "1. Vegetables" << std::endl
			<< "2. Fruits" << std::endl
			<< "3. Cereals" << std::endl
			<< "4. Meat" << std::endl
			<< "5. Seafood" << std::endl
			<< "6. Dairy" << std::endl
			<< "7. Eggs" << std::endl;

		std::cout << "Enter index of food group you would like to delete: " << std::endl;

		while (true) {
			std::cin >> foodGroupIndex;
			if (foodGroupIndex > 7 || foodGroupIndex <= 0) {
				std::cout << "Invalid index. Enter again: " << std::endl;
				continue;
			}
			break;
		}
		myRecepieList.getRecepieById(idToChange)->removeFoodGroup(foodGroupIndex);
		return;
	}
	std::cout << "Do you want to delete or add food group?" << std::endl;
	std::string command;
	while (true) {
		std::cin >> command;
		if (areEqualCaseInsesitiveWords(command, "delete")) {
			std::cout << "Enter index of food group you would like to delete: " << std::endl;
			while (true) {
				std::cin >> foodGroupIndex;
				if ( foodGroupIndex > numberOfFoodGroups - 1 || foodGroupIndex <= 0) {
					std::cout << "Invalid index. Enter again: " << std::endl;
					continue;
				}
				break;
			}
			myRecepieList.getRecepieById(idToChange)->setFoodGroup(currGroups[numberOfFoodGroups - 2]);
			return;
		}
		if(areEqualCaseInsesitiveWords(command, "add")) {
			std::cout << "List of groups: " << std::endl
				<< "1. Vegetables" << std::endl
				<< "2. Fruits" << std::endl
				<< "3. Cereals" << std::endl
				<< "4. Meat" << std::endl
				<< "5. Seafood" << std::endl
				<< "6. Dairy" << std::endl
				<< "7. Eggs" << std::endl;

			std::cout << "Enter index of food group you would like to add: " << std::endl;

			while (true) {
				std::cin >> foodGroupIndex;
				if (foodGroupIndex > 7 || foodGroupIndex <= 0) {
					std::cout << "Invalid index. Enter again: " << std::endl;
					continue;
				}
				if ((groups & intPow(2, foodGroupIndex - 1)) != 0) {
					std::cout << "Group is already added. Enter again: " << std::endl;
					continue;
				}
				break;
			}
			myRecepieList.getRecepieById(idToChange)->addFoodGroup(foodGroupIndex);
			return;
		}
		std::cout << "Invalid command. Enter again: " << std::endl;
	}
	

}

void changeProducts(Recepies& myRecepieList, int idToChange) {
	std::string product;
	std::string volumeStr;
	std::string unit;
	int volume;

	int numberOfProducts = 1;
	std::cout << "Current products are: " << std::endl;
	int deleteIndex;

	for (int i = 0; i < myRecepieList.getRecepieById(idToChange)->getProductList().size(); i++) {
		if (!myRecepieList.getRecepieById(idToChange)->getProductList()[i].isDeleted()) {
			std::cout << numberOfProducts << ". " << myRecepieList.getRecepieById(idToChange)->getProductList()[i].getProduct() << std::endl;
			numberOfProducts++;
		}
	}

	if (numberOfProducts == 2) {
		std::cout << "Enter product, volume and unit of measure of the product you would like to add in this format <name of product>, <volume>, <unit> :" << std::endl;
		std::cin >> std::ws;
		std::getline(std::cin, product, ',');
		std::cin >> std::ws;
		std::getline(std::cin, volumeStr, ',');
		std::cin >> unit;
		volume = std::stod(volumeStr);
		ProductWithVolume toAdd(product, volume, unit);
		myRecepieList.getRecepieById(idToChange)->addProduct(toAdd);
		return;
	}

	std::cout << "Do you want to delete or add product?" << std::endl;
	std::string command;
	while (true) {
		std::cin >> command;
		if (areEqualCaseInsesitiveWords(command, "delete")) {
			std::cout << "Enter index of product you would like to delete: " << std::endl;
			while (true) {
				std::cin >> deleteIndex;
				if (deleteIndex > numberOfProducts - 1 || deleteIndex <= 0) {
					std::cout << "Invalid index. Enter again: " << std::endl;
					continue;
				}
				break;
			}
			deleteIndex-=1;
			for (int i = 0; i <= deleteIndex; i++) {
				if (myRecepieList.getRecepieById(idToChange)->getProductList()[i].isDeleted()) {
					deleteIndex++;
				}
			}
			myRecepieList.getRecepieById(idToChange)->deleteProduct(deleteIndex);
			return;
		}
		if (areEqualCaseInsesitiveWords(command, "add")) {
			std::cout << "Enter product, volume and unit of measure of the product you would like to add in this format <name of product>, <volume>, <unit> :" << std::endl;
			std::cin >> std::ws;
			std::getline(std::cin, product, ',');
			std::cin >> std::ws;
			std::getline(std::cin, volumeStr, ',');
			std::cin >> unit;
			volume = std::stod(volumeStr);
			ProductWithVolume toAdd(product, volume, unit);
			myRecepieList.getRecepieById(idToChange)->addProduct(toAdd);
			return;
		}
		std::cout << "Invalid command. Enter again: " << std::endl;
	}
}

void changeLinks(Recepies& myRecepieList, int idToChange) {
	std::string link;

	int numberOfLinks = 1;
	std::cout << "Current links are: " << std::endl;
	int deleteIndex;

	for (int i = 0; i < myRecepieList.getRecepieById(idToChange)->getLinksList().size(); i++) {
		if (!myRecepieList.getRecepieById(idToChange)->getLinksList()[i].isDeleted()) {
			std::cout << numberOfLinks << ". ";
			myRecepieList.getRecepieById(idToChange)->getLinksList()[i].print();
			numberOfLinks++;
		}
	}

	if (numberOfLinks == 2) {
		std::cout << "Enter link thet you would like to be added: " << std::endl;
		std::cin >> link;
		Link toAdd(link);
		myRecepieList.getRecepieById(idToChange)->addLink(toAdd);
		return;
	}

	std::cout << "Do you want to delete or add product?" << std::endl;
	std::string command;
	while (true) {
		std::cin >> command;
		if (areEqualCaseInsesitiveWords(command, "delete")) {
			std::cout << "Enter index of link you would like to delete: " << std::endl;
			while (true) {
				std::cin >> deleteIndex;
				if (deleteIndex > numberOfLinks - 1 || deleteIndex <= 0) {
					std::cout << "Invalid index. Enter again: " << std::endl;
					continue;
				}
				break;
			}
			deleteIndex -= 1;
			for (int i = 0; i <= deleteIndex; i++) {
				if (myRecepieList.getRecepieById(idToChange)->getLinksList()[i].isDeleted()) {
					deleteIndex++;
				}
			}
			myRecepieList.getRecepieById(idToChange)->removeLink(deleteIndex);
			return;
		}
		if (areEqualCaseInsesitiveWords(command, "add")) {
			std::cout << "Enter link thet you would like to be added: " << std::endl;
			std::cin >> link;
			Link toAdd(link);
			myRecepieList.getRecepieById(idToChange)->addLink(toAdd);
			return;
		}
		std::cout << "Invalid command. Enter again: " << std::endl;
	}
}

void changeRecepie(Recepies& myRecepieList) {
	int idToChange = -1;
	if (CURR_LOGGED_USER == 0) {
		std::cout << "You must log in to view recepies." << std::endl;
		return;
	}
	if (!myRecepies(myRecepieList)) {
		return;
	}
	std::cout << "Enter Id of recepie you would like to change: " << std::endl;
	while (true) {
		std::cin >> idToChange;
		if (!myRecepieList.getRecepieById(idToChange)) {
			std::cout << "Recepie doesn't exist. Enter again: " << std::endl;
			continue;
		}
		if (myRecepieList.getRecepieById(idToChange)->isDeleted() || myRecepieList.getRecepieById(idToChange)->getOwnerId() != CURR_LOGGED_USER) {
			std::cout << "Recepie doesn't exist or it doesn't belong to you. Enter again: " << std::endl;
			continue;
		}
		break;
	}
	int changeItem = 0;

	/*std::string _title;
	int _foodGroup;
	int _timeToMake;
	std::vector<ProductWithVolume> _products;
	std::string _algorithm;
	std::vector<Link> _links;*/
	std::cout << "List of changeable values: " << std::endl
		<< "1. Title" << std::endl
		<< "2. Food groups" << std::endl
		<< "3. Time to make" << std::endl
		<< "4. Products" << std::endl
		<< "5. Algorithm" << std::endl
		<< "6. links" << std::endl 
		<< "Enter index of value you want to change: " << std::endl;

	while (true) {
		std::cin >> changeItem;
		if (changeItem > 0 && changeItem < 7) {
			break;
		}
		std::cout << "Invalid index.Enter again: " << std::endl;
	}

	std::string newValue;
	int newValueInt = -1;
	int foodGroupIndex = -1;
	int groups = myRecepieList.getRecepieById(idToChange)->getFoodGroup();
	int numberOfFoodGroups = 1;
	switch (changeItem)
	{
	case 1:
		std::cout << "Enter new title: " << std::endl;
		std::cin >> std::ws;
		std::getline(std::cin, newValue, '\n');
		myRecepieList.getRecepieById(idToChange)->setTitle(newValue);
		break;
	case 2:
		changeFoodGroup(groups, numberOfFoodGroups, foodGroupIndex, myRecepieList, idToChange);
		break;
	case 3:
		while (true) {
			std::cin >> newValueInt;
			if (newValueInt <= 0) {
				std::cout << "Invalid value. Enter again: " << std::endl;
				continue;
			}
			break;
		}
		myRecepieList.getRecepieById(idToChange)->setTimeToMake(newValueInt);
		break;
	case 4:
		changeProducts(myRecepieList, idToChange);
		break;
	case 5:
		std::cout << "Enter algorithm with maximum 10000 symbols and at the end write '~': " << std::endl;
		std::cin >> std::ws;
		std::getline(std::cin, newValue, '\n');
		if (newValue.length() > 10000) {
			newValue.resize(10000);
		}
		myRecepieList.getRecepieById(idToChange)->setAlgorithm(newValue);
		break;
	case 6:
		changeLinks(myRecepieList, idToChange);
		break;
	default:
		break;
	}
}

void previewRecepie(Recepies& myRecepieList) {
	if (myRecepieList.isEmpty()) {
		std::cout << "There are no existing recepies." << std::endl;
	}
	int searchedId;
	int counter = 1;
	for (int i = 0; i < myRecepieList.getSize(); i++) {
		std::cout << counter << ". " << myRecepieList[i]->getTitle() << "  Id: " << myRecepieList[i]->getId() << std::endl;
		counter++;
	}
	std::cout << "Enter Id of recepie you want to see info about." << std::endl;
	while (true) {
		std::cin >> searchedId;
		if (!myRecepieList.getRecepieById(searchedId)) {
			std::cout << "No recepie with this id exists.Enter again: " << std::endl;
			continue;
		}
		break;
	}


	myRecepieList.getRecepieById(searchedId)->printAllInfo();

}

void getTopChart(Recepies& myRecepieList) {
	if (myRecepieList.isEmpty()) {
		std::cout << "There are no recepies." << std::endl;
		return;
	}
	int n;
	std::string typeOfChart;
	std::cout << "Enter number of recepies: " << std::endl;
	while (true) {
		std::cin >> n;
		if (n > 0) {
			break;
		}
		std::cout << "Number must be atleast 1. Enter again: " << std::endl;
	}
	std::cout << "Enter type of chart popular rated or recent: " << std::endl;
	while (true) {
		std::cin >> typeOfChart;
		if (areEqualCaseInsesitiveWords(typeOfChart, "popular")) {
			std::vector<Recepie*> toSort = myRecepieList.getRecepieList();
			int maxPopularity = myRecepieList[0]->getTimesVisited();
			for (int i = 0; i < myRecepieList.getSize() - 1; i++) {
				if (toSort[i]->getTimesVisited() < toSort[i + 1]->getTimesVisited()) {
					Recepie* temp = toSort[i];
					toSort[i] = toSort[i + 1];
					toSort[i + 1] = temp;
				}
			}
			int counter = 1;
			for (int i = 0; i < n; i++) {
				if (!myRecepieList[i]) {
					return;
				}
				if (!toSort[i]->isDeleted()) {
					std::cout << counter << ". ";
					toSort[i]->printTitle();
				}
			}
			return;
		}
		if (areEqualCaseInsesitiveWords(typeOfChart, "rated")) {
			std::vector<Recepie*> toSort = myRecepieList.getRecepieList();
			int maxPopularity = myRecepieList[0]->getTimesVisited();
			for (int i = 0; i < myRecepieList.getSize() - 1; i++) {
				if (toSort[i]->getRating() < toSort[i + 1]->getRating()) {
					Recepie* temp = toSort[i];
					toSort[i] = toSort[i + 1];
					toSort[i + 1] = temp;
				}
			}
			int counter = 1;
			for (int i = 0; i < n; i++) {
				if (!myRecepieList[i]) {
					return;
				}
				if (!toSort[i]->isDeleted()) {
					std::cout << counter << ". ";
					toSort[i]->printTitle();
				}
			}
			return;
		}
		if (areEqualCaseInsesitiveWords(typeOfChart, "recent")) {
			std::vector<Recepie*> toSort = myRecepieList.getRecepieList();
			int maxPopularity = myRecepieList[0]->getTimesVisited();
			for (int i = 0; i < myRecepieList.getSize() - 1; i++) {
				if (toSort[i]->getAddTime() < toSort[i + 1]->getAddTime()) {
					Recepie* temp = toSort[i];
					toSort[i] = toSort[i + 1];
					toSort[i + 1] = temp;
				}
			}
			int counter = 1;
			for (int i = 0; i < n; i++) {
				if (!myRecepieList[i]) {
					return;
				}
				if (!toSort[i]->isDeleted()) {
					std::cout << counter << ". ";
					toSort[i]->printTitle();
				}
			}
			return;
		}
		std::cout << "Invalid type. Enter again: " << std::endl;
	}
}