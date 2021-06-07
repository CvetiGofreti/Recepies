#include <stdlib.h>
#include "User.h"
#include "Functions.h"

//opravi timeAdded

int main() {
	Ratings myRatingsList;
	myRatingsList.load("ratings.db");
	Recepies myRecepieList;
	myRecepieList.load("recepies.db");
	Users myUserList;
	myUserList.load("users.db");
	for (int i = 0; i < myRecepieList.getSize(); i++) {
		myRecepieList[i]->calculateRating(myRatingsList);
	}
	myRecepieList[0]->printAllInfo();
	std::string myCommand = "";
	int indexOfCommand = -1;
	while (true) {
		std::cout << "Enter command register/login/logout/exit: " << std::endl;
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
				addRecepie(myRecepieList);
				break;
			case 4:
				changeRecepie(myRecepieList);
				break;
			case 5:
				deleteRecepie(myRecepieList);
				break;
			case 6:
				previewRecepie(myRecepieList);
				break;
			case 7:
				searchByName(myRecepieList);
				break;
			case 8:
				rateRecepie(myRecepieList, myRatingsList);
				break;
			case 9:
				getTopChart(myRecepieList);
				break;
			case 10:
				viewProfil(myUserList, myRecepieList);
				break;
			case 11:
				myRecepies(myRecepieList);
				break;
			case 12:
				printUserRatings(CURR_LOGGED_USER, myRecepieList, myRatingsList);
				break;
			case 13:
				std::cout << "Saving changes..." << std::endl;
				save(myRecepieList);
				std::cout << "Changes saved!" << std::endl;
				std::cout << "Exiting..." << std::endl;
				return 0;
			default:
				break;
			}
		}
	}
}

//BCrypt::validatePassword