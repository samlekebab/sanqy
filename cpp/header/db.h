#pragma once
#include "SQLiteCpp.h"

class CardDataBase 
{
public:
	SQLite::Database sqLiteDb;
	CardDataBase(const char * file);
};

