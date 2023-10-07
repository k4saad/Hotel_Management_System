/*
author      :   saad khan
project     :   Hotel Management System
date        :   April-2023
*/

#include <string>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include "../Hotel_Management_System/crypto++/cryptopp/sha.h"
#include "../Hotel_Management_System/crypto++/cryptopp/hex.h"
#include<limits>
#include"Admin.h"

Admin::Admin() {
    if(!checkUsername("admin")) registerAdmin("admin", "admin");

}
bool Admin::registerAdmin(const std::string& username, const std::string& password) {
    std::string hashedPassword = hashPassword(password);
    std::ofstream file("passwords.txt", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file passwords.txt for writing" << std::endl;
        return false;
    }
    file << username << " " << hashedPassword << std::endl;
    return true;
}


bool Admin::checkUsername(const std::string admin_userName) {
    std::string password_filename = "passwords.txt";
    std::ifstream file(password_filename);  

    std::string line;
    std::unordered_set<std::string> users;  

    while (std::getline(file, line)) {  
        std::stringstream ss(line);
        std::string username, password;
        ss >> username >> password;
        users.insert(username);  
    }

    file.close(); 

    if (users.count(admin_userName) > 0) {
        return true;
    }
    else {
        return false;
    }
}

std::string Admin::hashPassword(const std::string & password) {
    CryptoPP::SHA256 hash;
    std::string hashResult;
    CryptoPP::StringSource(password, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(hashResult))));
    return hashResult;
}

bool Admin::adminLogin(const std::string& username, const std::string& password) {

    std::string hashedPassword = hashPassword(password);
    std::ifstream file("passwords.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file passwords.txt for reading" << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string fileUsername, fileHashedPassword;
        if (iss >> fileUsername >> fileHashedPassword) {
            if (fileUsername == username) {
                if (fileHashedPassword == hashedPassword) {
                    std::cout << "Login successful!" << std::endl;
                    return true;
                }
                else {
                    std::cout << "Incorrect password!" << std::endl;
                    system("PAUSE");
                    return false;
                }
            }
        }
    }
    std::cout << "User not found!" << std::endl;
    system("PAUSE");
    return false;
}

void Admin::run(const std::string& username, const std::string& password) {
    if (adminLogin(username, password)) {
        system("PAUSE");
        int admin_choice;
    label_3:
        system("CLS");
        std::cout << "\t\t\t------------------------------------------------------------\n";
        std::cout << "\t\t\t                           ADMIN MENUE                      \n";
        std::cout << "\t\t\t------------------------------------------------------------\n";
        std::cout << "\t\t\t  1)  Register New Employee                                 \n";
        std::cout << "\t\t\t  2)  Remove Employee                                       \n";
        std::cout << "\t\t\t  3)  View All Employee                                     \n";
        std::cout << "\t\t\t  4)  Back                                                  \n";

        if (std::cin >> admin_choice) {
            switch (admin_choice) {
            case 1:
                registerEmployee();
                break;
            case 2:
                removeEmployee();
                break;
            case 3:
                viewAllEmployee();
                break;
            case 4:
                return;
            default:
                std::cout << "Please enter valid input\n";
                system("PAUSE");
            }
            goto label_3;
        }
        else {
            std::cerr << "Error: Reading input" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            goto label_3;
        }
    }
    else {
        return;
    }
}


void Admin::registerEmployee() {

    system("CLS");
    std::cout << "enter Employee Id : ";
    if (std::cin >> employeeId);
    else {
        std::cerr << "Error: Reading input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("pause");
        return;
    }
    std::cout << "Enter Employee Name : ";
    if (std::cin >> employeeName);
    else {
        std::cerr << "Error: Reading input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("pause");
        return;
    }
    std::cout << "Enter Employee username : ";
    if (std::cin >> employeeUsername);
    else {
        std::cerr << "Error: Reading input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("pause");
        return;
    }
    std::cout << "Enter Employee password :  ";
    if (std::cin >> employeePassword);
    else {
        std::cerr << "Error: Reading input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("pause");
        return;
    }
    // hashing employee's password
    std::string hashed_employee_password = hashPassword(employeePassword);

    //inserting value in the database
    sqlite3_stmt* myStatement;
    std::string sql = "INSERT INTO employee VALUES(?,?,?,?);";
       
    int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);
    try {
        if (statusOfPrep != SQLITE_OK) {
            throw (std::string)"Error : Preparing Statement";
        }
        sqlite3_bind_int(myStatement, 1, employeeId);
        sqlite3_bind_text(myStatement, 2, employeeName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(myStatement, 3, employeeUsername.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(myStatement, 4, hashed_employee_password.c_str(), -1, SQLITE_STATIC);

        bool querySuccess = executeQueryNoResultsBack(myStatement);


        try {
            if (querySuccess == false) {
                throw (std::string)"Error : Adding employee";
            }
            std::cout << "Emloyee added successfully\n";
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

//delete employee
void Admin::removeEmployee() {
    system("CLS");
    sqlite3_stmt* myStatement;

    std::string sql = "SELECT employee.id, employee.name, employee.username FROM employee ORDER BY employee.id;";

    try {
        bool preparingSuccess = prepareQueryWithResults(sql, myStatement);
        if (preparingSuccess == false) {
            throw (std::string)"Error : Preparing Query";
        }
        int statusOfStep = sqlite3_step(myStatement);
        while (statusOfStep == SQLITE_ROW) {

            employeeId = sqlite3_column_int(myStatement, 0);
            employeeName = (char*)sqlite3_column_text(myStatement, 1);
            employeeUsername = (char*)sqlite3_column_text(myStatement, 2);

            std::cout << "---------------------------" << "\n";
            std::cout << "Id : " << employeeId << "\n";
            std::cout << "Name : " << employeeName << "\n";
            std::cout << "Username : " << employeeUsername << "\n";
            statusOfStep = sqlite3_step(myStatement);
        }
        sqlite3_finalize(myStatement);
        int delEmpId;
        std::cout << "\nEnter id of employee to be deleted : \n";
        if (std::cin >> delEmpId);
        else {
            std::cerr << "Error: Reading input" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("pause");
            return;
        }
        sql = "DELETE FROM employee WHERE id = (?);";
        int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);


        try {
            if (statusOfPrep != SQLITE_OK) {
                throw (std::string)"Error : Preparing Statement";
            }
            sqlite3_bind_int(myStatement, 1, delEmpId);
            bool querySuccess = executeQueryNoResultsBack(myStatement);

            try {
                if (querySuccess == false) {
                    throw (std::string)"Error : Removing employee";
                }
                std::cout << "Emloyee removed successfully\n";
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


void Admin::viewAllEmployee() {
    system("CLS");
    std::cout << "\nAll employee\n";
    std::string sql = "SELECT employee.id, employee.name, employee.username FROM employee ORDER BY employee.id";
    sqlite3_stmt* myStatement;
    try {
        bool preparingSuccess = prepareQueryWithResults(sql, myStatement);
        if (preparingSuccess == false) {
            throw (std::string)"Error : Preparing Query";
        }
        int statusOfStep = sqlite3_step(myStatement);
        while (statusOfStep == SQLITE_ROW) {

            employeeId = sqlite3_column_int(myStatement, 0);
            employeeName = (char*)sqlite3_column_text(myStatement, 1);
            employeeUsername = (char*)sqlite3_column_text(myStatement, 2);

            std::cout << "---------------------------" << "\n";
            std::cout << "Id : " << employeeId<< "\n";
            std::cout << "Name : " << employeeName << "\n";
            std::cout << "Username : " << employeeUsername << "\n";
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