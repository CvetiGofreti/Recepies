#include <stdlib.h>
#include "User.h"
#include "Functions.h"


int main() {
	
	Recepies myRecepieList;
	myRecepieList.load("recepies.db");
	Users myUserList;
	myUserList.load("users.db");
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
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				break;
			case 10:
				myProfil(myUserList);
				break;
			case 11:
				myRecepies(myRecepieList);
				break;
			case 12:
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