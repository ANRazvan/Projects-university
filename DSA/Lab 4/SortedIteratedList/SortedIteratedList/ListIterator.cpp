#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>
#include <iostream>
using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : list(list) {
	// Constructor:
	// BC: Theta(1)
	// WC: Theta(1)
	// AC: Theta(1)
	this->current = this->list.head;
}

void ListIterator::first() {
	// First:
	// BC: Theta(1)
	// WC: Theta(1)
	// AC: Theta(1)
	this->current = this->list.head;
}

void ListIterator::next() {
	// Next:
	// BC: Theta(1)
	// WC: Theta(1)
	// AC: Theta(1)
	if (this->current == nullptr)
		throw exception();
	this->current = this->current->next;
}

bool ListIterator::valid() const {
	// Valid:
	// BC: Theta(1)
	// WC: Theta(1)
	// AC: Theta(1)
	if (this->current == nullptr)
		return false;
	else
		return true;
}

TComp ListIterator::getCurrent() const {
	// GetCurrent:
	// BC: Theta(1)
	// WC: Theta(1)
	// AC: Theta(1)
	return this->current->info;
}
