#include "Functions.h"




int main() {

	Ratings myRatingsList;
	myRatingsList.load("ratings.db");
	Recipes myRecipeList;
	myRecipeList.load("recipes.db");
	Users myUserList;
	myUserList.load("users.db");
	for (int i = 0; i < myRecipeList.getSize(); i++) {
		myRecipeList[i]->calculateRating(myRatingsList);
	}

	std::string myCommand = "";
	int indexOfCommand = -1;

	printCommands();
	while (true) {
		std::cout << "Enter command. If you want to see list of commands enter 'commands': " << std::endl << "> ";
		std::cin >> myCommand;
		if (!isValidCommand(myCommand)) {
			std::cout << "Invalid command.Enter again: " << std::endl;
		}else {
			indexOfCommand = indexOfCommandfunc(myCommand);
			switch (indexOfCommand)
			{
			case 0 :
				registerUser(myUserList);
				break;
			case 1:
				loginUser(myUserList);
				break;
			case 2:
				logoutUser();
				break;
			case 3:
				addRecipe(myRecipeList);
				break;
			case 4:
				changeRecipe(myRecipeList);
				break;
			case 5:
				deleteRecipe(myRecipeList, myRatingsList);
				break;
			case 6:
				previewRecipe(myRecipeList);
				break;
			case 7:
				searchByName(myRecipeList);
				break;
			case 8:
				rateRecipe(myRecipeList, myRatingsList);
				break;
			case 9:
				getTopChart(myRecipeList);
				break;
			case 10:
				viewProfil(myUserList, myRecipeList);
				break;
			case 11:
				myRecipes(myRecipeList);
				break;
			case 12:
				printUserRatings(CURR_LOGGED_USER, myRecipeList, myRatingsList);
				break;
			case 13:
				std::cout << "Saving changes..." << std::endl;
				save(myRecipeList, myRatingsList);
				std::cout << "Changes saved!" << std::endl;
				std::cout << "Exiting..." << std::endl;
				return 0;
			case 14:
				printCommands();
			default:
				std::cout << "Error." << std::endl;
				break;
			}
		}
	}
}
