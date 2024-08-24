#pragma once
//this are the status of a card
//we chose the options of scheduling using
//the status and the "shown" member wich represent
//the box of the card

#define STATUS_LEARNING "LEARNING"
#define STATUS_KNOWN_EASY "KNOWN_EASY"
#define STATUS_KNOWN_NORMAL "KNOWN_NORMAL"
#define STATUS_KNOWN_HARD "KNOWN_HARD"
#define STATUS_OLD "OLD"
#define STATUS_RELEARNING "RELEARNING"

#define MAX_REVISION 60

#define OPTION_STR_MAX 100

#include <string>
#include "def.h"

extern "C"{
typedef struct Option{
	int time ;
	char str[OPTION_STR_MAX];
	char status[OPTION_STR_MAX];
	int shown;
	int failed;

} Option;
//typedef struct Option{
//	int time = -1;
//	char str[OPTION_STR_MAX]="";
//	char status[OPTION_STR_MAX]="";
//	int shown = 0;
//	int failed = 0;
//
//} Option;
typedef struct Options{
	Option option1;
	Option option2;
	Option option3;
	Option option4;
} Options;
}
struct COption:Option{
	COption(){
		time = -1;
		str[0] = '\0';
		status[0] = '\0';
		shown = 0;
		failed = 0; 
	}
};
struct COptions:Options{
	COptions(){
		option1 = COption();
		option2 = COption();
		option3 = COption();
		option4 = COption();
	}
};

struct Card;
COptions makeOptions(Card* card);
