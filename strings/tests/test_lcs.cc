#include "../longest_common_substr.cc"
#include <string>
#include <iostream>
using namespace std;


int main() {
	string A("otirpporeijgpowergjeågjeopnpoqerhgnopqkruskaldijkstrassdadsdadar");
	string B("iuthewriuthkruskaldijkstrabueqbfuiqgfuqygfnvkjdfbiehf5d");

	string C = longest_common_substr(A,B);
	cout << C << endl;
}