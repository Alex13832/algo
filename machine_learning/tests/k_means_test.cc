/** --------------------------------------------------------------
* K-means clustering test.
* Alexander Karlsson, 2015-08-14
* ---------------------------------------------------------------- */
#include "../k_means.cc"
#include "../../matplotlibcpp.h"
#include <time.h>
#include <stdlib.h>
namespace plt = matplotlibcpp;

int main() {
	vector<Item> items;

  	/* initialize random seed: */
 	srand (time(NULL));
  	for (int i = 0; i < 1000000; ++i) {
  		Item it;
  		it.x = rand() % 2000 + 1;
  		it.y = rand() % 2000 + 1;
  		items.push_back(it);
  	}

  	int k = 8;
	vector<vector<Item>> klusters = k_means(items,k);
	vector<int> x[15], y[15];

	for (int i = 0; i < k; ++i) {
		for (auto it: klusters[i]) {
			x[i].push_back(it.x);
			y[i].push_back(it.y);
		}

		plt::plot(x[i], y[i],"o");
	}

	plt::show();

}