/**
 --------------------------------------------------
 Project: cp264-a10q3
 File:    graph.c
 Author:  Manik sehgal
 Version: 2023-04-07
 --------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue_stack.h"
#include "graph.h"

GRAPH* new_graph(int order) {
	GRAPH *p = malloc(sizeof(GRAPH));
	p->order = order;
	p->size = 0;
	p->nodes = malloc(order * sizeof(GNODE*)); // create array of GNODE pointers
	int i;
	for (i = 0; i < order; i++) {
		p->nodes[i] = malloc(sizeof(GNODE)); // create a GNOGE object
		p->nodes[i]->nid = i; // set node id to be 
		p->nodes[i]->neighbor = NULL; // Initialize neighbor linked list
	}
	return p;
}

void add_edge(GRAPH *g, int from, int to, int weight) {
	if (g == NULL || from < 0 || from >= g->order || to < 0 || to >= g->order) {

		return;
	}
	ADJNODE *n = malloc(sizeof(ADJNODE));
	n->nid = to;
	n->weight = weight;
	n->next = NULL;

	// finding the from node
	int i;
	for (i = 0; i < g->order; i++) {
		if (g->nodes[i]->nid == from) {
			ADJNODE *p = g->nodes[i]->neighbor;
			if (p == NULL) {
				g->nodes[i]->neighbor = n;
			} else {
				while (p->next != NULL) {
					p = p->next;
				}
				p->next = n;
			}
			break;
		}
	}

	if (i == g->order) {
		free(n);
	}

	g->size++;
}

int get_weight(GRAPH *g, int from, int to) {
	if (g == NULL || from < 0 || from >= g->order || to < 0 || to >= g->order) {
		return INFINITY;
	}

	ADJNODE *np = g->nodes[from]->neighbor;

	while (np != NULL) {

		if (np->nid == to) {
			return np->weight;
		}
		np = np->next;
	}

	return INFINITY;
}

void clean_graph(GRAPH **gp) {
	GRAPH *g = *gp;
	if (gp != NULL && *gp != NULL) {
		for (int i = 0; i < g->order; i++) {
			ADJNODE *p = g->nodes[i]->neighbor;
			while (p != NULL) {
				ADJNODE *tmp = p;
				p = p->next;
				free(tmp);
			}
			free(g->nodes[i]);
		}
		free(g->nodes);
		free(g);
		*gp = NULL;
	}
}

void display_bforder(GRAPH *g, int start) {
	if (g == NULL)
		return;
	int n = g->order, visited[n], i;

	for (i = 0; i < n; i++)
		visited[i] = 0;

	//bread-first traversal algorithm

	QUEUE q = { 0 };
	GNODE *gnp = NULL;
	ADJNODE *anp = NULL;

	enqueue(&q, g->nodes[start]);
	visited[start] = 1;

	while (q.front) {
		gnp = (GNODE*) dequeue(&q);
		printf("%d ", gnp->nid); // pattern and action on node
		anp = gnp->neighbor;

		while (anp) {
			if (!visited[anp->nid]) {

				visited[anp->nid] = 1;
				enqueue(&q, g->nodes[anp->nid]);
			}
			anp = anp->next;
		}
	}
	clean_queue(&q);
}

void display_dforder(GRAPH *g, int start) {
	if (g == NULL)
		return;
	int n = g->order, visited[n], i;

	for (i = 0; i < n; i++)
		visited[i] = 0;

	// depth-first traversal algorithm

	STACK s = { 0 };
	GNODE *gnp = NULL;
	ADJNODE *anp = NULL;

	push(&s, g->nodes[start]);
	visited[start] = 1;

	while (s.top) {
		gnp = (GNODE*) pop(&s);
		printf("%d ", gnp->nid); // pattern and action on node
		anp = gnp->neighbor;
		while (anp) {
			if (!visited[anp->nid]) {
				visited[anp->nid] = 1;
				push(&s, g->nodes[anp->nid]);
			}
			anp = anp->next;
		}
	}
	clean_stack(&s);
}

void display_graph(GRAPH *g) {
	if (g == NULL)
		return;
	printf("order:%d\n", g->order);
	printf("size:%d\n", g->size);
	printf("from:(to weight)");
	int i;
	ADJNODE *ptr;
	for (i = 0; i < g->order; i++) {
		printf("\n%d:", g->nodes[i]->nid);
		ptr = g->nodes[i]->neighbor;
		while (ptr != NULL) {
			printf("(%d %d) ", ptr->nid, ptr->weight);
			ptr = ptr->next;
		}
	}
}

