/** -----------------------------------------------------------
* Optimal scheduling implementation. Earliest deadline first. 
* Alexander Karlsson, 2015-06-27
* ------------------------------------------------------------- */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct job {
  long start, finish;
  string label; // Not compulsory
};

struct job_comp {
  bool operator()(const job j1, const job j2) const
  { return j1.finish < j2.finish; }
};

/* Optimal scheduling */
vector<job> edf(vector<job> jobs)
{
  vector<job> opt_jobs;
  sort(jobs.begin(), jobs.end(), job_comp());

  while (!jobs.empty()) {
    job jb = jobs[0];
    opt_jobs.push_back(jb);

    jobs.erase(remove_if(jobs.begin(), jobs.end(), [&](job &j) {
      return j.start < jb.finish;
    }), jobs.end());
  }

  return opt_jobs;
}