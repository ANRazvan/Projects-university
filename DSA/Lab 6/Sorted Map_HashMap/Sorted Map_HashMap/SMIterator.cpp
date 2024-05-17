#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>
using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
	//TODO - Implementation
	this->currentPos = 0;
	this->elements = new TElem[m.nrElems];
	for (int i = 0; i < m.nrElems; i++) {
		this->elements[i] = NULL_TPAIR;
	}
	Relation rel = this->map.rel;
	for(int i = 0; i < this->map.m; i++)
		if(this->map.T[i] != NULL_TPAIR)
		{
			if (this->elements[0] == NULL_TPAIR) {
				this->elements[0] = this->map.T[i];
				continue;
			}
			int pos = 0;
			while (this->elements[pos] != NULL_TPAIR && rel(this->elements[pos].first,this->map.T[i].first)) {
				pos++;
				if(pos == this->map.nrElems)
					break;
			}
			for (int j = this->map.nrElems - 1; j > pos; j--) {
				this->elements[j] = this->elements[j - 1];
			}
			this->elements[pos] = this->map.T[i];
		}

}

void SMIterator::first(){
	//TODO - Implementation
	this->currentPos = 0;
}

void SMIterator::next(){
	//TODO - Implementation
	if(!this->valid())
		throw exception();
	this->currentPos++;
}

bool SMIterator::valid() const{
	//TODO - Implementation
	if(this->currentPos < this->map.nrElems)
		return true;
	return false;
}

TElem SMIterator::getCurrent() const{
	//TODO - Implementation
	if(!this->valid())
		throw exception();
	return this->elements[this->currentPos];
}


