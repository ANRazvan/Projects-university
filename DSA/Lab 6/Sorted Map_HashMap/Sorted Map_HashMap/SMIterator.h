#pragma once
#include "SortedMap.h"
#include <vector>
using namespace std;


//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
	const SortedMap& map;
	SMIterator(const SortedMap& mapionar);

	//TODO - Representation
	int currentPos;
	TElem* elements;


public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;
};

