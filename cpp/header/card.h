#pragma once	
#include <string>

struct Card {

	int uid;
	std::string word;
	int mateUid;
	int face;
	std::string status;
	int revisionTime;
	int shown;
	int failed;
};

struct TwoCards{
	Card front;
	Card back;
};

