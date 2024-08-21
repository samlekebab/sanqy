#include "lut.h"
#include <cstring>
#include "heap.h"

CardNode* CardNodeRP::getCardNode(){
	size_t ret = ((size_t)Heap::lut.cardNodeArray +(size_t) RP);
	return (CardNode*) ret;
}
void CardNodeRP::setCardNode(CardNode* cardNode){
	size_t res = (size_t)cardNode - (size_t)Heap::lut.cardNodeArray;
	RP = (void*) res;
}
CardNodeRP::CardNodeRP(CardNode* c){
	setCardNode(c);
}
CardNodeRP::CardNodeRP(){}
LUT::LUT(){
	cardNodeArray=new CardNodeList[maxSize];
	cardNodeArray[0].next = CardNodeRP();//empty RP
	size++;
	for (int i=0;i<LUT_MOD_SIZE;i++){
		cardNodeListRPArray[i] = 
			CardNodeRP(& cardNodeArray[0].item);
	}
}
LUT::~LUT(){
	delete[] cardNodeArray;
}
CardNodeRP LUT::getCardNode(int uid){
	int i = uid%LUT_MOD_SIZE;
	CardNodeList* l;
	for (l = (CardNodeList*) cardNodeListRPArray[i].getCardNode();
		l->next.RP != (void*)-1;
		l = (CardNodeList*)l->next.getCardNode()){

		if (l->item.uid==uid){
			CardNodeRP ret;
			ret.setCardNode(&l->item);
			return ret;
		}
	}
	//TODO error
	return CardNodeRP();
}

CardNodeRP LUT::createCardNode(int uid){
	int i = uid%LUT_MOD_SIZE;
	if (size>=maxSize){
		CardNodeList* newCardNodeArray = new CardNodeList[maxSize*2];
		memcpy(newCardNodeArray,cardNodeArray,
				size*sizeof(CardNodeList));
		delete[] cardNodeArray;
		cardNodeArray = newCardNodeArray;
		maxSize *= 2;
		
	}
	//get a new CardNode 
	CardNodeList* cl = &cardNodeArray[size];
	CardNode* c = & cl->item;
	size++;

	//partial initialisation
	c->uid = uid;

	//insert in the LUT
	cl->next = cardNodeListRPArray[i];
	CardNodeRP ret{c};
	cardNodeListRPArray[i] = ret;

	return ret;
}
