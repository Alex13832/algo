/** ------------------------------------------------------------
* Self Organizing lists. 
* Alexander Karlsson, 2015-07-16
* -------------------------------------------------------------- */
#ifndef SOLIST_H
#define SOLIST_H

#include "doubly_linked_list.cc"

template <typename T> class SOList {

public:
	
	typedef T value_type;
	/* Use this when searching */
	T at(const int k) const {return list->at(k);}
	/* This will modify the list */
	virtual T operator[](const int k) = 0;
	void push_back(T item) { list->push_back(item); }
	int size() { return list->length(); };

protected:
	DoublyLinkedList<T> *list = new DoublyLinkedList<T>;

};

#endif



/** Move to front method ------------------------------------- 
* An element is moved to the front if accessed. */

#ifndef SOLISTFRONT_H
#define SOLISTFRONT_H

template <typename T> 
class SOListFront : public SOList<T> {

public:
	SOListFront() {}
	T operator[](const int k);
};

#endif


/** Count method --------------------------------------------- 
* An element is moved one step or several steps to the front
* if the number of access times exceeds its predecessor(s). */

#ifndef SOLISTCOUNT_H
#define SOLISTCOUNT_H

#include <map>

template <typename T> 
class SOListCount : public SOList<T> {

public:
	T operator[](const int k);
private:
	map<T,int> counter;
};

#endif


/** Transpose method ----------------------------------------- 
* An element is swapped with its predecessor if accessed */

#ifndef SOLISTTRANSPOSE_H
#define SOLISTTRANSPOSE_H

template <typename T> 
class SOListTranspose : public SOList<T> {

public:
	T operator[](const int k);
};

#endif