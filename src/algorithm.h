//
// Created by jf on 11/21/17.
//

#ifndef SAKJDHASDKJ_ALGORITHM_H
#define SAKJDHASDKJ_ALGORITHM_H

#include "graph.h"

using namespace std;

class algorithm {

private:
	CGraph graph;
public:
    bool deep_search(CGraph *tree, int source, int dest,std::vector<int> &pth, int start_ind );
    void reset_visite(std::vector<CGraph::Graph> &tree);
    bool wide_search(CGraph *tree, int source, int dest,std::vector<int> &pth);
    bool dijkstra_search(CGraph *tree, int source, int destination,std::vector<int> &pth);
    bool floyd_warshal_search(CGraph *tree, int source, int destination,std::vector<int> &pth);
};


#endif //SAKJDHASDKJ_ALGORITHM_H
