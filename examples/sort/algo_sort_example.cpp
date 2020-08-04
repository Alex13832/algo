///
/// \brief Example source code for sort example.
/// \author alex011235
/// \date 2020-06-20
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "algo.hpp"

using namespace std;

// function generator:
int RandomNumber() { return (std::rand() % 100); }

int main()
{
  chrono::steady_clock::time_point begin, end;

  srand(unsigned(std::time(nullptr)));
  vector<int> rands(5000);
  generate(rands.begin(), rands.end(), RandomNumber);

  // Bubble sort ///////////////////////////////
  vector<int> rands_cp = rands;
  begin = chrono::steady_clock::now();
  algo::sort::Bubble(rands_cp);
  end = chrono::steady_clock::now();
  cout << "Bubble sort time duration sorting = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() / 1000.0 << " [ms]" << endl;

  // Bucket sort ///////////////////////////////
  rands_cp = rands;
  begin = chrono::steady_clock::now();
  algo::sort::Bucket(rands_cp);
  end = chrono::steady_clock::now();
  cout << "Bucket sort time duration sorting = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() / 1000.0 << " [ms]" << endl;

  // Gnome sort ////////////////////////////////
  rands_cp = rands;
  begin = chrono::steady_clock::now();
  algo::sort::Gnome(rands_cp);
  end = chrono::steady_clock::now();
  cout << "Gnome sort time duration sorting = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() / 1000.0 << " [ms]" << endl;

  // Heap sort /////////////////////////////////
  rands_cp = rands;
  begin = chrono::steady_clock::now();
  algo::sort::Heap(rands_cp);
  end = chrono::steady_clock::now();
  cout << "Heap sort time duration sorting = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() / 1000.0 << " [ms]" << endl;

  // Insertion sort ////////////////////////////
  rands_cp = rands;
  begin = chrono::steady_clock::now();
  algo::sort::Insertion(rands_cp);
  end = chrono::steady_clock::now();
  cout << "Insertion sort time duration sorting = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() / 1000.0 << " [ms]" << endl;

  // Merge sort ////////////////////////////////
  rands_cp = rands;
  begin = chrono::steady_clock::now();
  algo::sort::Merge(rands_cp);
  end = chrono::steady_clock::now();
  cout << "Merge sort time duration sorting = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() / 1000.0 << " [ms]" << endl;

  // Quick sort ////////////////////////////////
  rands_cp = rands;
  begin = chrono::steady_clock::now();
  algo::sort::Quick(rands_cp);
  end = chrono::steady_clock::now();
  cout << "Quick sort time duration sorting = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() / 1000.0 << " [ms]" << endl;

  return 0;
}