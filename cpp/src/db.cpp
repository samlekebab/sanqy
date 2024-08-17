#include "db.h"
#include <iostream>

CardDataBase::CardDataBase(const char * file):
	sqLiteDb(file,SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE)
{

	//initialize if this is the creation of the db
	//query the existance of the card table
	bool isTableCard;
	SQLite::Statement   query(sqLiteDb,
		"""SELECT name FROM sqlite_master \
		WHERE type='table' AND name='card'""");
	query.executeStep();
	isTableCard = query.hasRow();
	if (!isTableCard){
		printf("creating the card table\n");
		SQLite::Statement(sqLiteDb,
			""" CREATE TABLE card \
			(uid INTEGER PRIMARY KEY,\
			 word TEXT,\
			 face INTEGER,\
			 mate INTEGER,\
			 status TEXT,\
			 revisionTime INTEGER,\
			 shown INTEGER,\
			 failed INTEGER)""").exec();

	}
	    
	    
	//TODO

}
