#include <iostream>
#include <fstream>
#include <string>
#include "pKey.h"
#include "fCriptor.h"
using namespace PKey;
using namespace AdvancedConsole;

bool isExists(std::string login){
	std::string line;
	std::string salt = "rait0ut3st";
	fCriptor crypto;
	int x = 1;
	std::ifstream ifile("Accounts.txt");
	if(ifile.is_open()){
		while(getline(ifile, line)){
			crypto.decrypt(line, salt);
			if(line == login && x % 3 == 0){
				return true;
			}
		x++;
		}
	}
	return false;
}

void create(){
	std::string line;
	std::string salt = "rait0ut3st";
	fCriptor crypto;
	int x = 1;
	std::ifstream ifile("Accounts.txt");
	std::ofstream ofile("Account_new.txt");
	if(ifile.is_open()){
		while(getline(ifile, line)){
			crypto.encrypt(line, salt);
			ofile << line << std::endl;
		}
	}
}

void menu(bool isAdmin){
	if(isAdmin){
			
	} else {
		
	}
}

int main(){
	std::string login;
	
	//Intialize Libraries
	pKey key;
	
	std::cout << Color(AC_MAGENTA) << " Login: " << Color(AC_DEFAULT);
	std::cin >> login;
	
	key.Set(login); //setting pKey
	if(key.Validate() && isExists(login)){
		std::cout << login;
		//create();
	}
}
