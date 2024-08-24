#include <stdio.h>
#include "SQLiteCpp.h"
#include <iostream>
#include "sanqy.h"
#include "deck.h"
#include "status.h"
#include "cstdlib"
#include <sstream>
#include <ctime>
#include <ncurses.h>

//void test1(){
//	int time=0;
//	Deck* handler = (Deck*)openDatabase("test",time);
//	handler->todayHeap.print();
//	std::string face,back;
//	face="test";
//	back="tteesstt";
//	insertCard(handler,face,back);
//	std::string res = dumpDatabase(handler);
//	std::cout<<res<<std::endl;
//	int i;
//	std::cin >> i;
//	deleteCard(handler,i);
//	res = dumpDatabase(handler);
//	std::cout<<res<<std::endl;
//	handler->todayHeap.print();
//	closeDatabase(handler);
//
//}
//void fillDb(){
//	int time=0;
//	std::srand(std::time(0));
//	Deck* handler = (Deck*)openDatabase("test",time);
//	printf("filling database\n");
//	for (int i=0; i<1000;i++){
//		std::ostringstream face,back;
//		face << "front " << std::rand();
//		back << "back " << std::rand();
//		
//		insertCard(handler,face.str(),back.str());
//	}
//	closeDatabase(handler);
//
//}
//void test2(){
//
//	int time=5000;
//	Deck* handler = (Deck*)openDatabase("test",time);
//	if (isRevisionAvailable(handler,time)){
//		Options options = getOptions(handler);
//		revisionCallBack(handler,options,3,time);
//
//	}
//	closeDatabase(handler);
//}
void startRevision(void* handler, int time){
	UNUSED(handler);
	initscr(); 
	while(isRevisionAvailable(handler,time)){
		char front[MAX_WORD];
		char back[MAX_WORD];
		clear();
		getRevisionFront(handler,front);
		mvprintw(5,40,"%s",front);
		refresh();
		mvprintw(8,40,"ENTER - view solution");
		refresh();
		int cc= getch();
		if (cc=='q'){
			endwin();
			return;

		}
		Options options = getOptions(handler);
		clear();
		mvprintw(5,40,"%s",front);
		getRevisionBack(handler,back);
		mvprintw(6,40,"%s",back);
		mvprintw(8,40,"h-%s,j-%s,k-%s,l-%s",
				options.option1.str,
				options.option2.str,
				options.option3.str,
				options.option4.str);
		refresh();

		int no = 0;
		while(!no){
			int c = getch(); /* Wait for user input */
			if (c == 'q'){
				endwin();
				return;
			}
			else if (c == 'h' and options.option1.time>-1){
				no=1;
			}
			else if (c == 'j' and options.option2.time>-1){
				no=2;
			}
			else if (c == 'k' and options.option3.time>-1){
				no=3;
			}
			else if (c == 'l' and options.option4.time>-1){
				no=4;
			}
		}
		revisionCallBack(handler,no,time);
	}
	endwin();
	printf("revisions finished\n");
}
void test3(){
	Deck* handler = (Deck*)openDatabase("ju",10000);
	closeDatabase(handler);

}
int main(int argc, char* argv[]){
	int time = 1440*291+573;//TODO real time

	if(argc==1){
		printf("welcome on sanqy\n\
		add <table> <front> <back> to add a card \n\
		ls <table> to show all cards\n\
		rm <table> <uid> to remove card\n\
		update <table> <uid> <word> \
		modify a card TODO\n\
		reset <table> reset the status of all card\n\
		rev <table> to start a revision \n");
		return 0;

	}
	if(argc<3) {
		printf("missing arguments, did you specifyed the table?\n");
		return 0;
	}
	if(strcmp(argv[1],"add")==0){
		if (argc<5){
			printf("missing argument for add\n");
			return 0;
		}
		Deck* handler = (Deck*)openDatabase(argv[2],time);
		std::string face,back;
		face=argv[3];
		back=argv[4];
		insertCard(handler,face.c_str(),back.c_str());
		closeDatabase(handler);
		return 0;
	}
	if(strcmp(argv[1],"ls")==0){
		Deck* handler = (Deck*)openDatabase(argv[2],time);
		std::string res = dumpDatabase(handler);
		std::cout<<res<<std::endl;
		closeDatabase(handler);
		return 0;
	}
	if(strcmp(argv[1],"rm")==0){
		if (argc<4){
			printf("missing argument for rm\n");
			return 0;
		}
		Deck* handler = (Deck*)openDatabase(argv[2],time);
		int i = std::stoi(argv[3]);
		deleteCard(handler,i);
		closeDatabase(handler);
		return 0;
	}
	if(strcmp(argv[1],"update")==0){
		if (argc<4){
			printf("missing argument for rm\n");
			return 0;
		}
		Deck* handler = (Deck*)openDatabase(argv[2],time);
		int i = std::stoi(argv[3]);
		modifyCard(handler,argv[4],i);
		closeDatabase(handler);
		return 0;
	}
	if(strcmp(argv[1],"rev")==0){
		Deck* handler = (Deck*)openDatabase(argv[2],time);
		startRevision(handler,time);
		closeDatabase(handler);
		return 0;
	}
	if(strcmp(argv[1],"reset")==0){
		Deck* handler = (Deck*)openDatabase(argv[2],time);
		resetAllCards(handler);
		closeDatabase(handler);
	}


		
	return 0;
}
