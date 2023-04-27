#include<iostream>
#include<string>
#include<sqlite3.h>
#include<iostream>
#include<string>
#include"Admin.h"

template<class T>
class Hotel {

public:
	void login(T&);
	Hotel() = default;
	void run();
};

template<class T>
void Hotel<T>::login(T& A) {
	std::string username, password;
	std::cout << "username : ";
	std::cin >> username;
	std::cout << "password : ";
	std::cin >> password;
	if (!A.adminLogin(username, password)){
		
	}
}
template<class T>
void Hotel<T>::run() {
	T temp;
	login(temp);
}
int main() {
	Hotel<Admin>().run();
}