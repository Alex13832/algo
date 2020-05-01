#include <stdio.h>
#include "graph.c"

int main(int argc, char const *argv[]) {

      graph *g = malloc(sizeof(graph));

      read_graph(g, true);
      print_graph(g);

      return 0;
}
