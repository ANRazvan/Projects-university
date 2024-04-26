#include "Map.h"
#include <iostream>
using namespace std;
#include "MapIterator.h"

Map::Map() {
	//TODO - Implementation
	this->capacity = 10;
	this->nrElems = 0;
	this->head = -1;
	this->elements = new TElem[this->capacity];
	this->next = new int[this->capacity];

	for(int i = 0; i< this->capacity-1;i++)
		this->next[i] = i+1;

	this->next[capacity - 1] = -1;
	this->firstEmpty = 0;
}

Map::~Map() {
	//TODO - Implementation
	delete[] this->elements;
	delete[] this->next;
}


TValue Map::add(TKey c, TValue v) {
	//TODO - Implementation
	/*Complexities:
	BC: Theta(1) - when the element is the first one
	TC: O(n)
	WC: Theta(n) - when the element is not in the map
	*/

	if (this->head == -1) {

		this->head = 0;
		this->elements[0].first = c;
		this->elements[0].second = v;
		this->next[0] = -1;
		this->nrElems++;
		this->firstEmpty = 1;

		return NULL_TVALUE;
	}
	else {
		int current = this->head;
		int prev = -1;
		while (current != -1) {
			if (this->elements[current].first == c) {
				TValue old = this->elements[current].second;
				this->elements[current].second = v;
				return old;
			}
			prev = current;
			current = this->next[current];
		}
		// prev is the poz of the previous last element
		if (this->firstEmpty == -1) {
			TElem* newElems = new TElem[this->capacity * 2];
			int* newNext = new int[this->capacity * 2];
			for (int i = 0; i < this->capacity; i++) {
				newElems[i] = this->elements[i];
				newNext[i] = this->next[i];
			}
			for (int i = this->capacity; i < this->capacity * 2 - 1; i++) {
				newNext[i] = i + 1;
			}
			this->firstEmpty = this->capacity;
			this->capacity *= 2;
			newNext[this->capacity - 1] = -1;
			delete[] this->elements;
			delete[] this->next;
			this->elements = newElems;
			this->next = newNext;
		}	

		// adding
		int newpos = this->firstEmpty;
		this->firstEmpty = this->next[this->firstEmpty];
		if(this->firstEmpty == 0)
			this->firstEmpty = this->next[this->firstEmpty];

		this->elements[newpos].first = c;
		this->elements[newpos].second = v;
		this->next[newpos] = -1;
		this->next[prev] = newpos;
		this->nrElems++;
		return NULL_TVALUE;
		

	}
}

/*
TValue Map::add(TKey c, TValue v){
	//TODO - Implementation

	int current = this->head;
	int prev = -1;

	while (current != -1) {
		cout << this->elements[current].first << "  " << c << endl;
		if (this->elements[current].first == c) {
			TValue old = this->elements[current].second;
			this->elements[current].second = v;
			cout << old << endl;
			return old;
		}
		prev = current;
		current = this->next[current];
	}

	//resize if necessary
	if (this->firstEmpty == -1) {
		TElem* newElems = new TElem[this->capacity * 2];
		int* newNext = new int[this->capacity * 2];
		for (int i = 0; i < this->capacity; i++) {
			newElems[i] = this->elements[i];
			newNext[i] = this->next[i];
		}
		for (int i = this->capacity; i < this->capacity * 2 - 1; i++) {
			newNext[i] = i + 1;
			this->firstEmpty = this->capacity;
		}
		newNext[this->capacity * 2 - 1] = -1;
		delete[] this->elements;
		delete[] this->next;
		this->elements = newElems;
		this->next = newNext;
	}
	
	//adding 
	int newpos = this->firstEmpty;

	if (this->head == -1) {
		this->head = newpos;
		this->next[this->head] = -1;
	}
	else {
		this->next[prev] = newpos;
		this->next[newpos] = -1;
	}

	this->elements[newpos].first = c;
	this->elements[newpos].second = v;
	this->firstEmpty = this->next[this->firstEmpty];
	this->nrElems++;

	return NULL_TVALUE;
}*/

TValue Map::search(TKey c) const{
	//TODO - Implementation
	/*
	Complexities
	BC: Theta(1) - when the element is the first one
	TC: O(n)
	WC: Theta(n) - when the element is not in the map
	*/
	
	TValue oldValue = NULL_TVALUE;
	int current = head;
	
	while (current != -1) {
		if (elements[current].first == c) {
			oldValue = elements[current].second;
			return oldValue;
		}
		current = next[current];
	}

	return oldValue;

}
/*
TValue Map::remove(TKey c){
	//TODO - Implementation
	TValue oldValue = NULL_TVALUE;
	int current = head;
	int prev = -1;
	
	while (current != -1 && this->elements[current].first != c) {
		prev = current;
		current = this->next[current];
	}

	if (current != -1) {
		oldValue = this->elements[current].second;
		if (current == this->head)
			this->head = this->next[this->head];
		else
			this->next[prev] = this->next[current];
		this->next[current] = this->firstEmpty;
		this->firstEmpty = current;
		this->nrElems--;
		return oldValue;
	}

	return oldValue;
	
}
*/


TValue Map::remove(TKey c){
	//TODO - Implementation
	/*
	Complexities:
	BC: Theta(1) - when the element is the first one
	WC: Theta(n) - when the element is the last/ doesnt exist
	TC: O(n)
	*/
	if(this->head == -1)
		return NULL_TVALUE;

	if (this->elements[this->head].first == c) {
		TValue oldValue = this->elements[this->head].second;
		int oldhead = this->head;
		this->head = this->next[this->head];
		this->next[oldhead] = this->firstEmpty;
		this->firstEmpty = oldhead;
		this->nrElems--;
		return oldValue;
	}
	
	int current = this->head;
	int prev = -1;
	while (current != -1 && this->elements[current].first != c) {
		prev = current;
		current = this->next[current];
	}

	if(current == -1)
		return NULL_TVALUE;

	TValue old= this->elements[current].second;
	this->next[prev] = this->next[current];
	this->next[current] = this->firstEmpty;
	this->firstEmpty = current;
	this->nrElems--;
	return old;

}


int Map::size() const {
	//TODO - Implementation
	return this->nrElems;
}

bool Map::isEmpty() const{
	//TODO - Implementation
	return this->nrElems == 0;
}

MapIterator Map::iterator() const {
	return MapIterator(*this);
}



