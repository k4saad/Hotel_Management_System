/*
author      :   saad khan
project     :   Hotel Management System
date        :   April-2023
*/

#include<iostream>
#include<stdio.h>
#include"Room.h"
void Room::run() {

    int employee_choice;
label_5:
    system("CLS");
    std::cout << "\t\t\t------------------------------------------------------------\n";
    std::cout << "\t\t\t                            ROOM                            \n";
    std::cout << "\t\t\t------------------------------------------------------------\n";
    std::cout << "\t\t\t  1)  Add Room                                              \n";
    std::cout << "\t\t\t  2)  Delete Room                                           \n";
    std::cout << "\t\t\t  3)  All Room                                              \n";
    std::cout << "\t\t\t  4)  Back                                                  \n";
    if (std::cin >> employee_choice) {
        switch (employee_choice) {
        case 1:
            addRoom();
            break;
        case 2:
            deleteRoom();
            break;
        case 3:
            viewAllRoom();
            break;
        case 4:
            return;
        default:
            std::cout << "Please enter valid input\n";
            system("PAUSE");
        }
        goto label_5;
    }
    else {
        std::cerr << "Error: Reading input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("PAUSE");
        goto label_5;
    }
}
void Room::addRoom() {
    system("CLS");
    std::cout << "\t\t\t---Enter room details---\n";
    std::cout << "Room id : \n";
    if (std::cin >> roomId);
    else {
        std::cerr << "Error: Reading input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("pause");
        return;
    }
    std::cout << "Room name : \n";
    std::cin.ignore();
    if (getline(std::cin,roomName));
    else {
        std::cerr << "Error: Reading input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("pause");
        return;
    }
    std::cout << "Room capacity : \n";
    if (std::cin >> roomCapacity);
    else {
        std::cerr << "Error: Reading input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("pause");
        return;
    }
    std::cout << "Room rate/night : \n";
    if(std::cin >> roomPrice);
    else {
        std::cerr << "Error: Reading input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("pause");
        return;
    }
    std::cout << "Room Size : \n";
    if(std::cin >> roomSize);
    else {
        std::cerr << "Error: Reading input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("pause");
        return;
    }
    std::cout << "Room Bed Size (king/queen): \n";
    if (std::cin >> roomBedSize);
    else {
        std::cerr << "Error: Reading input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("pause");
        return;
    }
    std::cout << "Room Discription : \n";
    std::cin.ignore();
    if (getline(std::cin, roomDiscription));
    else {
        std::cerr << "Error: Reading input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("pause");
        return;
    }

    sqlite3_stmt* myStatement;
    std::string sql = "INSERT INTO room VALUES(?,?,?,?,?,?,?);";
    int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);
    try {
        if (statusOfPrep != SQLITE_OK) {
            throw (std::string)"Error : Preparing Statement";
        }
        sqlite3_bind_int(myStatement, 1, roomId);
        sqlite3_bind_text(myStatement, 2, roomName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(myStatement, 3, roomCapacity);
        sqlite3_bind_int(myStatement, 4, roomPrice);
        sqlite3_bind_int(myStatement, 5, roomSize);
        sqlite3_bind_text(myStatement, 6, roomBedSize.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(myStatement, 7, roomDiscription.c_str(), -1, SQLITE_STATIC);

        bool querySuccess = executeQueryNoResultsBack(myStatement);
        
        try {
            if (querySuccess == false) {
                throw (std::string)"Error : Adding room";
            }
            std::cout << "Room added successfully\n";
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
void Room::deleteRoom() {
    system("CLS");
    sqlite3_stmt* myStatement;
    std::string sql = "SELECT room.id, room.name, room.capacity, room.price, room.roomsize, room.bedsize, room.discription FROM room ORDER BY room.id;";
    try {
        bool preparingSuccess = prepareQueryWithResults(sql, myStatement);
        if (preparingSuccess == false) {
            throw (std::string)"Error : Preparing Query";
        }
        int statusOfStep = sqlite3_step(myStatement);
        while (statusOfStep == SQLITE_ROW) {
            roomId = sqlite3_column_int(myStatement, 0);
            roomName = (char*)sqlite3_column_text(myStatement, 1);
            roomCapacity = sqlite3_column_int(myStatement, 2);
            roomPrice = sqlite3_column_int(myStatement, 3);
            roomSize = sqlite3_column_int(myStatement, 4);
            roomBedSize = (char*)sqlite3_column_text(myStatement, 5);
            roomDiscription = (char*)sqlite3_column_text(myStatement, 6);

            std::cout << "---------------------------\n";
            std::cout << "Room id : " << roomId <<"\n";
            std::cout << "Room name : " << roomName <<"\n";
            std::cout << "Room capacity : " << roomCapacity << " guests\n";
            std::cout << "Room price : " << roomPrice << " Rupees / night\n";
            std::cout << "Room size : " << roomSize << " sq mt\n";
            std::cout << "Bed size : " << roomBedSize << " size\n";
            std::cout << "Room Discription : " << roomDiscription <<"\n";
            statusOfStep = sqlite3_step(myStatement);
        }
        int rId;
        std::cout << "\nEnter id of room to be deleted : \n";
        if (std::cin >> rId);
        else {
            std::cerr << "Error: Reading input" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("pause");
            return;
        }
        sql = "DELETE FROM room WHERE id = (?);";
        int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

        try {
            if (statusOfPrep != SQLITE_OK) {
                throw (std::string)"Error : Preparing Statement";
            }
            sqlite3_bind_int(myStatement, 1, rId);
            bool querySuccess = executeQueryNoResultsBack(myStatement);
            try {
                if (querySuccess == false) {
                    throw (std::string)"Error : Removing room";
                }
                std::cout << "Room removed successfully\n";
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
void Room::viewAllRoom() {
    system("CLS");
    std::cout << "\nAll room\n";
    std::string sql = "SELECT room.id, room.name, room.capacity, room.price, room.roomsize, room.bedsize, room.discription FROM room ORDER BY room.id";
    sqlite3_stmt* myStatement;
    try {
        bool preparingSuccess = prepareQueryWithResults(sql, myStatement);
        if (preparingSuccess == false) {
            throw (std::string)"Error : Preparing Query";
        }
        int statusOfStep = sqlite3_step(myStatement);
        while (statusOfStep == SQLITE_ROW) {
            roomId = sqlite3_column_int(myStatement, 0);
            roomName = (char*)sqlite3_column_text(myStatement, 1);
            roomCapacity = sqlite3_column_int(myStatement, 2);
            roomPrice = sqlite3_column_int(myStatement, 3);
            roomSize = sqlite3_column_int(myStatement, 4);
            roomBedSize = (char*)sqlite3_column_text(myStatement, 5);
            roomDiscription = (char*)sqlite3_column_text(myStatement, 6);

            std::cout << "---------------------------\n";
            std::cout << "Room id : " << roomId << "\n";
            std::cout << "Room name : " << roomName << "\n";
            std::cout << "Room capacity : " << roomCapacity << " guests\n";
            std::cout << "Room price : " << roomPrice << " Rupees / night\n";
            std::cout << "Room size : " << roomSize << " sq mt\n";
            std::cout << "Bed size : " << roomBedSize << " size\n";
            std::cout << "Room Discription : " << roomDiscription << "\n";
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