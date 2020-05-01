/** ------------------------------------------------------------
* Implementations for functions that belong to hash_table.h
* Alexander Karlsson, 2015-08-29
* -------------------------------------------------------------- */
#include "hash_table.h"
#include <iostream>
#include <string>
using namespace std;


template <typename T> 
HashTable<T>::HashTable() {}


template <typename T> 
void HashTable<T>::insert(string key, T value) {
	uint pos = hashi(key) % LENGTH;

	if (chain[pos].empty())	{
		chain[pos].push_back(pair<string,T>(key,value));	
	} else {
		vector<pair<string,T>> & vec = chain[pos];
		for (auto& p: vec) {
			if (p.first == key) p.second = value; // Overwrite if value already exists
		}
	}

}


template <typename T> 
T HashTable<T>::get(string key) const {
	uint pos = hashi(key) % LENGTH;
	if (chain[pos].empty()) throw -1;

	vector<pair<string,T>> vec = chain[pos];

	for (auto p: vec) {
		if (p.first == key) return p.second;
	}

	throw string("no value found");
}


template <typename T>
void HashTable<T>::remove(string key) {
	uint pos = hashi(key) % LENGTH;

	if (!chain[pos].empty()) {
		vector<pair<string,T>> & vec = chain[pos];
		int count = 0;
		for (size_t i = 0; i < vec.size(); ++i) {
			if (vec[i].first == key)  {
				count = i;
				break;
			}	
		}
		vec.erase(vec.begin()+count);
	}
}


template <typename T> 
uint HashTable<T>::hashi(const string key, const uint seed) const {
	uint hash = seed;
	for (auto c: key) hash = hash * 101 + (int)c;
	return hash;
 }