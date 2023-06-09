/*
author      :   saad khan
project     :   Hotel Management System
date        :   April-2023
*/
#include<iostream>
#include<limits>
#include<string>

#include<vector>
#include"DBAbstraction.h"
#include"Hotel.h"
#include"Staff.h"
#include"Guest.h"

Hotel::Hotel() {
    createTables();
}
void Hotel::createTables() {

    bool allQuerySuccess = true;
    std::vector<std::string> sqls = {
                                    "CREATE TABLE IF NOT EXISTS employee(id INTEGER PRIMARY KEY CHECK(id != 0 AND id > 0),name TEXT NOT NULL, username TEXT NOT NULL, password TEXT);\n",
                                    "CREATE TABLE IF NOT EXISTS room(id INTEGER PRIMARY KEY CHECK(id != 0 AND id > 0), name TEXT , capacity INTEGER, price INTEGER, roomsize INTEGER, bedsize TEXT, discription TEXT);\n",
                                    "CREATE TABLE IF NOT EXISTS income(name TEXT, quantity INTEGER, amount INTEGER, dept TEXT)\n",
                                    "CREATE TABLE IF NOT EXISTS food(name TEXT PRIMARY KEY, type TEXT, price INTEGER)\n"
                                    };
    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    for (int i = 0; i < sqls.size(); ++i) {

        std::string sql = sqls[i];

        bool querySuccess = executeQueryNoResultsBack(sql);

        if (querySuccess == false) {

            allQuerySuccess = false;
            break;
        }
    }

    if (allQuerySuccess) {
        sqlite3_exec(db, "COMMIT TRANSACTION;", NULL, NULL, NULL);
    }
    else {
        sqlite3_exec(db, "ROLLBACK TRANSACTION;", NULL, NULL, NULL);
        std::cout << "Error creating Tables";
        system("PAUSE");
    }
}

void Hotel::run() {
    int main_choice;
label_1:
    system("CLS");
    std::cout << "\t\t\t------------------------------------------------------------\n";
    std::cout << "\t\t\t                          Main Menue                        \n";
    std::cout << "\t\t\t------------------------------------------------------------\n";
    std::cout << "\t\t\t  1)  Staff                                                 \n";
    std::cout << "\t\t\t  2)  Guest                                                 \n";
    std::cout << "\t\t\t  3)  Exit                                                  \n";
    if (std::cin >> main_choice) {
        switch (main_choice) {
        case 1:
            runFunction("Staff");
            break;
        case 2:
            runFunction("Guest");
            break;
        case 3:
            exit(0);
        default:
            std::cout << "Please enter valid input\n";
            system("PAUSE");           
        }
     goto label_1;
    }
    else {
        std::cerr << "Error reading input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        goto label_1;
    }
}
void Hotel::runFunction(const std::string& f) {
    if (f == "Staff") {
        Staff S;
        S.run();
    }
    else if (f == "Guest") {
        Guest G;
        G.run();
    }
    else {
        std::cerr << "Error in Hotel.cpp" << std::endl;
    }
    return;
}