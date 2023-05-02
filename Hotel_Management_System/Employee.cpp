/*
author      :   saad khan
project     :   Hotel Management System
date        :   April-2023
*/

#include<iostream>
#include"Admin.h"
#include"Employee.h"
#include"Room.h"
#include"Food.h"
#include"Ledger.h"

void Employee::run(const std::string& username, const std::string& password) {
    if (employeeLogin(username, password)) {
        system("PAUSE");
        int employee_choice;
    label_4:
        system("CLS");

        std::cout << "\t\t\t------------------------------------------------------------\n";
        std::cout << "\t\t\t                            STAFF                           \n";
        std::cout << "\t\t\t------------------------------------------------------------\n";
        std::cout << "\t\t\t  1)  Room                                                  \n";
        std::cout << "\t\t\t  2)  Food                                                  \n";
        std::cout << "\t\t\t  3)  Ledger                                                \n";
        std::cout << "\t\t\t  4)  Back                                                  \n";
        if (std::cin >> employee_choice) {
            switch (employee_choice) {
            case 1:
                operation("Room");
                break;
            case 2:
                operation("Food");
                break;
            case 3:
                operation("Ledger");
                break;
            case 4:
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
}
bool Employee::employeeLogin(const std::string& username, const std::string& password) {
    std::string hashedEmployeePassword = Admin::hashPassword(password);
    std::string sql = "SELECT employee.name FROM employee WHERE username = (?) AND password = (?);";
    sqlite3_stmt* myStatement;
    try {
        bool preparingSuccess = prepareQueryWithResults(sql, myStatement);
        if (preparingSuccess == false) {
            throw (std::string)"Error : Preparing Query";
        }
        sqlite3_bind_text(myStatement, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(myStatement, 2, hashedEmployeePassword.c_str(), -1, SQLITE_STATIC);
        int statusOfStep = sqlite3_step(myStatement);
        if (statusOfStep == SQLITE_ROW) {
            std::string eName = (char*)sqlite3_column_text(myStatement, 0);
            sqlite3_finalize(myStatement);
            std::cout << "Login successful!" << std::endl;
            std::cout << "Welcome " << eName<<"\n";
            return true;
        }
        else {
            std::cout << "User not found!" << std::endl;
            system("PAUSE");
            return false;
        }  
    }
    catch (std::string e) {
        std::cerr << e << std::endl;
        system("PAUSE");
        return false;
    }
}
void Employee::operation(const std::string& opr) {
    if (opr == "Room") {
        Room R;
        R.run();
    }
    else if(opr == "Food") {
        Food F;
        F.run();
    }
    else {
        Ledger L;
        L.run();
    }
}