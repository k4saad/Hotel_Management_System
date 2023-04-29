/*
author      :   saad khan
project     :   Hotel Management System
date        :   April-2023
*/

#pragma once
#include<iostream>
#include"Admin.h"
class Staff {
    std::string userName, password;
public:
    void run();
    void login(const std::string&);
};