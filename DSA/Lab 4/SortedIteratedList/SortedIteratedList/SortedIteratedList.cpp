#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIteratedList::SortedIteratedList(Relation r) {
	// Constructor:
	// BC: Theta(1)
	// WC: Theta(1)
	// AC: Theta(1)
	this->rel = r;
	this->count = 0;
	this->head = nullptr;
}

int SortedIteratedList::size() const {
	// Size:
	// BC: Theta(1)
	// WC: Theta(1)
	// AC: Theta(1)
	return this->count;
}

bool SortedIteratedList::isEmpty() const {
	// isEmpty:
	// BC: Theta(1)
	// WC: Theta(1)
	// AC: Theta(1)
	return this->count == 0;
}

ListIterator SortedIteratedList::first() const {
	// First:
	// BC: Theta(1)
	// WC: Theta(1)
	// AC: Theta(1)
	ListIterator poz(*this);
	return poz;
}

TComp SortedIteratedList::getElement(ListIterator poz) const {
	// getElement:
	// BC: Theta(1)
	// WC: Theta(1)
	// AC: Theta(1)
	if (!poz.valid())
		throw exception();
	return poz.getCurrent();
}

TComp SortedIteratedList::remove(ListIterator& poz) {
	// Remove:
	// BC: Theta(1)
	// WC: Theta(n)
	// AC: O(n)
	if (!poz.valid())
		throw exception();
	TComp old = poz.getCurrent();

	if (this->head == poz.current) {
		this->head = this->head->next;
		delete poz.current;
		poz.current = this->head;
	}
	else {
		SLLnode* current = this->head;
		while (current->next != poz.current) {
			current = current->next;
		}
		current->next = poz.current->next;
		delete poz.current;
		poz.current = current->next;
	}
	this->count--;
	return old;
}

void SortedIteratedList::removeBetween(ListIterator& start, ListIterator& end) {
	// RemoveBetween:
	// BC: Theta(1)
	// WC: Theta(n)
	// AC: O(n)

	if (!start.valid() || !end.valid())
		throw exception();
	
	if (start.current == end.current) {
		if (this->head == start.current) {
			delete this->head;
			this->head = start.current->next;
		}
		SLLnode* next = start.current->next;
		delete start.current;
		start.current = next;
		this->count--;
		return;
	}


	if (this->head == start.current) {
		this->head = end.current->next;

		delete end.current;
		this->count--;

		while (start.current != end.current) {
			SLLnode* next = start.current->next;
			delete start.current;
			start.current = next;
			this->count--;
		}
	}
	else {
		SLLnode* current = this->head;
		while (current->next != start.current) {
			current = current->next;
		}
		current->next = end.current->next;

		while (start.current != end.current) {
			SLLnode* next = start.current->next;
			delete start.current;
			start.current = next;
			this->count--;
		}
		delete end.current;
		this->count--;
	}
	
}	

ListIterator SortedIteratedList::search(TComp e) const {
	// Search:
	// BC: Theta(1)
	// WC: Theta(n)
	// AC: O(n)
	ListIterator poz(*this);
	while (poz.valid()) {
		if (poz.getCurrent() == e) {
			return poz;
		}
		poz.next();
	}
	return poz;
}

void SortedIteratedList::add(TComp e) {
	// Add:
	// BC: Theta(1)
	// WC: Theta(n)
	// AC: O(n)
	// We create a new node with the given element
	SLLnode* newNode = new SLLnode;
	newNode->info = e;
	newNode->next = nullptr;

	// We check if the list is empty
	if (this->head == nullptr) {
		this->head = newNode;
		this->count++;
		return;
	}

	// We check if the element should be inserted at the beginning of the list
	if (!this->rel(this->head->info, e)) {
		newNode->next = this->head;
		this->head = newNode;
		this->count++;
		return;
	}

	// We find the position where the element should be inserted
	SLLnode* current = this->head;
	while (current->next != nullptr && this->rel(current->next->info, e)) {
		current = current->next;
	}

	newNode->next = current->next;
	current->next = newNode;
	this->count++;
}

SortedIteratedList::~SortedIteratedList() {
	// Destructor:
	// BC: Theta(n)
	// WC: Theta(n)
	// AC: Theta(n)
	SLLnode* current = this->head;
	while (current != nullptr) {
		SLLnode* next = current->next;
		delete current;
		current = next;
	}
}
