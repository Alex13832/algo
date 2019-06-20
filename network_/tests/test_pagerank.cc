/** ----------------------------------------------------------
* Test cases for the implementation of the pagerank 
* algorithm.
* ------------------------------------------------------------ */
#include "../pagerank.cc"
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
using namespace std;

/** Large test cases with 50 nodes. Test-file downloaded from 
 http://introcs.cs.princeton.edu/java/16pagerank/ */
bool test50(string file) {
	ifstream infile(file);
	string line;
	int num = 0;
	getline(infile, line);
	size_t N = stoi(line);

	vector<vector<int>> M(N,vector<int>(N));
	vector<int> degree(N);

	while (getline(infile, line)){	
		vector<int> temp;
		string s = line;
		string delimiter = " ";
		size_t pos = 0;
		string token;
		while ((pos = s.find(delimiter)) != string::npos) {
		    	token = s.substr(0, pos);
			try {
				
				num = stoi(token);
				temp.push_back(num);

			} catch (std::invalid_argument&) { }
		    	s.erase(0, pos + delimiter.length());
		}

		try {
			int num = stoi(s);
			temp.push_back(num);
		} catch (std::invalid_argument&) { }
		
		for (size_t i = 0; i < temp.size(); i+=2) {
			M[temp[i]][temp[i+1]]++;
		}
	}

	for(size_t i = 0; i < N; i++) {
		degree[i] = accumulate(M[i].begin(),M[i].end(),0);	
	}

	vector<vector<double>> p = transition_mat(M,degree);
	vector<double> rank = page_rank(p, 0.85, 0.0001); 
	double s = accumulate(rank.begin(), rank.end(),0.0);

	bool b = s > 0.98 && s < 1.02;
	return b;
}

int main() {
	/* Test 1 */
	vector<vector<double>> M1;
	M1.push_back(vector<double>{0.0, 0.5, 0.5, 0.0, 0.0 });
	M1.push_back(vector<double>{0.0, 0.0, 0.0, 1.0, 0.0 });
	M1.push_back(vector<double>{0.0, 0.0, 0.0, 0.5, 0.5 });
	M1.push_back(vector<double>{0.0, 0.0, 0.0, 0.0, 1.0 });
	M1.push_back(vector<double>{1.0, 0.0, 0.0, 0.0, 0.0 });
	vector<double> r1 = page_rank(M1, 0.8, 0.001);
	
	double s1 = accumulate(r1.begin(), r1.end(),0.0);
	bool b1 = s1 > 0.98 && s1  < 1.02;

	/* Test 2 */
	vector<vector<double>> M2;
	M2.push_back(vector<double>{0,0.5,0.5,0,0,0,0,0});
	M2.push_back(vector<double>{0,0,0,1,0,0,0,0});
	M2.push_back(vector<double>{0,0.5,0,0,0.5,0,0,0});
	M2.push_back(vector<double>{0,0.3333,0,0,0.3333,0.3333,0,0});
	M2.push_back(vector<double>{0,0,0,0,0,0.3333,0.3333,0.3333});
	M2.push_back(vector<double>{0,0,0,0,0,0,0,1});
	M2.push_back(vector<double>{0,0,0,0,0.5,0,0,0.5});
	M2.push_back(vector<double>{0,0,0,0,0,0.5,0.5,0});
	vector<double> r2 = page_rank(M2, 0.85, 0.0001); 
	
	double s2 = accumulate(r2.begin(), r2.end(),0.0);
	bool b2 = s2 > 0.98 && s2  < 1.02;

	/* Test 3 */
	vector<vector<double>> M3;
	M3.push_back(vector<double>{0,0.3333,0.3333,0.3333});
	M3.push_back(vector<double>{0,0,0.5,0.5});
	M3.push_back(vector<double>{1,0,0,0});
	M3.push_back(vector<double>{0.5,0,0.5,0});
	vector<double> r3 = page_rank(M3, 0.8, 0.001);

	double s3 = accumulate(r3.begin(), r3.end(),0.0);
	bool b3 = s3 > 0.98 && s3  < 1.02;

	/* Test 4 */
	vector<vector<int>> M4;
	M4.push_back(vector<int>{0,1,0,0,0});
	M4.push_back(vector<int>{0,0,2,2,1});
	M4.push_back(vector<int>{0,0,0,1,0});
	M4.push_back(vector<int>{1,0,0,0,0});
	M4.push_back(vector<int>{1,0,1,0,0});

	vector<int> deg = {1,5,1,1,2};
	vector<vector<double>> p = transition_mat(M4,deg);
	vector<double> r4 = page_rank(p, 0.85, 0.0001); 

	double s4 = accumulate(r4.begin(), r4.end(),0.0);
	bool b4 = s4 > 0.98 && s4  < 1.02;

	bool b5 = test50("testfiles/medium.txt");


	bool bauta = b1 && b2 && b3 && b4 && b5;
	if(bauta) {
		cout << "PageRank test cases passed" << endl;
	} else {
		cout << "PageRank test cases failed" << endl;
	}
}