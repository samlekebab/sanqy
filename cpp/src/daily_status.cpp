#include "daily_status.h"
#include "def.h"
#include <stdio.h>

using namespace std;

DailyStatus::DailyStatus(std::string f,int time):	
	file(f),
	dailyStatusStruct(fromFile(f)){
	if (time/1440 != dailyStatusStruct.time/1440){
		dailyStatusStruct.nbNewCards = 0;
	}
	dailyStatusStruct.time = time;
	saveStatus();
}
DailyStatusStruct DailyStatus::fromFile(std::string file){

	FILE* f = fopen(file.c_str(),"ab");
	fclose(f);
	f = fopen(file.c_str(),"rb");
	fseek(f, 0L, SEEK_END);
	size_t s = ftell(f);
	fseek(f, 0L, SEEK_SET);
	DailyStatusStruct ret{0,0};
	if (s<sizeof(DailyStatusStruct))
		return ret;
		
	fread(&ret,sizeof(DailyStatusStruct),1,f);
	fclose(f);
	return ret;
}
DailyStatus::~DailyStatus(){
	saveStatus();
}
void DailyStatus::saveStatus(){
	FILE* f = fopen(file.c_str(),"wb");
	fwrite(&dailyStatusStruct,sizeof(DailyStatusStruct),1,f);
	fclose(f);
}
