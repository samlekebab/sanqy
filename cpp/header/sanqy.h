#pragma once

void openDatabase(const char *);
void closeDatabase();

//return weather database is open
bool insertCard(const char *, const char *);
const char* dumpDatabase();
