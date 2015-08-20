/** --------------------------------------------------------------
* Train-data funtion for MyTree
* Alexander Karlsson, begun 2015-08-20
* ---------------------------------------------------------------- */
#include "my_tree.cc"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

MyTree train(string tree_file, string train_file) {
	ifstream file(tree_file);
	string line;
	getline(file,line);
	vector<string> cont; 
        string str(line);
        string buf; 		// buffer string
        stringstream ss(str);   // stream

        while (ss >> buf) cont.push_back(buf);

        MyTree tree(cont[0]);
        tree.insert(cont[0],cont[1],cont[2],cont[3]);

	/* Get line and split by whitespace */
	while (getline(file, line)){
	        vector<string> cont; 
	        string str(line);
	        string buf; 		// buffer string
	        stringstream ss(str);   // stream

	        while (ss >> buf) cont.push_back(buf);

	        tree.insert(cont[0],cont[1],cont[2],cont[3]);
	}

	ifstream file2(train_file);
	string line2; 

	while (getline(file2, line2)){
	        vector<string> cont; 
	        string str(line2);
	        string buf; 		// buffer string
	        stringstream ss(str);   // stream

	        while (ss >> buf) cont.push_back(buf);

	        Item item;
	        item.x = stoi(cont[0]);
	        item.y = stoi(cont[1]);
	        item.label = cont[2];
	        tree.addItem(item,true);
	}


	return tree;
}