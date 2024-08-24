#include "status.h"
#include "card.h"
#include <cstring>
COptions learning(Card* card){
	COptions ret;
	ret.option1.time = 1;
	sprintf(ret.option1.str,"again 1m");
	sprintf(ret.option1.status,STATUS_LEARNING);
	ret.option1.shown = 0;
	ret.option1.failed = card->failed;

	ret.option4.time = 1440*4;
	sprintf(ret.option4.str,"super easy 4d");
	sprintf(ret.option4.status,STATUS_KNOWN_EASY);
	ret.option4.shown = 1;
	ret.option4.failed = card->failed;

	if (card->shown == 0){
		ret.option3.time = 10;
		sprintf(ret.option3.str,"good 10m");
		sprintf(ret.option3.status,STATUS_LEARNING);
		ret.option3.shown = 1;
		ret.option3.failed = card->failed;

	}
	else if(card->shown == 1) {
		ret.option2.time = 10;
		sprintf(ret.option2.str,"hard 10m");
		sprintf(ret.option2.status,STATUS_LEARNING);
		ret.option2.shown = 1;
		ret.option2.failed = card->failed;


		ret.option3.time = 1440;
		sprintf(ret.option3.str,"good 1d");
		sprintf(ret.option3.status,STATUS_KNOWN_NORMAL);
		ret.option3.shown = 1;
		ret.option3.failed = card->failed;
	}

	return ret;
}
COptions known(Card* card, int easeFactor){
	COptions ret;
	ret.option1.time = 1;
	sprintf(ret.option1.str,"again 1m");
	sprintf(ret.option1.status,STATUS_RELEARNING);
	ret.option1.shown = card->shown>1?card->shown/2:1;
	ret.option1.failed = card->failed+1;

	ret.option2.time = 1440*1;
	sprintf(ret.option2.str,"hard %dd",ret.option2.time/1440);
	sprintf(ret.option2.status,STATUS_KNOWN_HARD);
	ret.option2.shown = card->shown>1?card->shown-1:card->shown;
	ret.option2.failed = card->failed;

	ret.option3.time = 1440*card->shown*2+easeFactor;
	sprintf(ret.option3.str,"good %dd",ret.option3.time/1440);
	sprintf(ret.option3.status,STATUS_KNOWN_NORMAL);
	ret.option3.shown = card->shown+1;
	ret.option3.failed = card->failed;

	if (card->shown <= 5){
		ret.option4.time = 1440*easeFactor*card->shown*2;
		sprintf(ret.option4.str,"easy %dd",ret.option4.time/1440);
		sprintf(ret.option4.status,STATUS_KNOWN_EASY);
		ret.option4.shown = card->shown+1;
		ret.option4.failed = card->failed;
	}else {
		ret.option4.time = 1440*MAX_REVISION;
		sprintf(ret.option4.str,"old %dd",ret.option4.time/1440);
		sprintf(ret.option4.status,STATUS_OLD);
		ret.option4.shown = 6;
		ret.option4.failed = card->failed;
	}

	return ret;
}

COptions old(Card* card){
	COptions ret;
	ret.option1.time = 10;
	sprintf(ret.option1.str,"again 10m");
	sprintf(ret.option1.status,STATUS_RELEARNING);
	ret.option1.shown = 3;
	ret.option1.failed = card->failed+1;

	ret.option3.time = 1440*MAX_REVISION;
	sprintf(ret.option3.str,"old %dd",ret.option3.time/1440);
	sprintf(ret.option3.status,STATUS_OLD);
	ret.option3.shown = 6;
	ret.option3.failed = card->failed;

	return ret;

}

COptions relearning(Card* card){
	COptions ret;
	ret.option1.time = 1;
	sprintf(ret.option1.str,"again 1m");
	sprintf(ret.option1.status,STATUS_LEARNING);
	ret.option1.shown = 0;
	ret.option1.failed = card->failed;

	ret.option2.time = 10;
	sprintf(ret.option2.str,"hard 10m");
	sprintf(ret.option2.status,STATUS_RELEARNING);
	ret.option2.shown = card->shown;
	ret.option2.failed = card->failed;

	ret.option3.time = 1440;
	sprintf(ret.option3.str,"good 1d");
	sprintf(ret.option3.status,STATUS_KNOWN_HARD);
	ret.option3.shown = card->shown;
	ret.option3.failed = card->failed;

	return ret;
}
COptions makeOptions(Card* card){
	if(isStatus(STATUS_LEARNING)){
		return learning(card);

	}else if(isStatus(STATUS_KNOWN_NORMAL)){
		return known(card, 2);

	}else if(isStatus(STATUS_KNOWN_EASY)){
		return known(card, 3);

	}else if(isStatus(STATUS_KNOWN_HARD)){
		return known(card, 1);

	}else if(isStatus(STATUS_OLD)){
		return old(card);

	}else if(isStatus(STATUS_RELEARNING)){
		return relearning(card);

	}

	return COptions();




}
