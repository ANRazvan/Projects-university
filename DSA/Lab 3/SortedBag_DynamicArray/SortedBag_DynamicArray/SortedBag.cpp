#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <stdexcept>
#include <iostream>


SortedBag::SortedBag(Relation r): capacity{10}, bagsize{0}, relation(r), size_arr{0}
{

    elements = new TComp [capacity];
    frec = new int [capacity];

	//TODO - Implementation
}

void SortedBag:: resize_array()
{
    int new_capacity = this->capacity *2;
    TComp *new_elemets = new TComp [new_capacity];
    int *new_frec= new int [new_capacity];

    for (int i=0;i<this->size_arr;i++)
    {
        new_elemets[i] = this->elements[i];
        new_frec[i] = this->frec[i];
    }

    delete[] elements;
    delete[] frec;

    this->elements=new_elemets;
    this->frec = new_frec;
    this->capacity=new_capacity;
}

int SortedBag:: find_element_index(TComp e) const
{
    for (int i=0; i<this->size_arr;i++)
    {
        if(this->elements[i] == e)
            return i;

    }
    return -1;
}

void SortedBag::add(TComp e) {

    int index = find_element_index(e);
    if (index!=-1)
    {
        this->frec[index]++;
        this->bagsize++;

    }
    else
    {
        if( this-> capacity == this->bagsize)
        {
            resize_array();
        }

        int i = this->size_arr-1;
        while(i>=0 && !relation(elements[i], e))
        {
            this->elements[i+1] = this-> elements[i];
            this -> frec[i+1] = this -> frec[i];
            i--;
        }

        this->elements[i+1] = e;
        this-> frec[i+1]=1;
        this->bagsize++;
        this->size_arr++;
    }



    //TODO - Implementation
}


bool SortedBag::remove(TComp e)
{

    int index = find_element_index(e);
    if (index == -1) {
        return false;
    } else {
        if (this->frec[index] > 1)
        {
            this->frec[index]--;
            this->bagsize--;
        } else {
            for (int i = index; i < this->size_arr - 1; i++)
            {
                this->elements[i] = this->elements[i + 1];
                this->frec[i] = this->frec[i + 1];
            }
            this->bagsize--;
            this->size_arr--;
        }
        return true;
    }

	//TODO - Implementation
    //return false;
}


bool SortedBag::search(TComp elem) const
{
    for (int i=0; i<this->size_arr;i++)
    {
        if(this->elements[i] == elem)
            return true;
    }
    return false;

	//TODO - Implementation
	//return false;
}


int SortedBag::nrOccurrences(TComp elem) const
{
    int index = find_element_index(elem);
    if (index!=-1)
    {
        return this->frec[index];
    }
    return 0;

	//TODO - Implementation
	//return 0;
}



int SortedBag::size() const
{
    return this->bagsize;
	//TODO - Implementation
	//return 0;
}


bool SortedBag::isEmpty() const
{
    if ( size() == 0)
        return true;
    return false;
	//TODO - Implementation
	//return false;
}


SortedBagIterator SortedBag::iterator() const
{
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
    delete[] elements;
    delete [] frec;
	//TODO - Implementation
}


void SortedBag::display()
{
    for (int i=0;i<this->size_arr;i++)
    {
        std::cout<<this->elements[i]<<" "<<this->frec[i]<<std::endl;
    }
}
