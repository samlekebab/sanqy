#pragma once
//this object save the number of new cards seen this day
#include <string>

struct DailyStatusStruct{
	int time = 0;
	int nbNewCards = 0;
	int nbRevisionCards = 0;
};
class DailyStatus{
public:
	std::string file;
	DailyStatusStruct dailyStatusStruct;
	DailyStatusStruct fromFile(std::string f);
	DailyStatus(std::string file, int time);
	void saveStatus();
	~DailyStatus();
};
