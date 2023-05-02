/*
author      :   saad khan
project     :   Hotel Management System
date        :   April-2023
*/

#pragma once
#include<string>
#include"Hotel.h"
class Ledger : public Hotel {
    std::string proName;
    int proQuantity, proIncome, proPrice;
    void viewRoomIncome();
    void viewFoodIncome();
    void viewTotalIncome();

public:
    void run();
};
