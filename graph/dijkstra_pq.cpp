// Dijkstra with priority queue implementation
// Use graph.cpp as graph data structure not graph.cc
// Alexander Karlsson 2016-02-27

#define UINT_MAX 4294967295U

// Comparator
struct comp_dijkstra {
  bool operator() (const pair<uint,uint>& lhs, const pair<uint,uint>& rhs) const
  {return lhs.second>rhs.second;}
};

// Dijkstra algorithm
vector<uint> dijkstra_pq(vector<vector<pair<int, int> >> G, const int s)
{
  priority_queue<pair<uint,uint>, vector<pair<uint,uint>>,comp_dijkstra> pq;

  vector<uint> dist(G.size(),UINT_MAX);
  vector<int> prev(G.size(),0);

  dist[s] = 0;
  pq.push(pair<uint,uint>(s,0));

  while (!pq.empty()) {
    pair<uint,uint> U = pq.top();
    pq.pop();
    uint u = U.first;

    for (auto v: G[u]) {
        uint alt = dist[u] + v.second;

        if (alt < dist[v.first]) {
          dist[v.first] = alt;
          prev[v.first] = u;
          pq.push(pair<int,int>(v.first,alt));
        }
      }
  }

  return dist;
}
