/*
author      :   saad khan
project     :   Hotel Management System
date        :   April-2023
*/

#pragma once
#include<string>
#include"Hotel.h"
class Guest : public Hotel {
	void operation(const std::string&);
public:
	void run();

};