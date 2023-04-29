/*
author      :   saad khan
project     :   Hotel Management System
date        :   April-2023
*/

#include<iostream>
#include<limits>
#include"Staff.h"
void Staff::run(){
    int staff_choice;
label_2:
    system("CLS");
    std::cout << "\t\t\t------------------------------------------------------------\n";
    std::cout << "\t\t\t                            STAFF                           \n";
    std::cout << "\t\t\t------------------------------------------------------------\n";
    std::cout << "\t\t\t  1)  Admin login                                           \n";
    std::cout << "\t\t\t  2)  Staff login                                           \n";
    std::cout << "\t\t\t  3)  Back                                                  \n";
    if (std::cin >> staff_choice) {
        switch (staff_choice) {
        case 1:
            login("Admin");
            break;
        case 2:
            //staff_login();
            break;
        case 3:
            return;
        default:
            std::cout << "Please enter valid input\n";
        }
        goto label_2;


    }
    else {
        std::cerr << "Error reading input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        goto label_2;
    }
    return;
}
void Staff::login(const std::string& s) {
    system("CLS");
    std::string username, password;
    std::cout << "username : ";
    std::cin >> username;
    std::cout << "password : ";
    std::cin >> password;
    if (s == "Admin") {
        Admin A;
        if (A.adminLogin(username, password)) {
            std::cout << "Access granted\n";
            system("PAUSE");
            A.run();
        }
        else {
            system("PAUSE");
            return;
        }
    }
    else {

    }
    return;
}