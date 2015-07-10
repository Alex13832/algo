#ifndef Node_H
#define Node_H

template <typename T>
struct Node {
	T value;
	Node *next = NULL;
};

#endif