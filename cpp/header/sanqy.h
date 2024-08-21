#pragma once
#define EXPORT extern "C" __attribute__((visibility("default"))) __attribute__((used))

#include <string>
#include "status.h"

std::string dumpDatabase(void*);

EXPORT
int hello();

EXPORT
void* openDatabase(const char *, int);
EXPORT
void closeDatabase(void*);


//return weather database is open
EXPORT
bool insertCard(void* voidDeck,const std::string &fwrd, const std::string &bwrd);

EXPORT
bool deleteCard(void* voidDeck, int uid);

EXPORT
bool isRevisionAvailable(void* voidDeck,int time);

EXPORT
void getRevisionFront(void* handler,char* ret);

EXPORT
void getRevisionBack(void* handler,char* ret);

EXPORT
Options getOptions(void* voidDeck);

EXPORT
void revisionCallBack(void* voidDeck,Options options, int no, int time);

EXPORT
void modifyCard(void* voidDeck,char* newWord,int uid);

EXPORT
void resetAllCards(void* handler);
