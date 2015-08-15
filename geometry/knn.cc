/** --------------------------------------------------------------
* K nearest neighbors (knn or KNN) implementation. Scans the
* set of items that is already processed for k nearest neighbors
* to a not already processed item and sets its label that is most
* frequent in knn.
* Alexander Karlsson, 2015-08-14
* ---------------------------------------------------------------- */
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
using namespace std;

struct Item {
	string label;	//Label/Name
	int x, y; 	//Location
	double dist;	//Distance to temporary Item
};

/* For comparing labels */
struct Item_string_comp {
  bool operator() (const  Item p1, const Item p2) const
  {return p1.label < p2.label;}
};

/* For comparing distances */
struct Item_dist_comp {
  bool operator() (const  Item p1, const Item p2) const
  {return p1.dist < p2.dist;}
};


/* Reads a file with "train-data", on each line written as: x y label */
void train(vector<Item>& train_data, string filename) {
	//vector<Item> train_data[max_x][max_x];

        ifstream file(filename);
        string line;

        /* Get line and split by whitespace */
        while (getline(file, line)){
                vector<string> line_content; 
                string str(line);
                string buf; 		// buffer string
                stringstream ss(str);   // stream

                while (ss >> buf) line_content.push_back(buf);

                Item item;
                item.x = stoi(line_content[0]);
                item.y = stoi(line_content[1]);
                item.label = line_content[2];

                train_data.push_back(item);
        }
}


/* k-nn algorithm, runs the algorithms with a chosen k. 
 Input: data-vector with no labels. 
 Returns: data-vector with labels set. */
void knn(vector<Item>& data, vector<Item> train_data, int k) {

	set<string> labels; 	/* Collect the labels in this vector*/
	size_t add_item = 0;

	if ((size_t) k > data.size()) {
		cout << "Too few data elements" << endl;
		return;
	} 
	
	/* Process all new items */	
	for (auto& item: data) {
		int x1 = item.x, y1 = item.y;

		for (auto& train_item: train_data) {
			int x2 = train_item.x, y2 = train_item.y;
			train_item.dist = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1); 
			labels.insert(train_item.label);
		}

		/* If the data-vector is very large, and speed is super important,
		try something else... */
		sort(train_data.begin(), train_data.end(), Item_dist_comp());
		vector<Item> cp_dat(k);
		copy(train_data.begin(), train_data.begin()+k, cp_dat.begin());
		sort(cp_dat.begin(),cp_dat.end(),Item_string_comp());

		vector<string> lbs;
		for (auto lb: cp_dat) lbs.push_back(lb.label);

		/* Find the label that is the most popular */
		int max = 0;
		string lbl;
		for (auto label: labels) {
			int ct = count(lbs.begin(),lbs.end(),label);

			if (ct > max) {
				max = ct;
				lbl = label;
			}

		}

		item.label = lbl;
		
		/* Add some new elements to the training set */
		if (++add_item == 7) {
			train_data.push_back(item);
			add_item = 0;	
		}
	
	}
}