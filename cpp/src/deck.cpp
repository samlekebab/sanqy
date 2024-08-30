#include "deck.h"
#include "card.h"

void Deck::scheduleNewCard(CardNodeRP cardNodeRP){
	//the card is new, so we expect it to be
	//shown immediatly
	cardNodeRP.getCardNode()->revisionTime = 0;

	//we push it (to the random pull)
	this->push(cardNodeRP);
}
void Deck::rebuildHeaps(){
	Heap::resetLUT();
	randomPool.heap.n=0;
	todayHeap.n=0;

	TwoCards* cards;
	int count = cardDatabase.getTwoCardArray(&cards,0);
	for (int i=0; i<count; i++){
		CardNodeRP cardNodeFront = Heap::lut
			.createCardNode(cards[i].front.uid);
		CardNodeRP cardNodeBack = Heap::lut
			.createCardNode(cards[i].back.uid);
		cardNodeFront.getCardNode()->revisionTime = 
			cards[i].front.revisionTime;
		cardNodeBack.getCardNode()->revisionTime = 
			cards[i].back.revisionTime;

		push(cardNodeFront);
		push(cardNodeBack);
	}
	delete[] cards;

	randomPool.chooseNext();

}
void Deck::removeFromHeap(int uid){
	CardNodeRP cardNode = Heap::lut.getCardNode(uid);
	Heap* h = cardNode.getCardNode()->heap;
	int  hPosition = cardNode.getCardNode()->heapPosition;
	h->pop(hPosition);
}

void Deck::rescheduleTopCard(const Option* option, int time){
	int revisionTime = option->time+time;
	//if inteval over a day,
	//we set revisionTime to a common time of given a given day
	//i.e. on the time of day of the 0
	revisionTime = option->time < 1440 ? revisionTime : (revisionTime/1440)*1440;
	CardNodeRP toReschedule = pop();
	
	//change the heaps
	toReschedule.getCardNode()->revisionTime = revisionTime;
	push(toReschedule);//TODO use two heap

	//update the database
	cardDatabase.setCardOption(revisionTime,option,toReschedule.getCardNode()->uid);
}


bool Deck::isEmpty(){
	return (randomPool.heap.isEmpty() 
		|| dailyStatus.dailyStatusStruct.nbNewCards >= newCardLimit)
		&& todayHeap.isEmpty();
}
CardNodeRP Deck::view(){
	if (!randomPool.heap.isEmpty() && 
		dailyStatus.dailyStatusStruct.nbNewCards < newCardLimit)
		return randomPool.viewRandom();
	return todayHeap.view();
}
CardNodeRP Deck::pop(){
	if (!randomPool.heap.isEmpty() && 
		dailyStatus.dailyStatusStruct.nbNewCards < newCardLimit){
		dailyStatus.dailyStatusStruct.nbNewCards ++;
		dailyStatus.saveStatus();
		return randomPool.popRandom();
	}
	dailyRevisionAvailableCounter--;
	return todayHeap.pop();
}
void Deck::push(CardNodeRP cardNode){
	if (cardNode.getCardNode()->revisionTime <=0){
		randomPool.heap.push(cardNode);
	}else{
		if (cardNode.getCardNode()->revisionTime/1440
				<=dailyStatus.dailyStatusStruct.time/1440){
			dailyRevisionAvailableCounter++;
		}
		todayHeap.push(cardNode);
	}


}
