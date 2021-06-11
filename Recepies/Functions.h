#pragma once
#include "C:\Users\Cveti\source\repos\Recepies\Recepies\libbcrypt\include\bcrypt\BCrypt.hpp"
#include <iostream>
#include <stdlib.h>
#include <cctype>
#include <string>
#include <fstream>
#include <iomanip>
#include "Users.h"
#include "FoodGroup.h"
#include "ProductWithVolume.h"
#include "Recipes.h"
#include "Ratings.h"

unsigned int CURR_LOGGED_USER = 0;

void printCommands() {
	std::cout << "=========Commands=========" << std::endl;
	std::cout << "1.  Login - to login" << std::endl
		<< "2.  Register - to register" << std::endl
		<< "3.  Exit - to exit and save all changes" << std::endl
		<< "4.  Logout - to logout" << std::endl
		<< "5.  AddRecipe - to add recipe" << std::endl
		<< "6.  ChangeRecipe - to change recipe" << std::endl
		<< "7.  DeleteRecipe - to delete recipe" << std::endl
		<< "8.  PreviewRecipe - to see list of all recipes and choose one to see all recipe info" << std::endl
		<< "9.  SearchRecipe - to search name of recipe" << std::endl
		<< "10. DoRecipeReview - to see list of all recipes and choose one to review" << std::endl
		<< "11. GetTopChart- to get top popular|rated|recent recipes" << std::endl
		<< "12. ViewProfil - search profil and see info about it" << std::endl
		<< "13. MyRecipes - to see your recipes" << std::endl
		<< "14. MyReviews - to see the reviews you made" << std::endl
		<< "==========================" << std::endl;
}

int intPow(int a, int b) {
	int result = 1;
	for (int i = 0; i < b; i++) {
		result *= a;
	}
	return result;
}

//https://www.cplusplus.com/reference/cctype/tolower/
std::string toLowerLetters(std::string str) {
	std::string lower = "";
	for (char sign : str) {
		lower += tolower(sign);
	}
	return lower;
}


bool areEqualCaseInsesitiveWords(std::string word1, std::string word2) {
	return toLowerLetters(word1) == toLowerLetters(word2);
}

//https://en.cppreference.com/w/cpp/string/basic_string/find
bool containsString(std::string main, std::string check) {
	if (main.find(check) != std::string::npos) {
		return true;
	}
	return false;
}


