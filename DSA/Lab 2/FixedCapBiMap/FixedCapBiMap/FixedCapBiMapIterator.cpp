#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>
using namespace std;


FixedCapBiMapIterator::FixedCapBiMapIterator(const FixedCapBiMap& d ) : map(d)
{
	//TODO - Implementation
	this->currentPosition = 0;

}


void FixedCapBiMapIterator::first() {
	//TODO - Implementation
	this->currentPosition = 0;
}


void FixedCapBiMapIterator::next() {
	//TODO - Implementation
	if (this->currentPosition == this->map.mapSize){
		throw exception();
	}
	this->currentPosition++;

}


TElem FixedCapBiMapIterator::getCurrent(){
	//TODO - Implementation
	if (this->currentPosition == this->map.mapSize) {
		throw exception();
	}
	return this->map.elements[this->currentPosition];
}


bool FixedCapBiMapIterator::valid() const {
	//TODO - Implementation

	return this->currentPosition < this->map.mapSize;

}



