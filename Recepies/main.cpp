#include <stdlib.h>
#include "User.h"
#include "Functions.h"




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
int main() {
	Users myUserList;
	myUserList.load("users.db");
	std::string myCommand = "";
	int indexOfCommand = -1;
	while (true) {
		std::cout << "Enter command register/login/logout/exit: " << std::endl;
		std::cin >> myCommand;
		if (!isValidCommand(myCommand)) {
			std::cout << "Invalid command.Enter again: " << std::endl;
		}
		
		else {
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
			case 14:
				std::cout << "Exiting..." << std::endl;
				return 0;
			default:
				break;
			}
		}
	}
}

//BCrypt::validatePassword