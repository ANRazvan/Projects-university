#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

    int current_index;

	//TODO - Representation

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

