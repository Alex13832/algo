/** ------------------------------------------------------------------
* Boyer-Moore algorithm for finding the location of a substring. 
* This implementation is modified, in a way such that all locations 
* of a substring are found.
* Alexander Karlson, 2015-07-21 
* -------------------------------------------------------------------- */
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int last_occurence(string str, char c) {
	int index = str.length();
	while (index != 0) {
		if (str[index] == c) {
			return index;
		} 
		index--;	
	}
	return 0;
}

/* Modified Boyer-Moore, finds all occurrences */
vector<int> boyer_moore(string text, string pattern) {
	int m = pattern.length(), n = text.length(), i = m-1, j = i;
	vector<int> matches;
	int chunk = 0, w_length = pattern.length();


	do {
		if (pattern[j] == text[i]) {
			if (j == 0) {
				matches.push_back(i+chunk);
				text = text.substr(i+w_length);
				chunk = chunk + i + w_length;
				m = w_length, n = text.length(), i = m-1, j = i;
			} else {
				i--;
				j--;
			}

		} else {
			i = i + m - min(j,1+last_occurence(text,text[i]));
			j = m - 1;
		}

	} while (i < n-1);

	return matches;
}