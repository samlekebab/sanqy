#pragma once
#include "def.h"

class Heap;
struct CardNode{
	int uid;
	int revisionTime;
	int heapPosition;
	Heap* heap;
};
//relative pointer to cardNode
class CardNodeRP{
public:
	void* RP = (void*)-1;//relative pointer
	CardNode* getCardNode();
	void setCardNode(CardNode*);
	CardNodeRP(CardNode*);
	CardNodeRP();

};
struct CardNodeList{//POD
	CardNode item;//need to be on first position 
	CardNodeRP next;
};
class LUT{
public:
	CardNodeList* cardNodeArray;//TODO rename
	int size=0;
	int maxSize=1;
	CardNodeRP cardNodeListRPArray[LUT_MOD_SIZE];
	LUT();
	~LUT();
	CardNodeRP createCardNode(int uid);
	CardNodeRP getCardNode(int uid);
};
