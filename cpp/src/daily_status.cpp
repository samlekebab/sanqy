#include "daily_status.h"
#include "def.h"
#include <stdio.h>

using namespace std;

DailyStatus::DailyStatus(std::string f,int time):	
	file(f),
	dailyStatusStruct(fromFile(f)){
	if (time/1440 != dailyStatusStruct.time/1440){
		dailyStatusStruct.time = time;
		dailyStatusStruct.nbNewCards = 0;
	}
}
DailyStatusStruct DailyStatus::fromFile(std::string file){

	FILE* f = fopen(file.c_str(),"ab");
	fclose(f);
	f = fopen(file.c_str(),"rb");
	fseek(f, 0L, SEEK_END);
	size_t s = ftell(f);
	fseek(f, 0L, SEEK_SET);
	//TODO openfile, check size, dump it in dailyStatusStruct
	DailyStatusStruct ret;
	if (s<sizeof(DailyStatusStruct))
		return ret;
		
	fread(&ret,sizeof(DailyStatusStruct),1,f);
	return ret;
}
DailyStatus::~DailyStatus(){
	FILE* f = fopen(file.c_str(),"wb");
	fwrite(&dailyStatusStruct,sizeof(DailyStatusStruct),1,f);

}
