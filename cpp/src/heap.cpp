#include "heap.h"
#include "def.h"
#include <cstring>
#include <new>

Heap::Heap(){
	n=0;
	maxSize=1;
	data = new CardNodeRP[maxSize];
}
void Heap::doubleDataSize(){
	CardNodeRP* newData = new CardNodeRP[2*maxSize];
	memcpy(newData,data,n*sizeof(CardNodeRP));
	delete[] data;
	data = newData;
	maxSize *= 2; 
}
void Heap::heapSwap(int i,int j){
	CardNodeRP tmp = data[i];
	data[i] = data[j];
	data[j] = tmp;
	data[i].getCardNode()->heapPosition = i;
	data[j].getCardNode()->heapPosition = j;
}
bool Heap::nodeCompare(CardNodeRP a, CardNodeRP b){
	int w1 = a.getCardNode()->revisionTime;
	int w2 = b.getCardNode()->revisionTime;
	return w2 < w1;

}
bool Heap::isEmpty() {
	return n <= 0;
}
CardNodeRP Heap::view(){
	return data[0];
}
void Heap::push(CardNodeRP cardNode){
	cardNode.getCardNode()->heap = this;
	cardNode.getCardNode()->heapPosition = n;
	if (n>=maxSize){
		doubleDataSize();
	}
	//TODO
	data[n] = cardNode;
	cardNode.getCardNode()->heapPosition = n;

	n += 1;
	int i = n - 1;
	while (i > 0 && 
	nodeCompare(data[(i - 1) / 2], data[i])) {
		int tmp = (i - 1) / 2;
		heapSwap(i, tmp);
		i = tmp;
	}
}
CardNodeRP Heap::pop(){
	return pop(0);
}
CardNodeRP Heap::pop(int position) {
	CardNodeRP res = data[position];
	n -= 1;
	data[position] = data[n];
	bool end = false;
	int i = position;
	int tmp = 2 * i + 1;
	while (!end && tmp < n) {
		int j = i;
		end = true;
		if (nodeCompare(data[i], data[tmp])) {
			heapSwap(i, tmp);
			end = false;
			j = tmp;
		}
		if (tmp + 1 < n && nodeCompare(data[i], data[tmp + 1])) {
			tmp++;
			heapSwap(i, tmp);
			end = false;
			j = (i == j ?tmp:j);
		}
		tmp = 2 * j + 1;
		i = j;
	}
	return res;
}
Heap::~Heap(){
	delete[] data;
}
LUT Heap::lut = LUT();
void Heap::resetLUT(){
	Heap::lut.~LUT();
	new(&(Heap::lut)) LUT();
}
#include <stdio.h>
void Heap::print(){
	printf("n : %d, maxSize : %d\n",n,maxSize);
	for (int i=0; i<n;i++){
		printf("%d\n",data[i].getCardNode()->uid);
	}
}
