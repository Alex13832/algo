#include <vector>
#include <string>
#include <fstream>
#include "../stable_marriage.cc"
using namespace std;

vector<vector<int>> read_file(string file) {
	ifstream infile(file);
	vector<vector<int>> vec;

	string line;
	int person = 0;
	while (getline(infile, line)){	
		
		string s = line;
		string delimiter = " ";
		vector<int> sub;
		vec.push_back(sub);
		size_t pos = 0;
		string token;
		

		while ((pos = s.find(delimiter)) != string::npos) {
		    	token = s.substr(0, pos);
			try {
				
				int num = stoi(token);
				vec[person].push_back(num);

			} catch (std::invalid_argument&) { }
			
		    	s.erase(0, pos + delimiter.length());
		    	
		}

		try {
			int num = stoi(s);
			vec[person].push_back(num);

		} catch (std::invalid_argument&) { }
 		
		person++;
	}

	return vec;
}

int main() {
	vector<vector<int>> men_prefs = read_file("testfiles/stable_match/men4.txt");
	vector<vector<int>> wom_prefs = read_file("testfiles/stable_match/women4.txt");
	stable_marriage(men_prefs,wom_prefs);
}