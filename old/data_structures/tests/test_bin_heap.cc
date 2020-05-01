/** ------------------------------------------------------------
* Tests for BinaryHeap
* Alexander Karlsson, begun 2015-07-26
* -------------------------------------------------------------- */
#include "../binary_heap.cc"

int main() {

	cout << "Simple push-test" << endl;
	BinaryHeap<int> *bh = new BinaryHeap<int>;
	bh->push(5);
	bh->push(6);
	bh->push(4);
	bh->push(0);
	bh->push(1);
	bh->push(2);
	bh->push(3);
	bh->push(7);

	bh->printAll();

	cout << "Test constructor with vector (Heapify)" << endl;
	vector<int> vec{8,3,1,2,4,5,6,10};
	BinaryHeap<int> *bh2 = new BinaryHeap<int>;
	bh2->heapify(vec);

	bh2->printAll();

	cout << "Test peek" << endl;
	cout << bh2->peek() << endl;

	cout << "Test pop (and percolate down) twice" << endl;
	cout << bh2->pop() << endl;
	bh2->printAll();
	cout << bh2->pop() << endl;
	bh2->printAll();

	delete bh; 
	delete bh2;

}