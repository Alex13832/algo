/**-----------------------------------------------------------
* Test for load_balancing.cc 
* Alexander Karlsson 2015-07-09
* ------------------------------------------------------------ */
#include "../load_balancing.cc"
#include <iostream>
#include <vector>
#include <time.h>    
#include <ctime>   
#include <chrono>
#include <random>
using namespace std;


int myrandom (int i) { return std::rand()%i;}


int main() {
	size_t nbr_of_jobs, nbr_of_machines;

	cout << "Number of jobs: ";
	cin >> nbr_of_jobs;
	cout << "Number of machines: ";
	cin >> nbr_of_machines;

	std::srand ( unsigned ( std::time(0) ) );
	int k = 50;
	vector<int> jobs(nbr_of_jobs);

	for (size_t i = 0; i < nbr_of_jobs; ++i) {
		jobs[i] = myrandom(k);
	}

	vector<Machine> machines(nbr_of_machines);

	for (size_t j = 0; j < nbr_of_machines; ++j) {
		Machine m;
		machines[j] = m;
	}

	load_balancing(machines,jobs);

	cout << "Total workload per machine " << endl;
	for (size_t j = 0; j < machines.size(); ++j) {
		cout << machines[j].load << " " << endl;
	}

}