#include <iostream>
using namespace std;

/* Forward Iterator for DynArray ---------------------------- */

template <typename T> struct DynArrayIterator {
	typedef T valye_type;

	T* items;
	size_t index = 0;
	
	DynArrayIterator(size_t i, T * itms[]) {
		items = *itms;
		index = i;
	} 
	
	bool operator!=(const DynArrayIterator& rhs) const {
		return index != rhs.index;
	}
	
	T& operator*() { return items[index]; }

	DynArrayIterator& operator++() {
		index++;
		return *this;
	}
};


/* Reverse iterator for DynArray ----------------------------- */

template <typename T> struct RDynArrayIterator {
	typedef T valye_type;

	T* items;
	size_t index;
	
	RDynArrayIterator(size_t i, T * itms[]) {
		items = *itms;
		index = i;
	} 
	
	bool operator!=(const RDynArrayIterator& rhs) const {
		return index != rhs.index;
	}
	
	T& operator*() { return items[index]; }

	RDynArrayIterator& operator++() {
		index--;
		return *this;
	}
};

