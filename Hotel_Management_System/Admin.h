/*
author      :   saad khan
project     :   Hotel Management System
date        :   April-2023
*/

#pragma once
#include<string>
#include"Hotel.h"
class Admin:public Hotel {
	std::string userName, password;
	std::string hashPassword(const std::string& password);
	bool registerAdmin(const std::string& username, const std::string& password);
	bool checkUsername(const std::string admin_userName);
	void registerStaff();
public:
	Admin();
	bool adminLogin(const std::string& username, const std::string& password);
	void run();
};
