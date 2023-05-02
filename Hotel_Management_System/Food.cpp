/*
author      :   saad khan
project     :   Hotel Management System
date        :   April-2023
*/

#include<iostream>
#include<vector>
#include<iomanip>
#include"Food.h"

void Food::employeeRun() {

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
        sqlite3_finalize(myStatement);
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
        sqlite3_finalize(myStatement);
        system("PAUSE");
    }
    catch (std::string e) {
        std::cerr << e << std::endl;
        system("PAUSE");
        return;
    }
}
void Food::orderFood() {
    system("CLS");
    sqlite3_stmt* myStatement;
    std::string sql = "SELECT food.name, food.price FROM food ORDER BY food.type;";
    int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);
    try {
        if (statusOfPrep != SQLITE_OK) {
            throw (std::string)"Something went wrong ";
        }
        int statusOfStep = sqlite3_step(myStatement);
        std::cout << "\n\n+---------------------------MENUE---------------------------+\n";
        std::cout << "\tNAME\t\t\t\t" << "PRICE\n\n";
        while (statusOfStep == SQLITE_ROW) {
            foodName = (char*)sqlite3_column_text(myStatement, 0);
            foodPrice = sqlite3_column_int(myStatement, 1);
           std::cout << "\t" << foodName << "\t\t\t\t" << foodPrice << "\n";
            statusOfStep = sqlite3_step(myStatement);
        }
        std::cout << "+-----------------------------------------------------------+\n\n\n";
        sqlite3_finalize(myStatement);
        bool guestChoice = true;
        std::string guestFoodName;
        std::vector<std::string> allGuestFoodName;
        int guestFoodQuantity, guestFoodPrice;
        std::vector<int> allGuestFoodQuantity, allGuestFoodPrice;
       std::cout << "\nEnter 0 to retrun back or 1 to continue :  \n";

       while (guestChoice) {
           std::cout << "Enter Food name : \n";
           if(std::cin >> guestFoodName);
           else {
               std::cerr << "Error: Reading input" << std::endl;
               std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
               system("pause");
               return;
           }
           std::cout << "Enter Quantity : \n";
           if (std::cin >> guestFoodQuantity);
           else {
               std::cerr << "Error: Reading input" << std::endl;
               std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
               system("pause");
               return;
           }
           sql = "SELECT food.price FROM food WHERE food.name=(?);";
           int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);
           try {
               if (statusOfPrep != SQLITE_OK) {
                   throw (std::string)"Something went wrong ";
               }
               sqlite3_bind_text(myStatement, 1, guestFoodName.c_str(), -1, SQLITE_STATIC);
               if (statusOfStep == SQLITE_ROW) {
                   guestFoodPrice = sqlite3_column_int(myStatement, 0);
                   allGuestFoodPrice.push_back(guestFoodPrice);

                   allGuestFoodQuantity.push_back(guestFoodQuantity);
                   allGuestFoodName.push_back(guestFoodName);
                   std::cout << guestFoodQuantity << " " << guestFoodName << " ordered.\n";
               }
               else {
                   std::cout << guestFoodName << " is not available.\n";
               }
               sqlite3_finalize(myStatement);               
           }
           catch (std::string e) {
               std::cerr << e << std::endl;
               system("PAUSE");
               return;
           }
           std::cout << "For recipt press 0 or to continue press 1\n";
           if(std::cin >> guestChoice);
           else {
               std::cerr << "Error: Reading input" << std::endl;
               std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
               guestChoice = false;
               system("pause");
           }
       }
       std::string dept = "food";
       for (decltype(allGuestFoodName.size()) i = 0; i <= allGuestFoodName.size(); ++i) {
           sql = "INSERT INTO income VALUES(?,?,?,?);";
           statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);
           try {
               if (statusOfPrep != SQLITE_OK) {
                   throw (std::string)"Something went wrong ";
               }
               sqlite3_bind_text(myStatement, 1, allGuestFoodName[i].c_str(), -1, SQLITE_STATIC);
               sqlite3_bind_int(myStatement, 2, allGuestFoodQuantity[i]);
               sqlite3_bind_int(myStatement, 3, allGuestFoodPrice[i]);
               sqlite3_bind_text(myStatement, 4, dept.c_str(), -1, SQLITE_STATIC);
               bool querySuccess = executeQueryNoResultsBack(myStatement);
               try {
                   if (querySuccess == false) {
                       throw (std::string)"Something went wrong ";
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
       int guestFoodTotalPrice = 0;
       system("CLS");
       std::cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
       std::cout << "\t|" << std::setw(36) << "      RECIPT " << std::setw(27) << "|\n";
       std::cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
       std::cout << "\t  NAME\t\t" << "PRICE\t\t" << "QUANTITY\n\n";
       for (decltype(allGuestFoodName.size()) i = 0; i <= allGuestFoodName.size(); ++i) {
           guestFoodTotalPrice = guestFoodTotalPrice + allGuestFoodPrice[i] * allGuestFoodQuantity[i];
           std::cout << "\t " << allGuestFoodName[i] << "\t\t" << allGuestFoodPrice[i] << " Rs" << "\t\t" << allGuestFoodQuantity[i] <<"\n";
       }
       std::cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
       std::cout << "\n\nGrand Total : " << guestFoodTotalPrice << " Rs" << "\n\n\n";
       std::cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
       system("PAUSE");

    }
    catch (std::string e) {
        std::cerr << e << std::endl;
        system("PAUSE");
        return;
    }
}