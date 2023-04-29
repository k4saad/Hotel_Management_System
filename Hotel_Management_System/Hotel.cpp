#include<iostream>
#include<limits>
#include<string>
/*
author      :   saad khan
project     :   Hotel Management System
date        :   April-2023
*/

#include<vector>
#include"DBAbstraction.h"
#include"Hotel.h"
#include"Admin.h"
#include"Staff.h"

Hotel::Hotel() {
    createTables();
}
void Hotel::createTables() {
    bool allQuerySuccess = true;
    std::vector<std::string> sqls = { "CREATE TABLE IF NOT EXISTS employee(id INTEGER PRIMARY KEY CHECK(id != 0 AND id > 0),name TEXT NOT NULL, username TEXT NOT NULL, password TEXT);\n" };
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
            run_function("Staff");
            break;
        case 2:
            //guest_menue();
            break;
        case 3:
            exit(1);
        default:
            std::cout << "Please enter valid input\n";
           
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
void Hotel::run_function(const std::string& f) {
    if (f == "Staff") {
        Staff s;
        s.run();
    }
    else if (f == "Customer") {

    }
    else {
        std::cerr << "Error in Hotel.cpp" << std::endl;
    }
    return;
}