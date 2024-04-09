#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
	//TODO - Implementation
	this->currentPosition = 0;
}

void SMIterator::first(){
	//TODO - Implementation
	this->currentPosition = 0;
}

void SMIterator::next(){
	//TODO - Implementation
	if (this->currentPosition == this->map.mapSize) {
		throw exception();
	}
	this->currentPosition++;

}

bool SMIterator::valid() const{
	//TODO - Implementation
	return this->currentPosition < this->map.mapSize;
}

TElem SMIterator::getCurrent() const{
	//TODO - Implementation
	if (this->currentPosition == this->map.mapSize) {
		throw exception();
	}
	return this->map.elements[this->currentPosition];
}