bool isValidCommand(std::string command) {
	return areEqualCaseInsesitiveWords(command, "login")
		|| areEqualCaseInsesitiveWords(command, "register")
		|| areEqualCaseInsesitiveWords(command, "exit")
		|| areEqualCaseInsesitiveWords(command, "logout")
		|| areEqualCaseInsesitiveWords(command, "addrecipe")
		|| areEqualCaseInsesitiveWords(command, "changeRecipe")
		|| areEqualCaseInsesitiveWords(command, "deleteRecipe")
		|| areEqualCaseInsesitiveWords(command, "previewRecipe")
		|| areEqualCaseInsesitiveWords(command, "searchRecipe")
		|| areEqualCaseInsesitiveWords(command, "doRecipeReview")
		|| areEqualCaseInsesitiveWords(command, "getTopChart")
		|| areEqualCaseInsesitiveWords(command, "viewProfil")
		|| areEqualCaseInsesitiveWords(command, "myRecipes")
		|| areEqualCaseInsesitiveWords(command, "myReviews") 
		|| areEqualCaseInsesitiveWords(command, "commands");
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
	if (areEqualCaseInsesitiveWords(command, "addRecipe")) {
		return 3;
	}
	if (areEqualCaseInsesitiveWords(command, "changeRecipe")) {
		return 4;
	}
	if (areEqualCaseInsesitiveWords(command, "deleteRecipe")) {
		return 5;
	}
	if (areEqualCaseInsesitiveWords(command, "previewRecipe")) {
		return 6;
	}
	if (areEqualCaseInsesitiveWords(command, "searchRecipe")) {
		return 7;
	}
	if (areEqualCaseInsesitiveWords(command, "doRecipeReview")) {
		return 8;
	}
	if (areEqualCaseInsesitiveWords(command, "getTopChart")) {
		return 9;
	}
	if (areEqualCaseInsesitiveWords(command, "viewProfil")) {
		return 10;
	}
	if (areEqualCaseInsesitiveWords(command, "myRecipes")) {
		return 11;
	}
	if (areEqualCaseInsesitiveWords(command, "myReviews")) {
		return 12;
	}
	if (areEqualCaseInsesitiveWords(command, "exit")) {
		return 13;
	}
	if (areEqualCaseInsesitiveWords(command, "commands")) {
		return 14;
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

bool containsSmalllLetter(std::string word) {
	for (char symbol : word) {
		if ((symbol >= 'a' && symbol <= 'z')) {
			return true;
		}
	}
	return false;
}

bool containsNumber(std::string word) {
	for (char symbol : word) {
		if ((symbol >= '0' && symbol <= '9')) {
			return true;
		}
	}
	return false;
}

bool isValidPassword(std::string password) {
	return password.length() >= 8 && containsNumber(password) && containsCapitalLetter(password) && containsNumber(password);
}

void registerUser(Users& myUsersList) {
	if (CURR_LOGGED_USER != 0) {
		std::cout << "User " << myUsersList.getUserById(CURR_LOGGED_USER)->getName() << " is logged in at the moment.Log out to register user. " << std::endl;
		return;
	}
	std::string regName;
	std::cout << "Enter username. Username can only contain small and capital letters, numbers, '-', '_', or '.' : " << std::endl;
	while (true) {
		std::cin >> regName;
		if (isValidUsername(regName) && !alreadyExistsUser(myUsersList, regName)) {
			break;
		}
		else {
			std::cout << "The name is invalid or it already exists.Enter again: " << std::endl;
		}
	}
	std::cout << "Enter password. Password must be at least 8 symbols and must contain at least 1 small letter, 1 capital letter and 1 number: " << std::endl;
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
	std::cout << "User registered successfully!" << std::endl;
}

void loginUser(Users& myUsersList) {
	if (CURR_LOGGED_USER != 0) {
		std::cout << "User " << myUsersList.getUserById(CURR_LOGGED_USER)->getName() << " is logged in at the moment.Log out to login another user. " << std::endl;
		return;
	}
	if (myUsersList.isEmpty()) {
		std::cout << "No users registered yet. " << std::endl;
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

//https://en.cppreference.com/w/cpp/io/manip/ws
void addRecipe(Recipes& myRecipeList) {
	if (CURR_LOGGED_USER == 0) {
		std::cout << "You must log in to add recipe!" << std::endl;
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
	std::cin >> std::ws;
	std::getline(std::cin, title);


	std::cout << "Enter how many groups of food will the recipe contain. Here is the list of groups: " << std::endl << "1. Vegetables" << std::endl << "2. Fruits" << std::endl << "3. Cereals" << std::endl << "4. Meat" << std::endl << "5. Seafood" << std::endl << "6. Dairy" << std::endl << "7. Eggs" << std::endl;
	while (true) {
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
	while (true) {
		std::cin >> timeToMake;
		if (timeToMake > 0) {
			break;
		}
		std::cout << "Time must be positive.Eneter again: " << std::endl;
	}
	
	std::cout << "Enter number of products you would like to add: " << std::endl;
	while (true) {
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
	while (true) {
		std::cin >> numberOfLinks;
		if (numberOfLinks > 0) {
			break;
		}
		std::cout << "Number of links must be positive.Eneter again: " << std::endl;
	}

	for (int i = 0; i < numberOfLinks; i++) {
		std::cout << "Enter link: " << std::endl;
		std::cin >> link;
		links.push_back(Link(link));
	}

	Recipe* toAddRecipe = new Recipe(title, foodGroup, timeToMake, products, algorithm, links, CURR_LOGGED_USER);
	std::ofstream oFile;
	oFile.open("recipes.db", std::ios::binary | std::ios::out | std::ios::app);
	toAddRecipe->serizalize(oFile);
	myRecipeList.addRecipe(toAddRecipe);
	std::cout << "Recipe added!" << std::endl;
	oFile.close();
}

void save(Recipes& myRecipeList, Ratings& myRatingsList) {
	std::ofstream oFile;
	oFile.open("recipes.db", std::ios::binary | std::ios::out);

	for (int i = 0; i < myRecipeList.getSize(); i++) {
		if (myRecipeList[i]) {
			myRecipeList[i]->serizalize(oFile);
		}
	}
	oFile.close();

	oFile.open("ratings.db", std::ios::binary | std::ios::out);

	for (int i = 0; i < myRatingsList.getSize(); i++) {
		if (!myRatingsList[i]->isDeleted()) {
			myRatingsList[i]->serizalize(oFile);
		}
	}
	oFile.close();
}

bool myRecipes(Recipes& myRecipeList) {
	if (CURR_LOGGED_USER == 0) {
		std::cout << "You must log in to view recipes." << std::endl;
		return false;
	}
	int recipeCounter = 1;
	for (int i = 0; i < myRecipeList.getSize(); i++) {
		if (myRecipeList[i] && myRecipeList[i]->getOwnerId() == CURR_LOGGED_USER ) {
			std::cout << recipeCounter << ". " << myRecipeList[i]->getTitle() << " Id: " << myRecipeList[i]->getId() << std::endl;
			recipeCounter++;
		}
	}
	if (recipeCounter == 1) {
		std::cout << "No recipes to show!" << std::endl;
		return false;
	}
	return true;
}

void rateRecipe(Recipes& myRecipeList, Ratings& myRatingsList) {
	if (CURR_LOGGED_USER == 0) {
		std::cout << "You must log in to rate recipe!" << std::endl;
		return;
	}
	bool hasRecipesToRate = false;
	for (int i = 0; i < myRecipeList.getSize(); i++) {
		if (myRecipeList[i] && myRecipeList[i]->getOwnerId() != CURR_LOGGED_USER) {
			hasRecipesToRate = true;
		}
	}
	if (!hasRecipesToRate) {
		std::cout << "There are no recipes you can review." << std::endl;
		return;
	}
	myRecipeList.print();
	std::cout << "Enter recipe Id you would like to rate: " << std::endl;
	int recipeId;
	
	while (true) {
		std::cin >> recipeId;
		if (!myRecipeList.getRecipeById(recipeId)) {
			std::cout << "Recipe doesn't exist. Enter again: " << std::endl;
			continue;
		}
		if (myRecipeList.getRecipeById(recipeId)->getOwnerId() == CURR_LOGGED_USER) {
			std::cout << "Cant rate own recipe. Enter again: " << std::endl;
			continue;
		}
		if (myRatingsList.existRating(CURR_LOGGED_USER, recipeId)) {
			std::cout << "Cant rate recipe twice. Enter again: " << std::endl;
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

	Rating* toAdd = new Rating(value, recipeId, CURR_LOGGED_USER);
	myRatingsList.addRating(toAdd);


	std::ofstream oFile;
	oFile.open("ratings.db", std::ios::binary | std::ios::out | std::ios::app);
	toAdd->serizalize(oFile);
	std::cout << "Rating added!" << std::endl;
	myRecipeList.getRecipeById(recipeId)->calculateRating(myRatingsList);
	oFile.close();
}

void printUserRatings(int userId, Recipes& myRecipesList, Ratings& myRatingList) {
	if (CURR_LOGGED_USER == 0) {
		std::cout << "You must log in to see your reviews." << std::endl;
		return;
	}
	int index = 1;
	for (int i = 0; i < myRatingList.getSize(); i++) {
		if (myRatingList[i]->getUserId() == userId && myRecipesList.getRecipeById(myRatingList[i]->getRecipeId())) {
			std::cout << index << ". " << myRecipesList.getRecipeById(myRatingList[i]->getRecipeId())->getTitle() << std::endl << "Rating value: " << myRatingList[i]->getValue() << std::endl << "Recipe id: " << myRatingList[i]->getRecipeId() << std::endl;
			index++;
		}
	}
	if (index == 1) {
		std::cout << "No Reviews to show!" << std::endl;
	}
}

void searchByName(Recipes& myRecipesList) {
	if (myRecipesList.isEmpty()) {
		std::cout << "There are no existing recipes yet." << std::endl;
		return;
	}
	int counter = 1;
	std::string searchedName;
	std::cout << "Enter search: " << std::endl;
	std::cin >> std::ws;
	std::getline(std::cin, searchedName, '\n');
	std::vector<Recipe*> tempVec;
	for (int i = 0; i < myRecipesList.getSize(); i++) {
		if (myRecipesList[i] && containsString(toLowerLetters(myRecipesList[i]->getTitle()), toLowerLetters(searchedName))) {
			std::cout << counter << ". " << myRecipesList[i]->getTitle() << " Id: " << myRecipesList[i]->getId() << std::endl;
			counter++;
			tempVec.push_back(myRecipesList[i]);
		}
	}
	if (counter == 1) {
		std::cout << "No recipes match this search. " << std::endl;
		return;
	}
	int searchId;
	std::cout << "Enter Id of recipe you would like to view: " << std::endl;
	while (true) {
		std::cin >> searchId;
		for (int i = 0; i < tempVec.size(); i++) {
			if (searchId == tempVec[i]->getId()) {
				tempVec[i]->printAllInfo();
				myRecipesList.getRecipeById(tempVec[i]->getId())->visit();
				return;
			}
		}
		std::cout << "Invalid Id. Enter again: " << std::endl;
	}
}

void viewProfil(Users& myUsersList, Recipes& myRecipesList) {
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
	bool hasRecipes = false;
	counter = 1;
	for (int i = 0; i < myRecipesList.getSize(); i++) {
		if (myRecipesList[i] && myRecipesList[i]->getOwnerId() == searchedId) {
			if (!hasRecipes) {
				std::cout << "Recipes: " << std::endl;
				hasRecipes = true;
			}
			std::cout << counter << ". ";
			myRecipesList[i]->printTitle();
			counter++;
		}
	}
	if (!hasRecipes) {
		std::cout << "No recipes to show." << std::endl;
	}
}

void deleteRecipe(Recipes& myRecipesList, Ratings& myRatingsList) {
	int idToDelete;
	if (CURR_LOGGED_USER == 0) {
		std::cout << "You must login to delete recipe." << std::endl;
		return;
	}
	if (!myRecipes(myRecipesList)) {
		return;
	}
	std::cout << "Enter Id of recipe you would like to delete: " << std::endl;
	while (true) {
		std::cin >> idToDelete;
		if (!myRecipesList.getRecipeById(idToDelete)) {
			std::cout << "Recipe doesn't exist. Enter again: " << std::endl;
			continue;
		}
		if (myRecipesList.getRecipeById(idToDelete)->getOwnerId() != CURR_LOGGED_USER) {
			std::cout << "Recipe doesn't belong to you. Enter again: " << std::endl;
			continue;
		}
		break;
	}
	myRecipesList.getRecipeById(idToDelete)->deleteRecipe();
	
	for (int i = 0; i < myRatingsList.getSize(); i++) {
		if (myRatingsList[i]->getRecipeId() == idToDelete) {
			myRatingsList[i]->deleteRating();
		}
	}
	std::cout << "Recipe deleted! " << std::endl;
}

void changeFoodGroup(int groups, int numberOfFoodGroups, int foodGroupIndex, Recipes& myRecipesList, int idToChange) {
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
		myRecipesList.getRecipeById(idToChange)->addFoodGroup(foodGroupIndex);
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
		myRecipesList.getRecipeById(idToChange)->removeFoodGroup(foodGroupIndex);
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
			myRecipesList.getRecipeById(idToChange)->setFoodGroup(currGroups[numberOfFoodGroups - 2]);
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
			myRecipesList.getRecipeById(idToChange)->addFoodGroup(foodGroupIndex);
			return;
		}
		std::cout << "Invalid command. Enter again: " << std::endl;
	}
}

void changeProducts(Recipes& myRecipesList, int idToChange) {
	std::string product;
	std::string volumeStr;
	std::string unit;
	double volume;

	int numberOfProducts = 1;
	std::cout << "Current products are: " << std::endl;
	int deleteIndex;

	for (int i = 0; i < myRecipesList.getRecipeById(idToChange)->getProductList().size(); i++) {
		if (!myRecipesList.getRecipeById(idToChange)->getProductList()[i].isDeleted()) {
			std::cout << numberOfProducts << ". " << myRecipesList.getRecipeById(idToChange)->getProductList()[i].getProduct() << std::endl;
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
		volume = std::stod(volumeStr, 0);
		ProductWithVolume toAdd(product, volume, unit);
		myRecipesList.getRecipeById(idToChange)->addProduct(toAdd);
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
				if (myRecipesList.getRecipeById(idToChange)->getProductList()[i].isDeleted()) {
					deleteIndex++;
				}
			}
			myRecipesList.getRecipeById(idToChange)->deleteProduct(deleteIndex);
			return;
		}
		if (areEqualCaseInsesitiveWords(command, "add")) {
			std::cout << "Enter product, volume and unit of measure of the product you would like to add in this format <name of product>, <volume>, <unit> :" << std::endl;
			std::cin >> std::ws;
			std::getline(std::cin, product, ',');
			std::cin >> std::ws;
			std::getline(std::cin, volumeStr, ',');
			std::cin >> unit;
			volume = std::stod(volumeStr, 0);
			ProductWithVolume toAdd(product, volume, unit);
			myRecipesList.getRecipeById(idToChange)->addProduct(toAdd);
			return;
		}
		std::cout << "Invalid command. Enter again: " << std::endl;
	}
}

void changeLinks(Recipes& myRecipesList, int idToChange) {
	std::string link;

	int numberOfLinks = 1;
	std::cout << "Current links are: " << std::endl;
	int deleteIndex;

	for (int i = 0; i < myRecipesList.getRecipeById(idToChange)->getLinksList().size(); i++) {
		if (!myRecipesList.getRecipeById(idToChange)->getLinksList()[i].isDeleted()) {
			std::cout << numberOfLinks << ". ";
			myRecipesList.getRecipeById(idToChange)->getLinksList()[i].print();
			numberOfLinks++;
		}
	}

	if (numberOfLinks == 2) {
		std::cout << "Enter link thet you would like to be added: " << std::endl;
		std::cin >> link;
		Link toAdd(link);
		myRecipesList.getRecipeById(idToChange)->addLink(toAdd);
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
				if (myRecipesList.getRecipeById(idToChange)->getLinksList()[i].isDeleted()) {
					deleteIndex++;
				}
			}
			myRecipesList.getRecipeById(idToChange)->removeLink(deleteIndex);
			return;
		}
		if (areEqualCaseInsesitiveWords(command, "add")) {
			std::cout << "Enter link thet you would like to be added: " << std::endl;
			std::cin >> link;
			Link toAdd(link);
			myRecipesList.getRecipeById(idToChange)->addLink(toAdd);
			return;
		}
		std::cout << "Invalid command. Enter again: " << std::endl;
	}
}

void changeRecipe(Recipes& myRecipesList) {
	int idToChange = -1;
	if (CURR_LOGGED_USER == 0) {
		std::cout << "You must log in to change recipes." << std::endl;
		return;
	}
	if (!myRecipes(myRecipesList)) {
		return;
	}
	std::cout << "Enter Id of recipe you would like to change: " << std::endl;
	while (true) {
		std::cin >> idToChange;
		if (!myRecipesList.getRecipeById(idToChange)) {
			std::cout << "Recipe doesn't exist. Enter again: " << std::endl;
			continue;
		}
		if (myRecipesList.getRecipeById(idToChange)->isDeleted() || myRecipesList.getRecipeById(idToChange)->getOwnerId() != CURR_LOGGED_USER) {
			std::cout << "Recipe doesn't exist or it doesn't belong to you. Enter again: " << std::endl;
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
	int groups = myRecipesList.getRecipeById(idToChange)->getFoodGroup();
	int numberOfFoodGroups = 1;
	switch (changeItem)
	{
	case 1:
		std::cout << "Enter new title: " << std::endl;
		std::cin >> std::ws;
		std::getline(std::cin, newValue, '\n');
		myRecipesList.getRecipeById(idToChange)->setTitle(newValue);
		break;
	case 2:
		changeFoodGroup(groups, numberOfFoodGroups, foodGroupIndex, myRecipesList, idToChange);
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
		myRecipesList.getRecipeById(idToChange)->setTimeToMake(newValueInt);
		break;
	case 4:
		changeProducts(myRecipesList, idToChange);
		break;
	case 5:
		std::cout << "Enter algorithm with maximum 10000 symbols and at the end write '~': " << std::endl;
		std::cin >> std::ws;
		std::getline(std::cin, newValue, '\n');
		if (newValue.length() > 10000) {
			newValue.resize(10000);
		}
		myRecipesList.getRecipeById(idToChange)->setAlgorithm(newValue);
		break;
	case 6:
		changeLinks(myRecipesList, idToChange);
		break;
	default:
		break;
	}
}

void previewRecipe(Recipes& myRecipesList) {
	if (myRecipesList.isEmpty()) {
		std::cout << "There are no existing recipes." << std::endl;
		return;
	}
	int searchedId;
	int counter = 1;
	for (int i = 0; i < myRecipesList.getSize(); i++) {
		if (myRecipesList[i]) {
			std::cout << counter << ". " << myRecipesList[i]->getTitle() << "  Id: " << myRecipesList[i]->getId() << std::endl;
			counter++;
		}
		
	}
	std::cout << "Enter Id of recipe you want to see info about." << std::endl;
	while (true) {
		std::cin >> searchedId;
		if (!myRecipesList.getRecipeById(searchedId)) {
			std::cout << "No recipe with this id exists.Enter again: " << std::endl;
			continue;
		}
		break;
	}
	myRecipesList.getRecipeById(searchedId)->printAllInfo();
	myRecipesList.getRecipeById(searchedId)->visit();
}

void getTopChart(Recipes& myRecipesList) {
	if (myRecipesList.isEmpty()) {
		std::cout << "There are no recipes." << std::endl;
		return;
	}
	int n;
	std::string typeOfChart;
	std::cout << "Enter number of recipes: " << std::endl;
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
			std::vector<Recipe*> toSort = myRecipesList.getRecipeList();
			for (int i = 0; i < myRecipesList.getSize() - 1; i++) {
				if (toSort[i]->getTimesVisited() < toSort[i + 1]->getTimesVisited()) {
					Recipe* temp = toSort[i];
					toSort[i] = toSort[i + 1];
					toSort[i + 1] = temp;
				}
			}
			int counter = 1;
			int index = -1;
			for (int i = 0; i < n; i++) {
				index++;
				if (index == myRecipesList.getSize()) {
					return;
				}
				if (!myRecipesList[i]) {
					i--;
					continue;
				}
				if (!toSort[i]->isDeleted()) {
					std::cout << counter << ". Visited " << toSort[i]->getTimesVisited() << " times: ";
					toSort[i]->printTitle();
				}
			}
			return;
		}
		if (areEqualCaseInsesitiveWords(typeOfChart, "rated")) {
			std::vector<Recipe*> toSort = myRecipesList.getRecipeList();
			for (int i = 0; i < myRecipesList.getSize() - 1; i++) {
				if (toSort[i]->getRating() < toSort[i + 1]->getRating()) {
					Recipe* temp = toSort[i];
					toSort[i] = toSort[i + 1];
					toSort[i + 1] = temp;
				}
			}
			int counter = 1;
			int index = -1;
			for (int i = 0; i < n; i++) {
				index++;
				if (index == myRecipesList.getSize()) {
					return;
				}
				if (!myRecipesList[i]) {
					i--;
					continue;
				}
				if (!toSort[i]->isDeleted()) {
					std::cout << counter << ". With rating " << std::setprecision(2) << std::fixed << toSort[i]->getRating() << "/5 : ";
					toSort[i]->printTitle();
				}
			}
			return;
		}
		if (areEqualCaseInsesitiveWords(typeOfChart, "recent")) {
			std::vector<Recipe*> toSort = myRecipesList.getRecipeList();
			for (int i = 0; i < myRecipesList.getSize() - 1; i++) {
				if (toSort[i]->getAddTime() < toSort[i + 1]->getAddTime()) {
					Recipe* temp = toSort[i];
					toSort[i] = toSort[i + 1];
					toSort[i + 1] = temp;
				}
			}
			int counter = 1;
			int index = -1;
			for (int i = 0; i < n; i++) {
				index++;
				if (index == myRecipesList.getSize()) {
					return;
				}
				if (!myRecipesList[i]) {
					i--;
					continue;
				}
				if (!toSort[i]->isDeleted()) {
					std::cout << counter << ". Added at ";
					toSort[i]->getAddTime().printNE();
					std::cout << ": ";
					toSort[i]->printTitle();
				}
			}
			return;
		}
		std::cout << "Invalid type. Enter again: " << std::endl;
	}
}