#include "sanqy.h"
#include "db.h"
#define UNUSED(X) (void)(X)


CardDataBase* cardDatabase=nullptr;

void openDatabase(const char* file){

	if (cardDatabase!=nullptr){
		closeDatabase();
	}
	cardDatabase = new CardDataBase(file);
}
void closeDatabase(){
	delete cardDatabase;
	cardDatabase = nullptr;
}
bool insertCard(const char * fwrd, const char bwrd){
	UNUSED(fwrd);
	UNUSED(bwrd);

	if (cardDatabase==nullptr){
		return 1;
	}
	//TODO
	return 0;
}
const char* dumpDatabase(){
	//TODO
	return "ras";
}
