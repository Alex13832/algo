/** ---------------------------------------------------------------------------
 Test for travelling salesman's approximation algorithm.
 Alexander Karlsson 2016-09-24
----------------------------------------------------------------------------- */
#include <vector>
#include "../travelling_salesman.cc"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    // Graph
    vector<vector<pair<int,int>>> adj(5);

    adj[0].push_back(make_pair(1, 70));
    adj[1].push_back(make_pair(0, 70));

    adj[0].push_back(make_pair(2, 35));
    adj[2].push_back(make_pair(0, 35));

    adj[0].push_back(make_pair(3, 40));
    adj[3].push_back(make_pair(0, 40));

    adj[0].push_back(make_pair(4, 60));
    adj[4].push_back(make_pair(0, 60));

    adj[1].push_back(make_pair(3, 40));
    adj[3].push_back(make_pair(1, 40));

    adj[1].push_back(make_pair(2, 25));
    adj[2].push_back(make_pair(1, 25));

    adj[1].push_back(make_pair(4, 50));
    adj[4].push_back(make_pair(1, 50));

    adj[2].push_back(make_pair(3, 10));
    adj[3].push_back(make_pair(2, 10));

    adj[2].push_back(make_pair(4, 12));
    adj[4].push_back(make_pair(2, 12));

    adj[3].push_back(make_pair(4, 15));
    adj[4].push_back(make_pair(3, 15));

    // Start node (4) may have an impact on the total travelling distance.
    vector<int> path = nearest_neighbor(adj, 5, 4);

    for (auto p: path)
        cout << p << endl;

    return 0;
}
