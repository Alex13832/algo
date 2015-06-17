/** ------------------------------------------------
* Stable-Marriage problem implementation using
* the Gale-Shapley algorithm
* Alexander Karlsson, 2015-06-17
*
* File usage: men in [1....n], women in [1...n]
* setup men and women ranking e.g.
* (men)		1: 1 2 3 4 ... n
		2: 3 4 1 2 ... n
		und zu weiter. 
(do the same for women)
---------------------------------------------- */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* Gale-Shapley algorithm*/
void stable_marriage(vector<vector<int>> men_pref, vector<vector<int>> women_pref) {
	
	int couples = men_pref[0].size();
	vector<int> engaged_men(couples, false);
	vector<int> engaged_women(couples, false);

	/* While there is a man  who is not engaged 
  	   and has not proposed to every woman on his list */

	int m = 0, m2 = 0;
	bool man_free = true;
	
	while (man_free) {
		int w = men_pref[m].front();
		men_pref[m].erase(men_pref[m].begin());
		cout << " w " << w << endl;
		if (engaged_women[w-1] == 0) {
			engaged_women[w-1] = m+1;
			engaged_men[m] = w;

		} else {
			m2 = engaged_women[w-1] - 1;

			auto pref1 = find(women_pref[w-1].begin(),women_pref[w-1].end(),m+1);
			auto pref2 = find(women_pref[w-1].begin(),women_pref[w-1].end(),m2+1);

			if (pref1 < pref2) {
				engaged_men[m] = w;
				engaged_women[w-1] = m+1;
				engaged_men[m2] = 0;
			}
		}
		
		for (size_t i = 0; i < engaged_men.size(); ++i) {
			if (engaged_men[i] == 0) m = i;
		}


		if ( find(engaged_men.begin(),engaged_men.end(),0) == engaged_men.end()) {
			man_free = false;
		}
		

	
		cout<< "m " << m << endl;
	}

	/* Print result */
	m = 1 ;
	for (auto w: engaged_men) {
		cout << "m: " << m << " w: " << w << endl;
		m++;
	}
}