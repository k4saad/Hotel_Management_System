#pragma once
#include<string>

class Admin {
	std::string userName, password;
	std::string hashPassword(const std::string& password);
	bool registerUser(const std::string& username, const std::string& password);
	bool checkUsername(const std::string admin_userName);
public:
	Admin();
	bool adminLogin(const std::string& username, const std::string& password);
};
