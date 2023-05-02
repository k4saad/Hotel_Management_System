/*
author      :   saad khan
project     :   Hotel Management System
date        :   April-2023
*/

#include<iostream>
#include<stdio.h>
#include<iomanip>
#include"Room.h"
void Room::employeeRun() {

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
        sqlite3_finalize(myStatement);
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
        sqlite3_finalize(myStatement);
        system("PAUSE");
    }
    catch (std::string e) {
        std::cerr << e << std::endl;
        system("PAUSE");
        return;
    }
}
void Room::bookRoom() {
    int noOfGuest;
label_7:
    system("CLS");
    std::cout << "Number of Guest : \n";
    if(std::cin >> noOfGuest);
    else {
        std::cerr << "Error: Reading input" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter valid number of guests\n";
        system("PAUSE");
        goto label_7;
    }
    sqlite3_stmt* myStatement;
    std::string sql = "SELECT room.id, room.name, room.capacity, room.price, room.roomsize, room.bedsize, room.discription FROM room WHERE room.capacity >= (?) ORDER BY room.capacity;";
    int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);
    try {
        if (statusOfPrep != SQLITE_OK) {
            throw (std::string)"Something went wrong ";
        }
        sqlite3_bind_int(myStatement, 1, noOfGuest);
        int statusOfStep = sqlite3_step(myStatement);
        std::cout << "\n\n+---------------------------AVAILABLE ROOMS---------------------------+\n";
        if (statusOfStep != SQLITE_ROW) {
            std::cout << "No room available\n";
            return;
        }
        else {
            while (statusOfStep == SQLITE_ROW) {
                roomId = sqlite3_column_int(myStatement, 0);
                roomName = (char*)sqlite3_column_text(myStatement, 1);
                roomCapacity = sqlite3_column_int(myStatement, 2);
                roomPrice = sqlite3_column_int(myStatement, 3);
                roomSize = sqlite3_column_int(myStatement, 4);
                roomBedSize = (char*)sqlite3_column_text(myStatement, 5);
                roomDiscription = (char*)sqlite3_column_text(myStatement, 6);

                std::cout << "Room id : " << roomId << "\tName : " << roomName << "\n";
                std::cout << "\t\tcapacity : " << roomCapacity << " guests\n";
                std::cout << "\t\tprice : " << roomPrice << " rupees / night\n";
                std::cout << "\t\tsize : " << roomSize << " sq mt\n";
                std::cout << "\t\tBed size : " << roomBedSize << " size\n";
                std::cout << "\t\tDiscription: " << roomDiscription << "\n";
                std::cout << "---------------------------+\n";

                statusOfStep = sqlite3_step(myStatement);
            }
        }
        sqlite3_finalize(myStatement);
        std::cout << "+-----------------------------------------------------------------------+\n\n\n";
        int crId = 0, numberOfNight, customerChoice;
        std::cout << "\nEnter 0 to retrun back or 1 to continue :  \n";
        if(std::cin >> customerChoice);
        else {
            std::cerr << "Error: Reading input" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("PAUSE");
            return;
        }
        if (customerChoice == 0) {
            return;
        }
        std::cout << "Enter room id : \n";
        if(std::cin >> crId);
        else {
            std::cerr << "Error: Reading input" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("PAUSE");
            return;
        }
        std::cout << "Number of night : \n";
        if(std::cin >> numberOfNight);
        else {
            std::cerr << "Error: Reading input" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("PAUSE");
            return;
        }

        int crPrice;
        std::string crName;

        sql = "SELECT room.name, room.price FROM room WHERE room.id = (?);";
        statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);
        try {
            if (statusOfPrep != SQLITE_OK) {
                throw (std::string)"Something went wrong ";
            }
            sqlite3_bind_int(myStatement, 1, crId);

            int statusOfStep = sqlite3_step(myStatement);
            if (statusOfStep == SQLITE_ROW) {
                crName = (char*)sqlite3_column_text(myStatement, 0);
                crPrice = sqlite3_column_int(myStatement, 1);
                sqlite3_finalize(myStatement);
                std::string dept = "room";
                sql = "INSERT INTO income VALUES(?,?,?,?);";
                statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);
                try {
                    if (statusOfPrep != SQLITE_OK) {
                        throw (std::string)"Something went wrong ";
                    }
                    sqlite3_bind_text(myStatement, 1, crName.c_str(), -1, SQLITE_STATIC);
                    sqlite3_bind_int(myStatement, 2, numberOfNight);
                    sqlite3_bind_int(myStatement, 3, crPrice);
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
                system("CLS");
                std::cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                std::cout << "\t|" << std::setw(36) << "      RECIPT " << std::setw(27) << "|\n";
                std::cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                std::cout << "\tRoom : " << crName << "\n";
                std::cout << "\tPrice : " << crPrice << " rupees / night\n";
                std::cout << "\tNumber of night : " << numberOfNight << "\n";
                std::cout << "\tTotal payable amount : " << crPrice * numberOfNight << "\n";
                std::cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                std::cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                system("PAUSE");

            }
            else {
                std::cout << "No room with room id " << crId << " found\n";
                sqlite3_finalize(myStatement);
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