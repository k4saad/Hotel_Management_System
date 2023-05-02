/*
author      :   saad khan
project     :   Hotel Management System
date        :   April-2023
*/

#pragma once
#include<string>
#include"DBAbstraction.h"

class Hotel:public DBAbstraction {
	void runFunction(const std::string&);
	void createTables();
public:
	Hotel();
	void run();
	
};
