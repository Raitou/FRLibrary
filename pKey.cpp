#include "pKey.h"

using namespace PKey;
using namespace AdvancedConsole;

pKey::pKey()
{
	std::cout << Color(AC_GREEN, AC_BOLD)
	<< "\t" << logo1 << std::endl 
	<< "\t" << logo2 << std::endl
	<< "\t" << logo3 << std::endl
	<< "\t" << logo4 << std::endl
	<< "\t" << logo5 << std::endl
	<< "\t" << logo6 << std::endl
	<< "\t" << logo7 << std::endl
	<< "\t" << logo8 << std::endl
	<< Color(AC_CYAN) << std::endl
	<< "\t\t" << logoInfo << std::endl
	<< Color(AC_YELLOW) << std::endl
	<< "\t" << pkEmuInfo1 << std::endl
	<< "\t" << pkEmuInfo2 << std::endl << std::endl;
}

User::User(){
	return;
}

void User::Set(std::string &x){
	pKey = x;
}

void User::Print(){
	std::cout << pKey;
}

bool User::Validate(){
	if(pKey == ""){
		return false;
	}
	if(!formatCheck(pKey)){
		return false;
	}
	if(!keyVerify()){
		return false;
	}
	return true;
}

Security::Security(){
	return;
}

bool Security::isAdmin(){
	return admin;
}

bool Security::formatCheck(std::string &pKey){	
	//Temp String
	std::string temp;
	
	//STEP 1: CHECK SIZE!
	if(pKey.length() != 30){
		return false;
	}
	
	//STEP 2: CHECK ALPHABET!
	for(int i = 0; pKey.length() > i; i++){
		bool hit = false;
		for(int j = 0; alphaNum.length() > j; j++){
			if(pKey[i] == alphaNum[j]){
				hit = true;
				break;
			} else {
				continue;
			}
		}
		if(!hit){
			return false;
		} else {
			continue;
		}
	}
	
	//STEP 3: CHECK FORMAT! JUST DASHES
	for(int i = 0; pKey.length() > i; i++){
		switch(i){
			case 18:
			case 12:
			case 6:
			case 1:
				if(pKey[i] == 45){
					continue;
				} else {
					return false;
				}
			break;
			default:
				continue;
		}
	}
	
	//Start Checking dashes
	int pos = pKey.find("-") + 1;
	
	//STEP 4: isAdmin?
	if(pKey[0] == '1' || pKey[0] == '0'){
		temp = pKey.substr(0,1);
		admin = std::stoi(temp);
	} else {
		return false;
	}
	
	//STEP 5: defineYearRegistration
	temp = pKey.substr(pos, sizeof(int));
	for(int i = 0; temp.length() > i; i++){
		if(isdigit(temp[i])){
			continue;
		} else {
			return false;
		}
	}
	
	//if Done
	if(std::stoi(temp) >= 2014 && std::stoi(temp) <= 2019){
		yearReg = std::stoi(temp);
	} else {
		return false;
	}
	
	//STEP 6: getUKey
	for(int i = 0; 4 > i; i++){
		temp = pKey.substr(pos);
		pos += (temp.find("-") + 1);
		if(pos >= 0){
			temp = pKey.substr(pos,5);
			for(int j = 0; temp.length() > j; j++){
				if(isalnum(temp[j])){
					continue;
				} else {
					return false;
				}
			}
			switch(i){
				case 0:
					key1 = temp;
					break;
				case 1:
					key2 = temp;
					break;
				case 2:
					key3 = temp;
					break;
				case 3:
					key4 = temp;
					break;
				default:
					return false;
			}
		}
	}
	
	return true;
}

bool Security::keyVerify(){
	for(int i = 0; key1.length() > i; i++){
		keyVal1 += (int)key1.c_str()[i];
	}
	
	if(keyVal1 <= 240){
		return false;
	}
	
	for(int i = 0; key2.length() > i; i++){
		keyVal2 += (int)key2.c_str()[i];
	}
	
	if(keyVal1 != keyVal2){
	    return false;
	}
	
	uid1 = keyVal1;
	
	if(key1 == key2){
		return false;
	}
	
	keyVal1 = 0;
	keyVal2 = 0;
	for(int i = 0; key3.length() > i; i++){
		keyVal1 += (int)key3.c_str()[i];
	}
	
	if(keyVal1 <= 240){
		return false;
	}
	
	if(
	key1 == key3 &&
	key2 == key3){
		return false;
	}
	
	for(int i = 0; key4.length() > i; i++){
		keyVal2 += (int)key4.c_str()[i];
	}
	
	if(keyVal1 != keyVal2){
	    return false;
	}
	
	if(
	key1 == key4 &&
	key2 == key4 &&
	key3 == key4){
		return false;
	}
	
	uid2 = keyVal2;
	
	if(uid1 == uid2 && admin != 1){
		return false;
	}
	
	if(uid1 != uid2 && admin != 0){
		return false;
	}
	
	return true;
}

void Security::printInfo(){
	std::cout 
	<< key1 << std::endl
	<< key2 << std::endl
	<< key3 << std::endl
	<< key4 << std::endl
	<< admin << std::endl
	<< yearReg << std::endl
	<< keyVal1 << std::endl
	<< keyVal2 << std::endl
	<< uid1 << std::endl
	<< uid2 << std::endl;
}

