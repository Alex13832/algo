#include "../queue.h"
#include <iostream>
using namespace std;

int main() {

	Queue<int> q;
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);
	q.enqueue(6);
	q.enqueue(7);
	q.enqueue(8);
	q.enqueue(9);

	cout << "Number of elements " << q.height() << endl;
	cout << "First element in the queue " << q.peak() << endl;

	cout << "Queue test. Should print FIFO, 1,2,3,..." << endl;

	while (!q.empty()) {
		int k = q.dequeue();
		cout << k << " ";
	}

	cout << endl;


}