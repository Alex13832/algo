/** ------------------------------------------------------
* Boyer-Moore algorithm test.
* Alexander Karlson, 2015-07-21 
* -------------------------------------------------------- */
#include "../boyer_moore.cc"
#include <iostream>
#include <vector>
using namespace std;

int main() {

	//6 37 118 180 218 249 330 392, 8 times 
	string text = "Lorem cucumber ipsum dolor sit amet, cucumber vel modus "
	"alienum eu. Omnium oporteat definitiones cu mei. Has et solum cucumber vitae, viderer " 
	"delicata consectetuer est at. At nisl cucumber facete qui, eu oblique "
	"Lorem cucumber ipsum dolor sit amet, cucumber vel modus "
	"alienum eu. Omnium oporteat definitiones cu mei. Has et solum cucumber vitae, viderer " 
	"delicata consectetuer est at. At nisl cucumber facete qui, eu oblique ";

	string pattern = "cucumber";

	vector<int> matches = boyer_moore(text, pattern);
	for (auto m: matches)  {
		cout << m << " ";
	}
	cout << endl;
}