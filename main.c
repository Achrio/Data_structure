#include <stdio.h>
#include "list_graph.h"

int main() {
	List_Graph g;
	
	graph_init(&g);

	insert_vertex(&g, 0);
	insert_vertex(&g, 1);
	insert_vertex(&g, 2);
	insert_vertex(&g, 3);
	insert_vertex(&g, 4);

	insert_edge(&g, 0, 1);
	insert_edge(&g, 1, 0);
	insert_edge(&g, 0, 2);
	insert_edge(&g, 2, 0);
	insert_edge(&g, 0, 4);
	insert_edge(&g, 4, 0);
	insert_edge(&g, 1, 2);
	insert_edge(&g, 2, 1);
	insert_edge(&g, 2, 4);
	insert_edge(&g, 4, 2);
	insert_edge(&g, 3, 4);
	insert_edge(&g, 4, 3);

	bfs_list(&g, 0);
}