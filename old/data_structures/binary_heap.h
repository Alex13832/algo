/** ------------------------------------------------------------
* BinaryHeap declaration
* Alexander Karlsson, begun 2015-07-26
* -------------------------------------------------------------- */
#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <iostream>
#include <vector>

template <typename T> class BinaryHeap {
	
public:

	typedef T value_type;

	BinaryHeap() : size(0) {}		
	~BinaryHeap() { delete array; }

	void heapify(std::vector<T> vec);
	/* Add new item */
	void push(T item);
	/* Returns min */
	T peek() {return (*array)[0]; }
	/* Removes and returns min */
	T pop();					

	bool isEmpty() { return array->size() == 0; };

	void printAll();

	/** Later
	void merge(BinaryHeap<T> bh)
	*/

private:

	std::vector<T> *array = new std::vector<T>;
	int size;
	/* Move items up */
	void percolate_up(int k);
	/* Move items down */
	void percolate_down(int k);
	/* Index of child's parent */
	int parent(int k);
	/* Index of parent's "left" child */
	int child_left(int k);
	/* Index of parent's "right" child */
	int child_right(int k);
};

#endif