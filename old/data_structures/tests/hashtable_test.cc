/** ------------------------------------------------------------
* Tests for HashTable
* Alexander Karlsson, 2015-07-17
* -------------------------------------------------------------- */
#include "../hash_table.cc"
#include <iostream>
using namespace std;


int main() {
	HashTable<int> ht;
	string testa = "heppa";
	ht.insert(testa,666);
	cout <<  ht.get("heppa") << endl;

	string k = "knurra";
	ht[k] = 500;

	cout << ht[k] << endl;

	ht[k] = 700;

	cout << ht[k] << endl;

	

}