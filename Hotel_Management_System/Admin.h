/*
author      :   saad khan
project     :   Hotel Management System
date        :   April-2023
*/

#pragma once
#include<string>
#include"Hotel.h"
class Admin:public Hotel {
	int employeeId;
	std::string employeeName, employeeUsername, employeePassword;
	bool registerAdmin(const std::string& username, const std::string& password);
	bool checkUsername(const std::string admin_userName);
	void registerEmployee();
	void removeEmployee();
	void viewAllEmployee();
public:
	static std::string hashPassword(const std::string& password);
	Admin();
	bool adminLogin(const std::string& username, const std::string& password);
	void run(const std::string& username, const std::string& password);
};
