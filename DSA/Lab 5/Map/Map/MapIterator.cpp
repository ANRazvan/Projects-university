#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;
#include <iostream>


MapIterator::MapIterator(const Map& d) : map(d)
{
	//TODO - Implementation
	this->current = this->map.head;
}


void MapIterator::first() {
	//TODO - Implementation
	this->current = this->map.head;
}


void MapIterator::next() {
	//TODO - Implementation
	if(this->current == -1)
		throw exception();
	this->current = this->map.next[this->current];
}

void MapIterator::previous() {
	/*
	Complexities:
	BC: Theta(1) - when the element is the first one
	TC: O(n)
	WC: Theta(n) - when the curr elem is the last
	*/

	if (!valid())
		throw exception();

	int currpoz = this->map.head;
	int prev = -1;
	while (currpoz != this->current)
	{
		prev = currpoz;
		currpoz = this->map.next[currpoz];
	}
	this->current = prev;

}


TElem MapIterator::getCurrent(){
	//TODO - Implementation
	if (this->current == -1)
		throw exception();
	return this->map.elements[this->current];
}


bool MapIterator::valid() const {
	//TODO - Implementation
	if (this->current == -1)
		return false;
	return true;
}



