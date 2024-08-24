#include "random_pool.h"
#include <cstdlib>
#include <ctime>
void RandomPool::chooseNext(){
	if (heap.n > 0){
		idRandom = 1 + std::rand() / ((RAND_MAX + 1u) / heap.n);
	}else{
		idRandom = 0;
	}
}
CardNodeRP RandomPool::viewRandom(){
	if (idRandom>=heap.n)
		return heap.view();
	return heap.data[idRandom];
}
CardNodeRP RandomPool::popRandom(){
	CardNodeRP ret;
	if (idRandom>=heap.n){
		ret = heap.pop();
	}else{
		ret = heap.pop(idRandom);
	}
	chooseNext();
	return ret;
}
RandomPool::RandomPool(){
	std::srand(std::time(nullptr));

}
