#include <stdio.h>
#include "SQLiteCpp.h"
#include <iostream>
#include "db.h"
int main(){
	CardDataBase cardDataBase("test.db3");
//
//	printf("\nhello sanqy\n");
//	try
//	{
//		// Open a database file
//		SQLite::Database    db("example.db3",  SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
//
//		// Compile a SQL query, containing one parameter (index 1)
//		SQLite::Statement   query(db, "SELECT * FROM test");
//
////		// Bind the integer value 6 to the first parameter of the SQL query
////		query.bind(1, 6);
//
//		// Loop to execute the query step by step, to get rows of result
//		while (query.executeStep())
//		{
//			// Demonstrate how to get some typed column value
//			int         id      = query.getColumn(0);
//			const char* value   = query.getColumn(1);
//
//			std::cout << "row: " << id << ", " << value <<std::endl;
//		}
//	}
//	catch (std::exception& e)
//	{
//		std::cout << "exception: " << e.what() << std::endl;
//	}
	return 0;
}
