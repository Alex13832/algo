/** -------------------------------------------------------------------
* Load balancing problem. Distribute a set of jobs on a set 
* of machines. Implemented with help of [Kleinberg,
* Tardos; Algorithm Design].
* Alexander Karlsson, 2015-07-08
* --------------------------------------------------------------------- */
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Machine {
	int load = 0;		// Load on Machine M_i
	vector<int> jobs; 	// Assigned jobs to machine M_i
};

void load_balancing(vector<Machine>& machines, vector<int> jobs) {
	size_t n = jobs.size();

	for (size_t j = 0; j < n; ++j) {

		int min_load = INT_MAX, mi = 0;;
		for (size_t i = 0; i < machines.size(); i++) {
			if (machines[i].load < min_load) {
				mi = i;
				min_load = machines[i].load;
			}
		}

		Machine & Mi = machines[mi];
		Mi.jobs.push_back(jobs[j]);
		Mi.load  += jobs[j];
	}
}