/** --------------------------------------------------------------
* My Decision tree implementation. Really simple, no fancy stuff.
* The implemenation uses hash-maps with string keys.
* Frome file:
* <Routine name> <value> <string, use if true> <string, use if false>
* Check: Routine name > value
* Alexander Karlsson, begun 2015-08-20
* ---------------------------------------------------------------- */
#ifndef MYTREE_H
#define MYTREE_H

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <set>


struct Item {
	int x,y;
	std::string label;	
};

class MyTree {

public:
	/* Constructor */
	MyTree(std::string first);
	/* Insert new node in tree */
	void insert(std::string var, std::string cond, std::string var_true, std::string var_false);
	/* Add an Item, after checking all nodes and stopping condition is reached,
	 if !train, training data is added, if train new data is addad, which need a label, 
	 majority vote is needed. */
	void addItem(Item item, bool train);
	/* Returns all added items */
	std::map<std::string,std::vector<Item>> getItems() {return items;}


private:
	std::map<std::string,std::vector<std::string>> tree;
	std::map<std::string,std::vector<Item>> items;
	std::string start;
	std::set<std::string> labels;
};


#endif