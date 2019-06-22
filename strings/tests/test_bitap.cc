#include "../bitap.cc"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string text = "hejej heee skaa fdfd ada dddd";
    string pattern = "heee skaa";

    string search = bitap_search(text, pattern);

    cout << search << endl;

    return 0; 
}