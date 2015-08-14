/** --------------------------------------------------------------
* knn test.
* Alexander Karlsson, 2015-08-14
* ---------------------------------------------------------------- */
#include "../knn.cc"
#include "../../matplotlibcpp.h"
#include <time.h>
#include <stdlib.h>
namespace plt = matplotlibcpp;


int main() {
	string file = "testfiles/knn/test_c.txt";
	vector<Item> train_data, items;
	
	train(train_data, file);
	

	vector<int> sx, sy, mx, my, mpx, mpy;

	for (auto t: train_data) {
		if(t.label == "s") {
			sx.push_back(t.x);
			sy.push_back(t.y);

		} else if(t.label == "m") {
			mx.push_back(t.x);
			my.push_back(t.y);
		
		} else if(t.label == "mp") {
			mpx.push_back(t.x);
			mpy.push_back(t.y);
		}
	}

	plt::plot(sx,sy,"ro");
	plt::plot(mx,my,"bo");
	plt::plot(mpx,mpy,"go");
	plt::show();


  	/* initialize random seed: */
 	srand (time(NULL));
  	int x, y;
  	for (int i = 0; i < 5000; ++i) {
  		x = rand() % 200 + 1;
  		y = rand() % 200 + 1;

  		Item it;
  		it.x = x;
  		it.y = y;

  		items.push_back(it);
  	}


	knn(items,train_data,10);



 
	vector<int> sxi, syi, mxi, myi, mpxi, mpyi;

	for (auto t: items) {
		if(t.label == "s") {
			sxi.push_back(t.x);
			syi.push_back(t.y);

		} else if(t.label == "m") {
			mxi.push_back(t.x);
			myi.push_back(t.y);
		
		} else if(t.label == "mp") {
			mpxi.push_back(t.x);
			mpyi.push_back(t.y);
		}
	}

	plt::plot(mxi, myi, "bo");
	plt::plot(sxi, syi,"ro");
	plt::plot(mpxi,mpyi,"go");
	plt::xlim(0, 200);
	plt::ylim(0, 200);
	plt::show();

	
}