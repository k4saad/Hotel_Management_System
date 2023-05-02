/*
author      :   saad khan
project     :   Hotel Management System
date        :   April-2023
*/

#include<iostream>
#include"Food.h"

void Food::run() {

    int employee_choice;
label_6:
    system("CLS");
    std::cout << "\t\t\t------------------------------------------------------------\n";
    std::cout << "\t\t\t                            ROOM                            \n";
    std::cout << "\t\t\t------------------------------------------------------------\n";
    std::cout << "\t\t\t  1)  Add Food                                              \n";
    std::cout << "\t\t\t  2)  Delete Food                                           \n";
    std::cout << "\t\t\t  3)  All Food                                              \n";
    std::cout << "\t\t\t  4)  Back                                                  \n";
    if (std::cin >> employee_choice) {
        switch (employee_choice) {
        case 1:
            addFood();
            break;
        case 2:
            deleteFood();
            break;
        case 3:
            viewAllFood();
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

void Food::addFood() {
    system("CLS");
    std::cout << "\t\t\t---Enter food details---\n";
    std::cout << "Food Name : \n";
    std::cin.ignore();
    if(getline(std::cin, foodName));
    else {
        std::cerr << "Error: Reading input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("pause");
        return;
    }
    std::cout << "Food Type ( soup, starter, entree )  : \n";
    if(std::cin >> foodType);
    else {
        std::cerr << "Error: Reading input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("pause");
        return;
    }
    std::cout << "Food Price : \n";
    if(std::cin >> foodPrice);
    else {
        std::cerr << "Error: Reading input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("pause");
        return;
    }
    sqlite3_stmt* myStatement;
    std::string sql = "INSERT INTO food VALUES(?,?,?);";
    int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);
    try {
        if (statusOfPrep != SQLITE_OK) {
            throw (std::string)"Error : Preparing Statement";
        }
        sqlite3_bind_text(myStatement, 1, foodName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(myStatement, 2, foodType.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(myStatement, 3, foodPrice);
        bool querySuccess = executeQueryNoResultsBack(myStatement);

        try {
            if (querySuccess == false) {
                throw (std::string)"Error : Adding food";
            }
            std::cout << "Food added successfully\n";
            system("PAUSE");
        }
        catch (std::string e) {
            std::cerr << e << std::endl;
            system("PAUSE");
            return;
        }
    }
    catch (std::string e) {
        std::cerr << e << std::endl;
        system("PAUSE");
        return;
    }
}

void Food::deleteFood() {
    system("CLS");
    sqlite3_stmt* myStatement;
    std::string sql = "SELECT food.name, food.type, food.price FROM food ORDER BY food.type;";
    try {
        bool preparingSuccess = prepareQueryWithResults(sql, myStatement);
        if (preparingSuccess == false) {
            throw (std::string)"Error : Preparing Query";
        }
        int statusOfStep = sqlite3_step(myStatement);
        while (statusOfStep == SQLITE_ROW) {
            foodName = (char*)sqlite3_column_text(myStatement, 0);
            foodType = (char*)sqlite3_column_text(myStatement, 1);
            foodPrice = sqlite3_column_int(myStatement, 2);
            std::cout << "---------------------------\n";
           
            std::cout << "Food name : " << foodName << "\n";
            std::cout << "Food type : " << foodType << "\n";
            std::cout << "Food price : " << foodPrice << " per plate\n";
            statusOfStep = sqlite3_step(myStatement);
        }

        std::string delFoodName;
        std::cout << "\nEnter food name to be deleted\n";
        std::cin.ignore();
        if (getline(std::cin, delFoodName));
        else {
            std::cerr << "Error: Reading input" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("pause");
            return;
        }
        sql = "DELETE FROM food WHERE name = (?);";
        int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

        try {
            if (statusOfPrep != SQLITE_OK) {
                throw (std::string)"Error : Preparing Statement";
            }
            sqlite3_bind_text(myStatement, 1, delFoodName.c_str(), -1, SQLITE_STATIC);
            bool querySuccess = executeQueryNoResultsBack(myStatement);
            try {
                if (querySuccess == false) {
                    throw (std::string)"Error : Removing food";
                }
                std::cout << "Food removed successfully\n";
                system("PAUSE");
            }
            catch (std::string e) {
                std::cerr << e << std::endl;
                system("PAUSE");
                return;
            }
        }
        catch (std::string e) {
            std::cerr << e << std::endl;
            system("PAUSE");
            return;
        }
    }
    catch (std::string e) {
        std::cerr << e << std::endl;
        system("PAUSE");
        return;
    }
}
void Food::viewAllFood() {
    system("CLS");
    sqlite3_stmt* myStatement;
    std::string sql = "SELECT food.name, food.type, food.price FROM food ORDER BY food.type;";
    try {
        bool preparingSuccess = prepareQueryWithResults(sql, myStatement);
        if (preparingSuccess == false) {
            throw (std::string)"Error : Preparing Query";
        }
        int statusOfStep = sqlite3_step(myStatement);
        while (statusOfStep == SQLITE_ROW) {
            foodName = (char*)sqlite3_column_text(myStatement, 0);
            foodType = (char*)sqlite3_column_text(myStatement, 1);
            foodPrice = sqlite3_column_int(myStatement, 2);
            std::cout << "---------------------------\n";

            std::cout << "Food name : " << foodName << "\n";
            std::cout << "Food type : " << foodType << "\n";
            std::cout << "Food price : " << foodPrice << " per plate\n";
            statusOfStep = sqlite3_step(myStatement);
        }
        system("PAUSE");
    }
    catch (std::string e) {
        std::cerr << e << std::endl;
        system("PAUSE");
        return;
    }
}