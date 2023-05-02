/*
author      :   saad khan
project     :   Hotel Management System
date        :   April-2023
*/

#pragma once
#include<string>
#include"Hotel.h"
class Room : public Hotel{
    int roomId, roomSize, roomCapacity, roomPrice;
    std::string roomName, roomDiscription, roomBedSize;
    void addRoom();
    void deleteRoom();
    void viewAllRoom();

public:
    void employeeRun();
    void bookRoom();
};