/** ------------------------------------------------------------
* This code will find the longest increasing subsequence
* Alexander Karlsson 2015-07-20
* -------------------------------------------------------------- */
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

/** Returns the longest increasing subsequenc of the input 
sequence seq */
vector<int> longest_incr_subseq(const vector<int> seq) {

	size_t N = seq.size(); 
	/* P stores the index of the predecessor of seq[i] */
	vector<int> P(N);
	/* M stores the index of the smallest value seq[k] */
	vector<int> M(N+1);
	int L = 1;

	for (size_t i = 0; i < N; i++) {
		int min = 1, max = L, mid;

		/* Binary search */
		while (min <= max) {
			mid = ceil((min+max)/2);

			if (seq[M[mid]] < seq[i]) min = mid+1;
			else max = mid-1;
		}

		int Lhat = min;
		P[i] = M[Lhat-1];
		M[Lhat] = i;

		if (Lhat > L) L = Lhat;
	}

	/* Reconstruction of the longest subsequence */
	vector<int> subseq(L);
	int k = M[L];

	for (size_t i = L-1; i > 0; i--) {
		subseq[i] = seq[k];
		k = P[k];
	}
	subseq[0] = M[1];

	return subseq;
}