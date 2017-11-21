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

#define MAX_DECIMAL_INT_LENGHT 5


using namespace std;



class CGraph
{
private:

	int ** ReadFromFile(char * file_name);
	int ** Generate(int minL, int maxL, int minP, int maxP);

	void CreateFromMatrice(int ** L);

public:

	struct Node{
		int id;
		int value;

		Node(int _id, int _value) :
		id(_id),
		value(_value)
		{
		}
	};

	struct Graph{
		int id;
		int nb_nodes;
		std::list<Node> nodes;
	};
	int N;

	std::vector<Graph> graph;

	CGraph();
	~CGraph();

};

#endif /* GRAPH_H_ */
