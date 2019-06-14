/** ------------------------------------------------------------
* Tests for the longest increasing subsequence implementation
* Alexander Karlsson 2015-07-20
* -------------------------------------------------------------- */
#include "../longest_incr_subsequence.cc"
#include <iostream>
using namespace std;

int main() {
	vector<int> seq{0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
	vector<int> subseq = longest_incr_subseq(seq);

	cout << "size " << subseq.size() << endl;

	for (auto p: subseq) {
		cout << p << " ";
	}
	cout << endl;

	vector<int> seq2{100,1,99,97,2,96,3,95,94,4,5,6,93,92,
		91,7,8,9,10,90,89,88,11,12};
	vector<int> subseq2 = longest_incr_subseq(seq2);
	
	cout << "size " << subseq2.size() << endl;

	for (auto p: subseq2) {
		cout << p << " ";
	}
	cout << endl;

}