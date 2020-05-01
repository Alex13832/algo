// Graph data structure
// Credit to Steven S. Skiena

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXV 1000 // Max vertices

typedef struct {
      int y, weight;                // adjacency info and weight
      struct edgenode *next;
} edgenode;

typedef struct {
      edgenode *edges[MAXV+1];      // Adjacy info
      int degree[MAXV+1];           // outdegree of each vertex
      int nvertices;                // number of vertices in the graph
      int nedges;                   // number of edges in the graph
      bool directed;
} graph;

void initialize_graph(graph *g, bool directed)
{
      g->nvertices = 0;
      g->nedges = 0;
      g->directed = directed;

      int i;
      for (i = 1; i <= MAXV; i++) g->degree[i] = 0;
      for (i = 1; i <= MAXV; i++) g->edges[i] = NULL;
}

// Insert an edge between x and y
void insert_edge(graph *g, int x, int y, bool directed)
{
      edgenode *p;
      p = malloc(sizeof(edgenode));
      p->weight = 0;
      p->y = y;
      p->next = g->edges[x];

      g->edges[x] = p;              // insert at head of list
      g->degree[x]++;

      if (directed == false)
            insert_edge(g, y, x, true);
      else g->nedges++;
}

// Make a new graph with n vertices and m edges
// Reads the graph from a file
void read_graph(graph *g, bool directed)
{
      int i, m, x, y;               // counter, #edges, vertices in edge (x,y)

      initialize_graph(g, directed);

      scanf("%d %d",&(g->nvertices), &m);

      for (i = 1; i <= m; i++) {
            scanf("%d %d", &x, &y);
            insert_edge(g, x, y, directed);
      }
}

//Prints the graph g
void print_graph(graph *g)
{
      int i;
      edgenode *p;

      for (i = 0; i <= g->nvertices; i++) {
            printf("%d: ", i);
            p = g->edges[i];
            while (p != NULL) {
                  printf(" %d", p->y);
                  p = p->next;
            }
            printf("\n");
      }
}
