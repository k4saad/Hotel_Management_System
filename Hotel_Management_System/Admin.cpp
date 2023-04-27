#include <string>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <sha.h>
#include <hex.h>
#include"Admin.h"
#include"DBAbstraction.h"

Admin::Admin() {
    if(!checkUsername("saad")) registerUser("saad", "123123");

}
bool Admin::registerUser(const std::string& username, const std::string& password) {
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
                    return false;
                }
            }
        }
    }
    std::cout << "User not found!" << std::endl;
    return false;
}