/** ---------------------------------------------------------------------------
 Test for minimax algorithm.
 Alexander Karlsson 2016-09-25
----------------------------------------------------------------------------- */
#include "../minimax.cc"
#include <iostream>
#include <vector>

using namespace std;

Node makeNode(int weight)
{
    Node n = {weight};
    return n;
}

int main() {

    Node n0 = makeNode(0);
    Node n1 = makeNode(0);
    Node n2 = makeNode(0);
    Node n3 = makeNode(0);
    Node n4 = makeNode(0);
    Node n5 = makeNode(0);
    Node n6 = makeNode(0);
    Node n7 = makeNode(0);
    Node n8 = makeNode(0);
    Node n9 = makeNode(0);
    Node n10 = makeNode(-1);
    Node n11 = makeNode(0);
    Node n12 = makeNode(1);
    Node n13 = makeNode(-1);
    Node n14 = makeNode(-1);
    Node n15 = makeNode(-1);
    Node n16 = makeNode(-1);
    Node n17 = makeNode(-1);
    Node n18 = makeNode(1);
    Node n19 = makeNode(-1);
    Node n20 = makeNode(-1);

    n4.children.push_back(n9);
    n4.children.push_back(n10);

    n5.children.push_back(n11);
    n5.children.push_back(n12);

    n6.children.push_back(n13);
    n6.children.push_back(n14);

    n7.children.push_back(n15);
    n7.children.push_back(n16);
    n7.children.push_back(n17);

    n8.children.push_back(n18);
    n8.children.push_back(n19);
    n8.children.push_back(n20);

    n1.children.push_back(n4);
    n1.children.push_back(n5);
    n2.children.push_back(n6);
    n3.children.push_back(n7);
    n3.children.push_back(n8);

    n0.children.push_back(n1);
    n0.children.push_back(n2);
    n0.children.push_back(n3);

    int val = minimax(n0, 3, true);


    cout << val << endl; // 0
    cout << n0.weight << endl;

    return 0;
}
