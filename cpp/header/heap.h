#pragma once
#include "lut.h"


class Heap{
public:
	static LUT lut;
	static void resetLUT();

	Heap();
	CardNodeRP* data;
	int n;
	int maxSize;
	void push(CardNodeRP);
	CardNodeRP view();
	CardNodeRP pop();
	CardNodeRP pop(int position);
	bool isEmpty();
	void print();
	~Heap();

private :
	void doubleDataSize();
	void heapSwap(int i, int j);
	bool nodeCompare(CardNodeRP i, CardNodeRP j);
};
