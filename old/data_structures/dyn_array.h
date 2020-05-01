/** ------------------------------------------------------------
* Declaration of a dynamic array implementation DynArray.
* Alexander Karlsson, 2015-07-25
* -------------------------------------------------------------- */

#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <memory>
#include <iostream>
#include "dynarray_iterators.cc"
	
template <typename T> class DynArray {
public:

	typedef T value_type;
	DynArray();
	/* Constructor with initializer list */
	DynArray(std::initializer_list<T> lst);
	/* Constructor with different size */
	DynArray(const std::size_t s);
	/* Constructor with different size and same value */
	DynArray(const std::size_t s, const T item);
	
	/* Add item last */
	void push_back(T item);
	/* Returns the size */
	size_t size() {return index;}
	
	/* Returns the item at index n */
	T const operator[](std::size_t n) const {
		T item = items[n];		
		return item;
	}
	
	/* Returns the item at index n, this can be used with assignment */
	T & operator[](std::size_t n) {
		T & item = items[n];		
		return item;
	}
		
	/* Returns the item last in the list */	
	T back() {return items[index-1];}
	void pop_back();
	/* Removes the element at pos */
	void removeAt(const int pos); 
	
	/* Prints all :) */
	void printAll();
	
	/* Forward iterator */ 
	using iterator1 = DynArrayIterator<T>;
	iterator1 begin() { return iterator1(0, &items); }
	iterator1 end() { return iterator1(index, &items); }
	
	/* Reverse iterator */
	using iterator2 = RDynArrayIterator<T>;
	iterator2 rbegin() { return iterator2(index-1, &items); }
	iterator2 rend() {return iterator2(-1, &items); }

protected:
	T* items = new T[8];
private:
	size_t limit = 8;

	size_t index = 0;
	
	/** Private function that makes the local array bigger when 
	more space is needed */
	void resize(size_t s);

};

#endif