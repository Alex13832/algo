/** --------------------------------------------------------------
* Decision test.
* Alexander Karlsson, begun 2015-08-20
* ---------------------------------------------------------------- */
#include "../decision.cc"
#include "../../matplotlibcpp.h"
#include <time.h>
#include <stdlib.h>
namespace plt = matplotlibcpp;


int main() {

	string tree_file = "decision/tree1";
	string train_data = "decision/train_data";
	MyTree tree = train(tree_file,train_data);
	vector<int> x[4],y[4];
	

	/* No training */

	/* initialize random seed: */
 	srand (time(NULL));
  	for (int i = 0; i < 10000; ++i) {
  		Item it;
  		it.x = rand() % 400;
  		it.y = rand() % 400;
  		tree.addItem(it,false);
  	}


	map<string,vector<Item>> items = tree.getItems();

	for (auto it = items.begin(); it != items.end(); ++it) {

		for (auto itm: it->second) {

			if (itm.label == "T") {
				x[0].push_back(itm.x);
				y[0].push_back(itm.y);
			}

			if (itm.label == "C") {
				x[1].push_back(itm.x);
				y[1].push_back(itm.y);
			}


			if (itm.label == "St") {
				x[2].push_back(itm.x);
				y[2].push_back(itm.y);
			}

			if (itm.label == "Sq") {
				x[3].push_back(itm.x);
				y[3].push_back(itm.y);
			}


		}

	}
 	
 	plt::plot(x[0],y[0],"b^");
 	plt::plot(x[1],y[1],"yo");
 	plt::plot(x[2],y[2],"m*");
 	plt::plot(x[3],y[3],"cs");
 	plt::show();
	
}