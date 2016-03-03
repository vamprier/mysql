#ifndef MYSQL_H
#define MYSQL_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <mysql/mysql.h>

using namespace std;


string readData(	const string& hostName,
					const string& dbName,
					const string& userName,
					const string& password,
					const int& port,
					const string& query,
					vector< vector<string> >& dataSet);

string writeData(	const string& hostName,
					const string& dbName,
					const string& userName,
					const string& password,
					const int& port,
					const vector<string>& querySet);

string deleteData(	const string& hostName,
					const string& dbName,
					const string& userName,
					const string& password,
					const int& port,
					const string& query);

#endif
