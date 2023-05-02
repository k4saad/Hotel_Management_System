/*
author      :   saad khan
project     :   Hotel Management System
date        :   April-2023
*/

#include<iostream>
#include"Ledger.h"

void Ledger::run() {

    int employee_choice;
label_6:
    system("CLS");
    std::cout << "\t\t\t------------------------------------------------------------\n";
    std::cout << "\t\t\t                            ROOM                            \n";
    std::cout << "\t\t\t------------------------------------------------------------\n";
    std::cout << "\t\t\t  1)  Room Income                                           \n";
    std::cout << "\t\t\t  2)  Food Income                                           \n";
    std::cout << "\t\t\t  3)  Total Income                                          \n";
    std::cout << "\t\t\t  4)  Back                                                  \n";
    if (std::cin >> employee_choice) {
        switch (employee_choice) {
        case 1:
            viewRoomIncome();           
            break;
        case 2:
            viewFoodIncome();
            break;
        case 3:
            viewTotalIncome();
            break;
        case 4:
            return;
        default:
            std::cout << "Please enter valid input\n";
            system("PAUSE");
        }
        goto label_6;
    }
    else {
        std::cerr << "Error: Reading input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("PAUSE");
        goto label_6;
    }
}

void Ledger::viewRoomIncome() {
    system("CLS");
    sqlite3_stmt* myStatement;
    int totalIncome = 0;
    std::string sql = "SELECT name, quantity, amount from income WHERE dept = 'room';";
    try {
        bool preparingSuccess = prepareQueryWithResults(sql, myStatement);
        if (preparingSuccess == false) {
            throw (std::string)"Error : Preparing Query";
        }
        int statusOfStep = sqlite3_step(myStatement);
        while (statusOfStep == SQLITE_ROW) {
            proName = (char*)sqlite3_column_text(myStatement, 0);
            proQuantity = sqlite3_column_int(myStatement, 1);
            proPrice = sqlite3_column_int(myStatement, 2);
            proIncome = proPrice * proQuantity;
            totalIncome = totalIncome + proIncome;
            std::cout << "---------------------------\n";
            std::cout << "Room Name : " << proName << "\n";
            std::cout << "Nights : " << proQuantity << " nights\n";
            std::cout << "Price : " << proPrice << " Rs / night\n";
            std::cout << "Income : " << proIncome << " Rs\n";
            statusOfStep = sqlite3_step(myStatement);
        }
        sqlite3_finalize(myStatement);
        std::cout << "\n------------------------------------------\n";
        std::cout << "Total Income : " << totalIncome << " Rs\n";
        std::cout << "------------------------------------------\n\n\n";
        system("PAUSE");
    }
    catch (std::string e) {
        std::cerr << e << std::endl;
        system("PAUSE");
        return;
    }
}

void Ledger::viewFoodIncome(){
    system("CLS");
    sqlite3_stmt* myStatement;
    int totalIncome = 0;
    std::string sql = "SELECT name, quantity, amount from income WHERE dept = 'food';";
    try {
        bool preparingSuccess = prepareQueryWithResults(sql, myStatement);
        if (preparingSuccess == false) {
            throw (std::string)"Error : Preparing Query";
        }
        int statusOfStep = sqlite3_step(myStatement);
        while (statusOfStep == SQLITE_ROW) {
            proName = (char*)sqlite3_column_text(myStatement, 0);
            proQuantity = sqlite3_column_int(myStatement, 1);
            proPrice = sqlite3_column_int(myStatement, 2);
            proIncome = proPrice * proQuantity;
            totalIncome = totalIncome + proIncome;
            std::cout << "---------------------------\n";
            std::cout << "Food Name : " << proName << "\n";
            std::cout << "Quantity : " << proQuantity << "\n";
            std::cout << "price : " << proPrice << " Rs\n";
            std::cout << "Income : " << proIncome << " Rs\n";

            statusOfStep = sqlite3_step(myStatement);
        }
        sqlite3_finalize(myStatement);
        std::cout << "\n------------------------------------------\n";
        std::cout << "Total Income : " << totalIncome << " Rs\n";
        std::cout << "------------------------------------------\n\n\n";
        system("PAUSE");
    }
    catch (std::string e) {
        std::cerr << e << std::endl;
        system("PAUSE");
        return;
    }
    
}

void Ledger::viewTotalIncome() {
    system("CLS");
    sqlite3_stmt* myStatement;
    int totalIncome = 0;
    std::string sql = "SELECT quantity, amount from income;";
    try {
        bool preparingSuccess = prepareQueryWithResults(sql, myStatement);
        if (preparingSuccess == false) {
            throw (std::string)"Error : Preparing Query";
        }
        int statusOfStep = sqlite3_step(myStatement);
        while (statusOfStep == SQLITE_ROW) {

            proQuantity = sqlite3_column_int(myStatement, 0);
            proIncome = sqlite3_column_int(myStatement, 1);
            totalIncome = totalIncome + proIncome * proQuantity;

            statusOfStep = sqlite3_step(myStatement);
        }
        sqlite3_finalize(myStatement);
        std::cout << "\n------------------------------------------\n";
        std::cout << "Total Income : " << totalIncome << " Rs\n";
        std::cout << "------------------------------------------\n";
        system("PAUSE");
    }
    catch (std::string e) {
        std::cerr << e << std::endl;
        system("PAUSE");
        return;
    }
}