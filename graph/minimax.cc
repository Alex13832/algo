/** ---------------------------------------------------------------------------
 Minimax algorithm.
 Alexander Karlsson 2016-09-25
----------------------------------------------------------------------------- */
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef struct Node {
    int weight;
    vector<Node> children;
} Node;

/**
 Minimax algorithm.
 @param[in] N, Root node.
 @param[in] depth, number of layers in tree.
 @param[in] maximizingPlayer, if layer is maximizing or minimizing.
*/
int minimax(Node N, int depth, bool maximizingPlayer)
{
    if (depth == 0 || N.children.size() == 0)
        return N.weight;

    if (maximizingPlayer) {
        int bestValue = INT32_MIN;

        for (Node Nx: N.children) {
            int v = minimax(Nx, depth-1, false);
            bestValue = max(bestValue, v);
        }
        N.weight = bestValue;
        return bestValue;

    } else {
        int bestValue = INT32_MAX;

        for (Node Nx: N.children) {
            int v = minimax(Nx, depth-1, true);
            bestValue = min(bestValue, v);
        }
        N.weight = bestValue;
        return bestValue;
    }

    return 0;
}
