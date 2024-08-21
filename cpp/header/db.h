#pragma once
#include "SQLiteCpp.h"
#include "card.h"
#include "status.h"

class CardDatabase 
{
public:
	SQLite::Database sqLiteDb;
	CardDatabase(const char * file);
	void insertCard(TwoCards& card);
	Card getCard(int cardID);
	int getTwoCardArray(TwoCards** ret,int face);
	int insertRow(const Card& card, int mate);
	void setRowMate(int uid, int mate);
	int deleteCardAndMate(int uid);
	void setCardOption(const Option* option, int uid);
	void setCardOption(int revisionTime, const Option* option, int uid);
	void updateCard(char* newWord,int uid);
	void resetAllCards(const char* status, int revTime);
};

