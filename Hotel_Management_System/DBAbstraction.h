/*
author      :   saad khan
project     :   Hotel Management System
date        :   April-2023
*/

#pragma once
#include<string>
#include"sqlite3.h"

class DBAbstraction {

public:
	DBAbstraction();
	~DBAbstraction();

protected:
	sqlite3* db;

	bool executeQueryNoResultsBack(sqlite3_stmt* myStatement);
	bool executeQueryNoResultsBack(std::string sql);
	bool prepareQueryWithResults(std::string sql, sqlite3_stmt*& myStatement);

};
