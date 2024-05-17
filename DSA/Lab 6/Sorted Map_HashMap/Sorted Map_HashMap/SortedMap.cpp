#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>
using namespace std;


SortedMap::SortedMap(Relation r) {
	//TODO - Implementation
	this->m = 16;
	this->T = new TElem[this->m];
	this->nrElems = 0;
	this->rel = r;
	for (int i = 0; i < this->m; i++) {
		this->T[i] = NULL_TPAIR;
	}
}

int SortedMap::hash1(TKey k) const
{
	int abs = k % this->m;
	if (abs < 0)
		abs = -abs;
	return abs;
}

int SortedMap::hash2(TKey k) const
{
	int abs = k % (this->m - 1);
	if (abs < 0)
		abs = -abs;
	if (abs % 2 == 0)
		return 1 + abs;
	return 2 + abs;
}

//BC: Theta(1) - when the element is the first one
//TC : O(n)
//WC : Theta(n) - when the element is not in the map
TValue SortedMap::add(TKey k, TValue v) {
	/*
		BC: Theta(1) - when the element is the first one
		TC : O(n)
		WC : Theta(n) - when the map is full
	*/
	int i = 0;
	int start = hash1(k) % this->m;
	int step = hash2(k) % this->m;
	int pos = start;

	//while (i < this->m && this->T[pos] != NULL_TPAIR) {
	//	cout << this->T[pos].first << " " << k << endl;
	//	if (this->T[pos].first == k) {
	//		TValue oldValue = this->T[pos].second;
	//		this->T[pos].second = v;
	//		return oldValue;
	//	}
	//	i++;
	//	pos = (pos + step) % ;
	//}

	//while (i < this->m) {
	//	if (this->T[i].first == k) {
	//		TValue oldValue = this->T[i].second;
	//		this->T[i].second = v;
	//		return oldValue;
	//	}
	//	i++;
	//}
	i = 0;

	while (i < this->m && this->T[pos] != NULL_TPAIR) {
		//if (this->T[pos].first == k) {
		//	TValue oldValue = this->T[pos].second;
		//	this->T[pos].second = v;
		//	cout << "exsiting 2 " << k << " " << v << " " << oldValue << endl;
		//	return oldValue;
		//}
		if (this->T[pos].first == k) {
			TValue oldValue = this->T[pos].second;
			this->T[pos].second = v;
			return oldValue;
		}
		i++;
		pos = (pos + step) % this->m;
	}

	if (i == this->m) {

		// Resize the table when it's full
		TElem* newT = new TElem[this->m * 2];
		for (int j = 0; j < this->m * 2; j++) {
			newT[j] = NULL_TPAIR;
		}
		int oldm = this->m;
		this->m *= 2;
		// Rehash all the elements into the new table
		for (int j = 0; j < oldm; j++) {
			if (this->T[j] != NULL_TPAIR && this->T[j] != DELETED_TPAIR) {
				int newI = 0;
				int newStart = hash1(this->T[j].first) % (oldm * 2);
				int newStep = hash2(this->T[j].first) % (oldm * 2);
				int newPos = newStart;
				while (newI < oldm * 2 && newT[newPos] != NULL_TPAIR) {
					newI++;
					newPos = (newPos + newStep) % (oldm * 2);
				}
				newT[newPos] = this->T[j];

			}
		}
		delete[] this->T;
		this->T = newT;
		// Now add the new element
		i = 0;
		pos = hash1(k) % this->m;
		step = hash2(k) % this->m;
		while (i < this->m && this->T[pos] != NULL_TPAIR) {
			i++;
			pos = (pos + step) % this->m;
		}

		if (i < this->m) {
			this->T[pos] = make_pair(k, v);
			this->nrElems++;
		}

		return NULL_TVALUE;
	}
	else {
		this->T[pos] = make_pair(k, v);
		this->nrElems++;
		return NULL_TVALUE;
	}
	
}

int SortedMap::getKeyRange() const {
	/*
		BC: Theta(m) - when the map has only one element
		TC : Theta(m)
		WC : Theta(m)
	*/
	if (this->nrElems == 0) {
		return -1;
	}
	int min = this->T[0].first;
	int max = this->T[0].first;
	for (int i = 1; i < this->m; i++) {
		if (this->T[i] != NULL_TPAIR) {
			if (this->T[i].first < min) {
				min = this->T[i].first;
			}
			if (this->T[i].first > max) {
				max = this->T[i].first;
			}
		}
	}
	return max - min;
}

