#pragma once
#define EXPORT extern "C" __attribute__((visibility("default"))) __attribute__((used))

#include <string>
#include "status.h"

std::string dumpDatabase(void*);

EXPORT
void* openDatabase(const char *, int);
EXPORT
void closeDatabase(void*);


//return weather database is open
EXPORT
bool insertCard(void* voidDeck,const char* fwrd, const char* bwrd);

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
void revisionCallBack(void* voidDeck, int no, int time);

EXPORT
void modifyCard(void* voidDeck,char* newWord,int uid);

EXPORT
void resetAllCards(void* handler);

EXPORT 
void getCardWord(void* handler,int uid, char* ret);

extern "C" {
struct TwoInt{
	int one;
	int two;
};

struct TestStruct{
	int mInt;
};
}

EXPORT
TestStruct testStruct();

EXPORT 
int getCardsUids(void* handler, TwoInt**);

EXPORT
void invalidateCardsUids(TwoInt* uids);
