/** ------------------------------------------------------------------
* A few lines of code to produce the crossword dictionary.
* Alexander Karlson, begun 2015-08-15
* -------------------------------------------------------------------- */
#include "../crossword_dict.cc"


int main(int argc, char *argv[]) { 
	cout << argv[1] << " " << argv[2] << endl;
	cout << argc << endl;
	if(argc == 3) {	
		process_dictionary_file(argv[1],argv[2]);
	}
}
