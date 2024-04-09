#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b), current_index(0)
{
	//TODO - Implementation
}

TComp SortedBagIterator::getCurrent() {
    if (!valid()) {
        throw exception();
    }
    return bag.elements[current_index];
	//TODO - Implementation
	//return NULL_TCOMP;
}

bool SortedBagIterator::valid() {

    return this->current_index<this->bag.size_arr && this->current_index<this->bag.bagsize;
	//TODO - Implementation
	//return false;
}

void SortedBagIterator::next() {
    if (!valid()) {
        throw exception();

    }
    this -> current_index++;
        //TODO - Implementation
    }

    void SortedBagIterator::first() {
        this->current_index = 0;
        //TODO - Implementation
    }

