#pragma once
#include "lut.h"
#include "heap.h"

class RandomPool{
public:
	Heap heap;
	int idRandom=0;
	void chooseNext();
	CardNodeRP popRandom();
	CardNodeRP viewRandom();
	RandomPool();
};
