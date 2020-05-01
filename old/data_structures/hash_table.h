/** ------------------------------------------------------------
* Header file for HashTable
* Alexander Karlsson, 2015-08-29
* -------------------------------------------------------------- */
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <string>
#include <list>
#include <vector>

#define LENGTH 100000

template <typename T> class HashTable {

public:
	typedef T value_type;

	HashTable();
	/* Inserts a value with key, totally uneccessary since one can use []*/
	void insert(std::string key, T value);
	/* Returns the value that belongs to a key*/
	T get(std::string key) const;
	/* Remove a value with the key */
	void remove(std::string key);
	
	/** The proxy class makes it possible to (1) return value that belongs to a key
	(2) overwrite a value that belongs to a key and (3) assignment */

	template <typename K> class proxy {
	public:
		proxy(HashTable<K> &h, std::string key) : ht(h), key(key) {}
		operator K() const {
			return ht.get(key);
		}
		proxy & operator=(K const &value) {
			ht.insert(key,value);
			return *this;
		}
	private:
		HashTable<K> & ht;
		std::string key;

	};

	proxy<T> operator[](const std::string& key) {return proxy<T>(*this, key);}

private:
 	std::vector<std::pair<std::string,T>> *chain = new std::vector<std::pair<std::string,T>>[LENGTH];
	/* Comuptes the hash for the key */
	uint hashi(const std::string key, const uint seed = 0) const;

};


#endif