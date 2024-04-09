#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIteratedList::SortedIteratedList(Relation r) {
	//TODO - Implementation
	this->rel = r;
	this->count = 0;
	this->head = new SLLnode;
	this->head->info = NULL_TCOMP;
	this->head->next = nullptr;
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

	if(!poz.valid())
		throw exception();
	TComp old = poz.getCurrent();
	if (poz.current->next == nullptr)
		poz.current->info == NULL_TCOMP;
	else {
		poz.current->info = poz.current->next->info;
		SLLnode* temp = poz.current->next;
		poz.current->next = poz.current->next->next;
		free(temp);
	}
	
	this->count--;
	return old;
}

ListIterator SortedIteratedList::search(TComp e) const{
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
	SLLnode* current = this->head;

	// if we need to insert on first position
	if (!this->rel(this->head->info, e)) {
		SLLnode* newNode = new SLLnode;
		newNode->info = this->head->info;
		newNode->next = this->head->next;
		this->head->info = e;
		this->head->next = newNode;
		this->count++;
		return;
	}
	//check if the element exists already
	while (current->next != nullptr && this->rel(current->next->info, e)) {
		current = current->next;
	}

	if(this->head->info == NULL_TCOMP) {
		this->head->info = e;
		this->head->next = nullptr;
		this->count++;
	}
	else {
		SLLnode* newNode = new SLLnode;
		newNode->info = e;
		newNode->next = current->next;
		current->next = newNode;
		this->count++;
	}

}

SortedIteratedList::~SortedIteratedList() {
	//TODO - Implementation
}
