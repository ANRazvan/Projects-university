#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>
using namespace std;

SortedMap::SortedMap(Relation r) {
	//TODO - Implementation
	this->mapSize = 0;
	this->rel = r;
	this->capacity = 10;
	this->elements = new TElem[capacity];
}

TValue SortedMap::add(TKey k, TValue v) {
	//TODO - Implementation
	int index = 0;
	int position = -1;
	TValue old = NULL_TVALUE;
	while (index < this->mapSize) {

	}
	return old;
}


TValue SortedMap::search(TKey k) const {
	//TODO - Implementation
	int index = 0;
	while (index < this->mapSize) {
		if (this->elements[index].first == k) {
			return this->elements[index].second;
		}
		index++;
	}
	return NULL_TVALUE;
}

TValue SortedMap::remove(TKey k) {
	//TODO - Implementation
	int index = 0;
	TValue value = NULL_TVALUE;
	bool removed = false;
	while (index < this->mapSize) {
		if (this->elements[index].first == k) {
			removed = true;
			value = this->elements[index].second;
		}
		if (index < this->mapSize - 1 && removed == true)
			this->elements[index] = this->elements[index + 1];
		index++;
	}

	if (removed == true)
		this->mapSize--;
	return value;
}

int SortedMap::size() const {
	//TODO - Implementation
	return this->mapSize;
}

bool SortedMap::isEmpty() const {
	//TODO - Implementation
	return this->mapSize == 0;
}

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

int SortedMap::updateValues(SortedMap& sm) {
	int number = 0;


}

SortedMap::~SortedMap() {
	//TODO - Implementation
	delete[] this->elements;
}
