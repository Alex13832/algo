/** ---------------------------------------------------------------------------
 Approximation algorithm for the travelling salesman problem.
 Alexander Karlsson 2016-09-24
---------------------------------------------------------------------------- */
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> nearest_neighbor(vector< vector< pair<int,int> > > G, size_t N, int start)
{
    int curr = start;
    vector<bool> visited(N,false);
    visited[curr] = true;

    /* Salesman's path */
    vector<int> path;
    path.push_back(curr);

    while (find(visited.begin(), visited.end(), false) != visited.end()) {
        int next;
        int min_w = INT32_MAX;
        cout << curr << " " ;
        cout << G[curr].size() << endl;
        for (size_t i = 0; i < G[curr].size(); i++) {
            /* Find closest neightbor */
            if (G[curr][i].second < min_w && visited[G[curr][i].first] == false) {
                next  = G[curr][i].first;
                min_w = G[curr][i].second;
            }
        }

        curr = next;
        visited[curr] = true;
        path.push_back(curr);
    }

    return path;
}