/*

TValue SortedMap::add(TKey k, TValue v) {
	//TODO - Implementation
	int i = 0;
	int start = hash1(k) % this->m;
	int step = hash2(k) % this->m;
	int pos = start;

	while (i < this->m && this->T[pos] != NULL_TPAIR) {
		if (this->T[pos].first == k) {
			TValue oldValue = this->T[pos].second;
			this->T[pos].second = v;
			return oldValue;
		}
		i++;
		pos = (pos + step) % k;
	}
	i = 0;
	pos = start;
	while (i < this->m && this->T[pos] != NULL_TPAIR)
	{
		i++;
		pos = (pos + step) % k;
	}

	if (i == this->m) {
		//// resize, rehash and compute the position for k again
		//// implement the resize function
		cout << "resize \n" << endl;
		//TElem* newT = new TElem[this->m * 2 + 1];
		//for (int i = 0; i < this->m * 2 + 1; i++) {
		//	newT[i] = NULL_TPAIR;
		//}

		//for (int i = 0; i < this->m; i++) {
		//	if (this->T[i] != NULL_TPAIR) {
		//		int j = 0;
		//		int newPos = hash1(this->T[i].first);
		//		int newstep = hash2(this->T[i].first);
		//		while (j < this->m * 2 + 1 && newT[newPos] != NULL_TPAIR) {
		//			j++;
		//			newPos = (newPos + newstep) % (this->m * 2 + 1);
		//		}
		//		newT[newPos] = this->T[i];
		//	}
		//}
		//delete[] this->T;
		//this->T = newT;
		//this->m = this->m * 2 + 1;
		//this->T[pos] = make_pair(k, v);
		//this->nrElems++;
		////cout << "2added : " << k << " " << v << endl;

        TElem* newT = new TElem[this->m * 2];
		for (int i = 0; i < this->m * 2; i++) {
			newT[i] = NULL_TPAIR;
		}
		for (int i = 0; i < this->m; i++) {
			if (this->T[i] != NULL_TPAIR) {
				int j = 0;
				int newPos = hash1(this->T[i].first) % (this->m * 2);
				int newstep = hash2(this->T[i].first) % (this->m * 2);
				while (j < this->m * 2 && newT[newPos] != NULL_TPAIR) {
					j++;
					newPos = (newPos + newstep) % (this->m * 2);
				}
				newT[newPos] = this->T[i];
			}
		}
		delete[] this->T;
		this->T = newT;
		this->m = this->m * 2;
		this->T[pos] = make_pair(k, v);
		this->nrElems++;

	}
	else {
		this->T[pos] = make_pair(k, v);
		this->nrElems++;
		//cout << "1added : " << k << " " << v << endl;

	}


	return NULL_TVALUE;
}
*/
TValue SortedMap::search(TKey k) const {
	/*
		BC: Theta(1) - when the element is the first one
		TC : O(n)
		WC : Theta(n) - when the element is not in the map
	*/
	//TODO - Implementation
	int i = 0;
	int pos = hash1(k) % this->m;
	int step = hash2(k) % this->m;
	while (i < this->m && this->T[pos] != NULL_TPAIR) {
		if (this->T[pos].first == k) {
			return this->T[pos].second;
		}
		i++;
		pos = (pos + step) % this->m;
	}

	return NULL_TVALUE;

}

TValue SortedMap::remove(TKey k) {
	
		//BC: Theta(1) - when the element is the first one
		//TC : O(n)
		//WC : Theta(n) - when the element is not in the map
	
	//TODO - Implementation


	int i = 0;
	int pos = hash1(k) % this->m;
	int step = hash2(k) % this->m;
	while (i < this->m && this->T[pos] != NULL_TPAIR) {
		//cout << this->T[pos].first << " " << k << endl;
		if (this->T[pos].first == k) {
			TValue oldValue = this->T[pos].second;
			this->T[pos] = DELETED_TPAIR;
			this->nrElems--;
			return oldValue;
		}
		i++;
		pos = (pos + step) % this->m;
	}

	return NULL_TVALUE;

 //   int i = 0;
	//while (i < this->m) {
	//	if (this->T[i].first == k) {
	//		TValue oldValue = this->T[i].second;
	//		this->T[i] = NULL_TPAIR;
	//		this->nrElems--;
	//		return oldValue;
	//	}
	//	i++;
	//}

	//return NULL_TVALUE;
}

int SortedMap::size() const {
	//TODO - Implementation
	return this->nrElems;
}

bool SortedMap::isEmpty() const {
	//TODO - Implementation
	return this->nrElems == 0;
}

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

SortedMap::~SortedMap() {
	//TODO - Implementation
	delete[] this->T;
}
