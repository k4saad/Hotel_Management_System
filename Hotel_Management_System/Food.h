/*
author      :   saad khan
project     :   Hotel Management System
date        :   April-2023
*/

#pragma once
#include<string>
#include"Hotel.h"
class Food : public Hotel {
    std::string foodName, foodType;
    int foodPrice;
    void addFood();
    void deleteFood();
    void viewAllFood();

public:
    void employeeRun();
    void orderFood();
};
