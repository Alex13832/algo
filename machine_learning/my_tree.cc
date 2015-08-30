/** --------------------------------------------------------------
* Implementation of MyTree
* Alexander Karlsson, begun 2015-08-20
*
* N.B. Not sure if this is ok, sometimes work as expected, 
* sometimes not.
* ---------------------------------------------------------------- */
#include "my_tree.h"
using namespace std;

MyTree::MyTree(string first) : start(first) {}

void MyTree::insert(string var, string cond, string var_true, string var_false) {
	vector<string> ins{var, cond, var_true, var_false};
	tree.insert(pair<string,vector<string>>(var,ins));
}

void MyTree::addItem(Item item, bool train) {
	string var = start;
	/* Go through tree */
	while (var[0] != 's') {
		vector<string> vec = tree[var];
		
		int cond = stoi(vec[1]);
		bool left = false;

		if (var[0] == 'X') {
			
			if (item.x > cond) left = true;

		} else if (var[0] == 'Y') {

			if (item.y > cond) left = true;
		}
		
		left == true ? var = vec[2] : var = vec[3];

	}

	if (!train) {
		string label;
		int max;
		map<string,int> label_count;
		vector<Item> itms = items[var];

		/* Count the number of occurrences of a label*/
		for (auto it: itms) {
			label_count[it.label]++;
		}

		/* Majority vote */
		for (auto it = label_count.begin(); it != label_count.end(); ++it) {
			if (it->second > max) {
				max = it->second;
				label = it->first;
			}
		}

		item.label = label;
		//cout << label << endl;



	}

	items[var].push_back(item);

}