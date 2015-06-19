/* -----------------------------------------------------
* Rabin-Karp algorithm implementation
* Alexander Karlson, 2015-06-16 
* ---------------------------------------------------**/
#include <string>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

/* Finger-print */
ulong fingerprint(string str) {
	hash<string> shash;
	return shash(str);
}


/* Finds starting positions of every occurence of pattern in text */
vector<int> rabin_karp(string text, string pattern) {
	vector<int> pos;	
	size_t n = text.length();
	size_t m = pattern.length();
	ulong hash_p = fingerprint(pattern);
	ulong hash_t = fingerprint(text.substr(0,m));

	for (size_t i = 0; i < (n-m+1); i++) {
		if (hash_t == hash_p) {
			if (text.substr(i,m) == pattern) pos.push_back(i);
		} 
		string temp = text.substr(i+1,m);
		hash_t = fingerprint(temp);
	}

	return pos;
}


/* Finds starting positions of occurences patterns in text */
vector<int> rabin_karp_multi(string text, set<string> patterns, int m) {
	set<ulong> hash_pm;
	vector<int> pos;
	size_t n = text.length();

	for (auto pattern: patterns) {
		hash_pm.insert(fingerprint(pattern));
	}

	ulong hash_t = fingerprint(text.substr(0,m));

	for (size_t j = 0; j <(n-m+1); j++) {
		bool h_find = hash_pm.find(hash_t) != hash_pm.end();
		bool p_find = patterns.find(text.substr(j,m)) != patterns.end();
		if (h_find && p_find) pos.push_back(j);
		
		string temp = text.substr(j+1,m);
		hash_t = fingerprint(temp);
	}

	return pos;
}


int main() {

	string sentence = "one two one three one two hello one";
	set<string> words;
	words.insert("one");
	words.insert("two");
	vector<int> pos1 = rabin_karp(sentence, "one");
	vector<int> pos2 = rabin_karp_multi(sentence, words,3);

	cout << "Rabin-Karp single word seach: " << endl;
	for (auto p1: pos1) {
		cout << p1 << " ";
	} 
	cout << endl;
	cout << "Rabin-Karp multi word seach: " << endl;

	for (auto p2: pos2) {
		cout << p2 << " ";
	}
}