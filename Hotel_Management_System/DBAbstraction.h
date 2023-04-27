#pragma once
#include<string>
#include"sqlite3.h"

class DBAbstraction {

public:
	DBAbstraction(std::string pathToFile);
	~DBAbstraction();

protected:
	sqlite3* db;

	bool executeQueryNoResultsBack(sqlite3_stmt* myStatement);
	bool executeQueryNoResultsBack(std::string sql);
	bool prepareQueryWithResults(std::string sql, sqlite3_stmt*& myStatement);

};
