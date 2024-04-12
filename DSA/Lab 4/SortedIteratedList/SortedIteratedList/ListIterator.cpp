#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>
#include <iostream>
using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : list(list) {
	//TODO - Implementation
	this->current = this->list.head;
}

void ListIterator::first() {
	//TODO - Implementation
	this->current = this->list.head;
}

void ListIterator::next() {
	//TODO - Implementation
	if (this->current == nullptr || this->current->info == NULL_TCOMP)
		throw exception();
	this->current = this->current->next;
}

bool ListIterator::valid() const {
	//TODO - Implementation
	if (this->current == nullptr/* || this->current->info == NULL_TCOMP*/)
		return false;
	else
		return true;
}

TComp ListIterator::getCurrent() const {
	//TODO - Implementation
	return this->current->info;
}


