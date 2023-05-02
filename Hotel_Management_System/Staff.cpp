/*
author      :   saad khan
project     :   Hotel Management System
date        :   April-2023
*/

#include<iostream>
#include<limits>
#include"Admin.h"
#include"Employee.h"
#include"Staff.h"
void Staff::run(){
    int staff_choice;
label_2:
    system("CLS");
    std::cout << "\t\t\t------------------------------------------------------------\n";
    std::cout << "\t\t\t                            STAFF                           \n";
    std::cout << "\t\t\t------------------------------------------------------------\n";
    std::cout << "\t\t\t  1)  Admin login                                           \n";
    std::cout << "\t\t\t  2)  Employee login                                        \n";
    std::cout << "\t\t\t  3)  Back                                                  \n";
    if (std::cin >> staff_choice) {
        switch (staff_choice) {
        case 1:
            login("Admin");
            break;
        case 2:
            login("Employee");
            break;
        case 3:
            return;
        default:
            std::cout << "Please enter valid input\n";
            system("PAUSE");
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
    if (std::cin >> username);
    else {
        std::cerr << "Error reading input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cout << "password : ";
    if (std::cin >> password);
    else {
        std::cerr << "Error reading input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    if (s == "Admin") {
        Admin A;
        A.run(username, password);
        return;
        
    }
    else {
        Employee E;
        E.run(username, password);
        return;
    }
    
}