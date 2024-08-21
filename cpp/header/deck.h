#pragma once
#include "db.h"
#include "heap.h"
#include "status.h"
#include "daily_status.h"
#include "random_pool.h"
class Deck{
public:
	DailyStatus dailyStatus;
	RandomPool randomPool;
	Heap todayHeap;
	CardDatabase cardDatabase;

	int newCardLimit=NEW_CARD_LIMIT;

	Card* getTopCard();
	void rescheduleTopCard(const Option* option, int time);
	void scheduleNewCard(CardNodeRP cardNode);
	void rebuildHeaps();
	void removeFromHeap(int uid);

	CardNodeRP view();
	CardNodeRP pop();
	void push(CardNodeRP);
	bool isEmpty();
	
};

