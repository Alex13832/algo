/** ------------------------------------------------------------
* Implementation of iterator operations.
* Can be used for begin(), end(), rbegin() and rend()
* Alexander Karlsson, begun 2015-07-17
* -------------------------------------------------------------- */
using namespace std;

/* Operators for forward iterator, begin(), end() */

template <typename T> struct ListIterator {
	typedef T value_type;

	Node<T> *node;

	explicit ListIterator(Node<T> *n) : node(n) {}

	bool operator!=(const ListIterator& rhs) const {
		return node != rhs.node;
	}

	T& operator*() { return node->value;}

	ListIterator& operator++() {
		node = node->next;
		return *this;
	}

};

/* Operators for backward iterators, rbegin(), rend()*/

template <typename T> struct RListIterator {
	typedef T value_type;

	Node<T> *node;

	explicit RListIterator(Node<T> *n) : node(n) {}

	bool operator!=(const RListIterator& rhs) const {
		return node != rhs.node;
	}

	T& operator*() { return node->value;}

	RListIterator& operator++() {
		node = node->prev;
		return *this;
	}

};


