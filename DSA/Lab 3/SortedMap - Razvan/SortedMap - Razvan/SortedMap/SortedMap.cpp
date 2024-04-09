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
	/*
	BC = Theta(1)
	WC = Theta(n+n) = Theta(n)
	AC = O(n)
	TC = O(n)

	*/
	//TODO - Implementation
	int index = 0;
	TValue old = NULL_TVALUE;
	while (index < this->mapSize && rel(this->elements[index].first, k)) {
		if (this->elements[index].first == k) {
			old = this->elements[index].second;
			this->elements[index].second = v;
			return old;
		}
		index++;
	}

	if (this->mapSize == this->capacity) {
		this->capacity *= 2;
		TElem* new_arr = new TElem[this->capacity];
		for (int i = 0; i < mapSize; i++)
			new_arr[i] = this->elements[i];
		delete[] this->elements;
		this->elements = new_arr;
	}

	for (int i = this->mapSize - 1; i >= index; i--)
		this->elements[i + 1] = this->elements[i];

	this->elements[index].first = k;
	this->elements[index].second = v;
	this->mapSize++;
	return old;
}


TValue SortedMap::search(TKey k) const {
	/*
		BC = Theta(1)
		WC = Theta(n)
		AC = O(n)
		TC = O(n)
	*/
	//TODO - Implementation
	int index = 0;
	while (index < this->mapSize && rel(this->elements[index].first, k)) {
		if (this->elements[index].first == k) {
			return this->elements[index].second;
		}
		index++;
	}
	return NULL_TVALUE;
}

TValue SortedMap::remove(TKey k) {
	/*
		BC = Theta(n)
		WC = Theta(n)
		AC = Theta(n)
		TC = O(n)
	*/
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
	/*
	* m = sm.mapSize
	* n = original map size
	*	BC = Theta(1)
		AC = m * n * n = O(m*n^2)
		WC = m * n * n = Theta(m*n^2)
		TC = O(m*n^2)
	*/
	int number = 0;
	int index_sm = 0;
	//while (index_sm < sm.mapSize) {
	//	int index = 0;
	//	while (index < this->mapSize) {
	//		if (this->elements[index].first == sm.elements[index_sm].first) {
	//			this->remove(this->elements[index].first);
	//			this->add(sm.elements[index_sm].first, sm.elements[index_sm].second);
	//			number++;
	//			break;
	//		}
	//		index++;
	//	}
	//	index_sm++;
	//}
	while (index_sm < sm.mapSize) {
		int index = 0;
		while (index < this->mapSize) {
			if (this->elements[index].first == sm.elements[index_sm].first) {
				if (rel(sm.elements[index_sm].first, this->elements[mapSize - 1].first)) {
					int index_curr = index;
					while (!rel(sm.elements[index_sm].first, this->elements[index_curr + 1].first)) {
						index_curr++;
					}
					for (int i = index; i < index_curr; i++)
						this->elements[i] = this->elements[i + 1];
					this->elements[index_curr] = sm.elements[index_sm];

				}
				else {
					int index_curr = index;
					while (!rel(sm.elements[index_sm].first, this->elements[index_curr + 1].first)) {
						index_curr--;
					}
					for (int i = index_curr; i < index; i++)
						this->elements[i+1] = this->elements[i];
					this->elements[index_curr] = sm.elements[index_sm];
				}
				number++;
				break;
			}
			index++;
		}
		index_sm++;
	}
	return number;
}


SortedMap::~SortedMap() {
	//TODO - Implementation
	delete[] this->elements;
}
