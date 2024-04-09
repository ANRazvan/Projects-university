#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"

FixedCapBiMap::FixedCapBiMap(int capacity) {
	//TODO - Implementation
	if (capacity <= 0) {
		throw exception();
	}
	this->capacity = capacity;
	this->mapSize = 0;
	this->elements = new TElem[this->capacity];
}

FixedCapBiMap::~FixedCapBiMap() {
	//TODO - Implementation
	delete[] this->elements;
}

bool FixedCapBiMap::add(TKey c, TValue v){
	//TODO - Implementation
	if (this->mapSize == capacity) {
		throw exception();
	}
	int count = 0;
	int index = 0;
	while (count < 2 && index < this->mapSize) {
		if (this->elements[index].first == c) {
			count++;
		}
		index++;
	}
	if (count == 2) {
		return false;
	}
	this->elements[mapSize].first = c;
	this->elements[mapSize].second = v;
	this->mapSize++;

	return true;
}

ValuePair FixedCapBiMap::search(TKey c) const{
	//TODO - Implementation
	ValuePair result;
	result.first = NULL_TVALUE;
	result.second = NULL_TVALUE;

	int nrfound = 0;
	int index = 0;
	while (nrfound < 2 && index < this->mapSize) {
		if (this->elements[index].first == c) {
			if (nrfound == 0) {
				result.first = this->elements[index].second;
				nrfound++;
			}
			else {
				result.second = this->elements[index].second;
				nrfound++;
			}
		}
		index++;
	}
	return result;

}

bool FixedCapBiMap::remove(TKey c, TValue v){
	//TODO - Implementation
	int index = 0;
	while (index < this->mapSize) {
		if (this->elements[index].first == c && this->elements[index].second == v) {
			this->elements[index] = this->elements[this->mapSize - 1];
			this->mapSize--;
			return true;
		}
		index++;
	}
	return false;
}

ValuePair FixedCapBiMap::removeKey(TKey c) {
	ValuePair result;
	result.first = NULL_TVALUE;
	result.second = NULL_TVALUE;

	int nrfound = 0;
	int index = 0;

	while (nrfound < 2 && index < this->mapSize) {
		if (this->elements[index].first == c) {
			if (nrfound == 0) {
				result.first = this->elements[index].second;
				nrfound++;
				this->elements[index] = this->elements[this->mapSize-1];
				mapSize--;
			}
			else {
				result.second = this->elements[index].second;
				nrfound++;
				this->elements[index] = this->elements[this->mapSize-1];
				mapSize--;
			}
		}
		else {
			index++;
		}
	}
	return result;
}


int FixedCapBiMap::size() const {
	//TODO - Implementation
	return this->mapSize;
}

bool FixedCapBiMap::isEmpty() const{
	//TODO - Implementation
	return this->mapSize == 0;
}

bool FixedCapBiMap::isFull() const {
	//TODO - Implementation
	return this->mapSize == capacity;
}

FixedCapBiMapIterator FixedCapBiMap::iterator() const {
	return FixedCapBiMapIterator(*this);
}



