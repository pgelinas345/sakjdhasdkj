/*
 * graphe.h
 *
 *  Created on: Nov 20, 2017
 *      Author: phil
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <vector>

#define MAX_NUMBER_OF_NODES 0x7FFF
#define MIN_NUMBER_OF_NODES 3
#define MAX_NUMBER_OF_EDGES(x) (x-1)
#define MIN_NUMBER_OF_EDGES 2
#define	MIN_EDGES_VALUE		1
#define MAX_EDGES_VALUE		0x7FFF


using namespace std;



class CGraph
{
public:

	struct Node{
		int id;
		int value;

		Node(int _id, int _value):
		id(_id),
		value(_value)
		{
		}
	};

	struct Graph{
		int id;
		int nb_nodes;
		bool PassedOn;
		std::list<Node> nodes;
	};


	int N;

	std::vector<Graph> graph;
	int **AdjMatrix;

	CGraph();
	~CGraph();

	int saveToFile(const char * file_name);
	void displayNodes(void);
	int countViewedNodes(void);
	void resetVisited(void);
	void displayViewedNodes(void);
	void displayPath(std::vector<int> v);
	int countSolutionCost(std::vector<int> v);
	void addEdges(std::vector<Graph> &tree,int idSrc, int idDst, int Value);
	int nodeToNodeValue(std::vector<Graph> v, int id_from, int id_to);
	int isIdInList(std::list<CGraph::Node> list, int id);

private:

	int ** ReadFromFile(char * file_name);
	int ** Generate(int minL, int maxL, int minP, int maxP);

	bool isEdgeVisited(std::vector<Graph> v, int id);
	bool isEdgeInList(std::list<Node> l, int id);
	void CreateFromMatrice(int ** L);
};

#endif /* GRAPH_H_ */
