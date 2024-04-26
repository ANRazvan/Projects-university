#pragma once
#include "Map.h"
class MapIterator
{
	//DO NOT CHANGE THIS PART
	friend class Map;
private:
	const Map& map;
	//TODO - Representation
	int current;

	MapIterator(const Map& m);
public:
	void first();
	void next();
	void previous();
	TElem getCurrent();
	bool valid() const;
};


