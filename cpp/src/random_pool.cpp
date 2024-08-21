#include "random_pool.h"
#include <cstdlib>
#include <ctime>
void RandomPool::chooseNext(){
	idRandom = 1 + std::rand() / ((RAND_MAX + 1u) / heap.n);
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
