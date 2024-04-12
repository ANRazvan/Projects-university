#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIteratedList::SortedIteratedList(Relation r) {
	//TODO - Implementation
	this->rel = r;
	this->count = 0;
	this->head = nullptr;
}

int SortedIteratedList::size() const {
	//TODO - Implementation
	return this->count;
}

bool SortedIteratedList::isEmpty() const {
	//TODO - Implementation
	return this->count == 0;
}

ListIterator SortedIteratedList::first() const {
	//TODO - Implementation
	ListIterator poz(*this);
	return poz;

}

TComp SortedIteratedList::getElement(ListIterator poz) const {
	//TODO - Implementation
	if (!poz.valid())
		throw exception();
	return poz.getCurrent();
}

TComp SortedIteratedList::remove(ListIterator& poz) {
	//TODO - Implementation
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

ListIterator SortedIteratedList::search(TComp e) const {
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
	//TODO - Implementation
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
	//TODO - Implementation
	SLLnode* current = head;

	while (current != nullptr) {
		SLLnode* next = current->next;
		delete current;
		current = next;
	}
}
