/*
author      :   saad khan
project     :   Hotel Management System
date        :   April-2023
*/

#pragma once
#include<string>
#include"Hotel.h"
class Employee :public Hotel {
	std::string hashPassword(const std::string& password);
	void operation(const std::string&);
public:
	bool employeeLogin(const std::string& username, const std::string& password);
	void run(const std::string& username, const std::string& password);
	
};
