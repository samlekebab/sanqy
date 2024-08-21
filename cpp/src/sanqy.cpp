#include "sanqy.h"
#include "db.h"
#include "deck.h"
#include "def.h"
#include <string>
#include <stdio.h>
#include "random_pool.h"

EXPORT
int hello(){
	printf("hello\n");
	return 43;
}

EXPORT
void* openDatabase(const char* file,int time){
	hello();
	std::string dbFile{file};
	dbFile += ".db3";
	std::string dailyStatusFile{file};
	dailyStatusFile += ".status";
	Deck* deck = new Deck{
		DailyStatus(dailyStatusFile, time),
		RandomPool{},
		Heap(),//TODO open heap in storage
		//opening the database
		CardDatabase(dbFile.c_str())
	};

	//TODO make heap read from file
	//DEBUG for now we just recreate the heap 
	//on every opening of the db
	deck->rebuildHeaps();

	return deck;
}
void closeDatabase(void * deck){
	delete (Deck*)deck;
}
bool deleteCard(void* voidDeck, int uid){
	if (voidDeck==nullptr){
		return 1;
	}
	auto deck = (Deck*)voidDeck;
	CardDatabase& db = deck->cardDatabase;
	int mateUid = db.deleteCardAndMate(uid);
	
	//delete from heap using lut
	deck->removeFromHeap(uid);
	deck->removeFromHeap(mateUid);
	

	return 0;

}
bool insertCard(void* voidDeck,const std::string &fwrd, const std::string &bwrd){

	if (voidDeck==nullptr){
		return 1;
	}
	auto deck = (Deck*)voidDeck;
	CardDatabase& db = deck->cardDatabase;
	
	//put the card in the db
	TwoCards card{
		Card{
			0,
			fwrd,
			0,
			0,
			STATUS_LEARNING,
			0,
			0,
			0
			},
		Card{
			0,
			bwrd,
			0,
			1,
			STATUS_LEARNING,
			0,
			0,
			0
			}
	};
	db.insertCard(card);
	

	//schedule it in the heap
	CardNodeRP cardNodeFront = Heap::lut.createCardNode(card.front.uid);
	CardNodeRP cardNodeBack = Heap::lut.createCardNode(card.back.uid);
	deck->scheduleNewCard(cardNodeFront);
	deck->scheduleNewCard(cardNodeBack);

	
	
	return 0;
}
std::string dumpDatabase(void* voidDeck){
	if (voidDeck==nullptr){
		return "";
	}
	auto deck = (Deck*)voidDeck;
	CardDatabase& db = deck->cardDatabase;
	TwoCards* cards;
	std::string result{""};
	int count = db.getTwoCardArray(&cards,0);
	char line[MAX_WORD*2 + 100];
	for(int j=0;j<count;j++){
		std::sprintf(line,"%d : %s | %s : %d\n",
			cards[j].front.uid,
			cards[j].front.word.c_str(),
			cards[j].back.word.c_str(),
			cards[j].back.uid);
		result += line;
	}

	delete[] cards;
	return result;
}
EXPORT
void getRevisionFront(void* voidDeck,char* ret){

	if (voidDeck==nullptr){
		sprintf(ret,"XXX");
		return;
	}
	auto deck = (Deck*)voidDeck;
	CardNodeRP next = deck->view();
	Card card = deck->cardDatabase.getCard(next.getCardNode()->uid);
	sprintf(ret,"%s",card.word.c_str());

}

EXPORT
void getRevisionBack(void* voidDeck,char* ret){

	if (voidDeck==nullptr){
		sprintf(ret,"YYY");
		return;
	}
	auto deck = (Deck*)voidDeck;
	CardNodeRP next = deck->view();
	Card card = deck->cardDatabase.getCard(next.getCardNode()->uid);
	Card back = deck->cardDatabase.getCard(card.mateUid);
	sprintf(ret,"%s",back.word.c_str());

}
EXPORT
bool isRevisionAvailable(void* voidDeck,int time){
	if (voidDeck==nullptr){
		return false;
	}
	auto deck = (Deck*)voidDeck;
	
	if (deck->isEmpty())
		return false;
	

	//get the next card and check the revisionTime
	CardNodeRP next = deck->view();
	int revTime = next.getCardNode()->revisionTime;
	bool ret = revTime < time+DELAY_REV_MARGIN;
	return ret;
}
void revisionCallBack(void* voidDeck,Options options, int no, int time){
	if (voidDeck==nullptr){
		return;
	}
	auto deck = (Deck*)voidDeck;
	Option* option =& ((Option*)(&options))[no-1];
	
	
	//TODO count unique uids for number of card of the day
	
	//update the heap and database
	deck->rescheduleTopCard(option,time);
}
EXPORT
Options getOptions(void* voidDeck){
	if (voidDeck==nullptr){
		return Options();
	}
	auto deck = (Deck*)voidDeck;
	Card card = deck->cardDatabase.getCard(
			deck->view().getCardNode()->uid);
	return makeOptions(&card);
}

EXPORT
void modifyCard(void* voidDeck,char* newWord,int uid){
	if (voidDeck==nullptr){
		return;
	}
	auto deck = (Deck*)voidDeck;
	deck->cardDatabase.updateCard(newWord,uid);

}
void resetAllCards(void* voidDeck){
	if (voidDeck==nullptr){
		return;
	}
	auto deck = (Deck*)voidDeck;
	deck->cardDatabase.resetAllCards(STATUS_LEARNING,0);
	deck->rebuildHeaps();

}
