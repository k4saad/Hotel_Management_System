/*
author      :   saad khan
project     :   Hotel Management System
date        :   April-2023
*/

#include<iostream>
#include"Guest.h"
#include"Room.h"
#include"Food.h"
#include"Ledger.h"

void Guest::run() {
    int guest_choice;
label_4:
    system("CLS");

    std::cout << "\t\t\t------------------------------------------------------------\n";
    std::cout << "\t\t\t                    Welcome To XYZ Hotel                    \n";
    std::cout << "\t\t\t------------------------------------------------------------\n";
    std::cout << "\t\t\t  1)  Book Room                                             \n";
    std::cout << "\t\t\t  2)  Order Food                                            \n";
    std::cout << "\t\t\t  3)  Back                                                  \n";
    if (std::cin >> guest_choice) {
        switch (guest_choice) {
        case 1:
            operation("Room");
            break;
        case 2:
            operation("Food");
            break;
        case 3:
            return;
        default:
            std::cout << "Please enter valid input\n";
            system("PAUSE");
        }
        goto label_4;
    }
    else {
        std::cerr << "Error reading input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("PAUSE");
        goto label_4;
    }
}

void Guest::operation(const std::string& opr) {
    if (opr == "Room") {
        Room R;
        R.bookRoom();
    }
    else {
        Food F;
        F.orderFood();
    }
}