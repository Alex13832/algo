/** ------------------------------------------------------------
* Main file.
* Alexander Karlsson, begun 2015-08-07
* -------------------------------------------------------------- */
#include "spell_checker.cc"
#include <iostream>

using namespace std;

void print_usage()
{
  cout << "<in_filename.txt> <out_filename.txt> <language> " << endl;
  cout << "Supported languages: [English <eng> (default), Spanish <esp>, Swedish <swe>] " << endl;
}

int main(int argc, char *argv[])
{
  string infile, lang, outfile;

  if (argc == 4) {

    infile = argv[1];
    outfile = argv[2];
    lang = argv[3];
  } else if (argc == 3) {

    infile = argv[1];
    outfile = argv[2];
    lang = "eng";
  } else {

    print_usage();
    exit(EXIT_FAILURE);
  }

  SpellChecker sp(infile, outfile, lang);
  sp.spellCheck();
}