//
// Created by jf on 11/21/17.
//

#include "algorithm.h"


bool algorithm::deep_search(std::vector<CGraph::Graph> &tree, int source, int dest,std::vector<CGraph::Graph> &pth, int start_ind  ){
    int i,j;
    bool found;
    std::list<CGraph::Node> neighbord;
    for(i=0;tree[i].id!=source && i<tree.size();i++);
    if(tree[i].PassedOn){
        return false;
    }
    tree[i].PassedOn= false;
    found= false;
    neighbord=tree[i].nodes;
    for(auto it=neighbord.begin();it!=neighbord.end(),found!= true;it++){
        for(j=0;tree[j].id!=it->id && j<tree[i].nb_nodes;j++);
        if(tree[j].id==dest){
            found=true;
            pth[start_ind+1]=tree[j];
        }
        else{
            found=algorithm::deep_search(tree,tree[j].id,dest,pth,(start_ind+1));
        }
    }

    if(found){
        pth[start_ind]=tree[i];
    }
    tree[i].PassedOn=found;
}
/**
 *
 * @param tree
 * @param source
 * @param dest
 * @param pth
 * @param start_ind
 * @return
 */

bool algorithm::wide_search(std::vector<CGraph::Graph> &tree, int source, int dest,std::vector<CGraph::Graph> &pth){
    int i,j;
    bool found=false;
    std::vector<CGraph::Graph> working_queue;
    CGraph::Graph current;
    for (i = 0; tree[i].id != source && i < tree.size(); i++);
    tree[i].PassedOn = true;
    current=tree[i];

    while(!working_queue.empty() && !found) {
        if(!working_queue.empty()){
            current=working_queue.back();
            working_queue.pop_back();
        }
        for (i = 0; tree[i].id != current.id && i < tree.size(); i++);
        tree[i].PassedOn = true;
        for (auto it = tree[i].nodes.begin(); it != tree[i].nodes.end() && !found; it++) {
            for (j = 0; tree[j].id != it->id && j < tree.size(); j++);
            if (!tree[j].PassedOn) {
                tree[j].PassedOn = true;
                working_queue.push_back(tree[j]);
            }
            if(tree[j].id==dest){
                found=true;
            }
        }
    }
    pth=working_queue;
}

void algorithm::reset_visite(std::vector<CGraph::Graph> &tree){
    for(auto i=0;i<tree.size();i++)
        tree[i].PassedOn= false;
}

int algorithm::nodeToNodeValue(std::vector<CGraph::Graph> v, int id_from, int id_to){

	int retVal = -1;

	for (auto it = v.begin(); it != v.end(); it++) {
		if (it->id == id_from)
		{
			isIdInList(it->nodes,id_to);
		}
	}

	return retVal;
}


int algorithm::isIdInList(std::list<CGraph::Node> list, int id){

	int retVal = -1;

	for(auto it = list.begin(); it != list.end() && (retVal == -1) ; it++)
	{
		if(it->id == id)
		{
			retVal = it->value;
		}
	}

	return retVal;
}


bool algorithm::dijkstra_search(std::vector<CGraph::Graph> &tree, int source, int destination,std::vector<int> &pth){

	int N = tree.size();

	bool * Visited = new bool[N];
	int * D = new int[N];
	int * path = new int[N];
	int Nearest;
	int nNext;
	pth.clear();

	int nbVisited = 0;

	for (auto it = tree.begin(); it != tree.end(); it++) {
		if (it->id == source) {
			for(int i=0; i<N ; i++)
			{
				D[i] = isIdInList(it->nodes,i);
				pth.push_back(source);
				Visited[i] = false;
			}
		}
	}

	Visited[source] = true;
	nbVisited = 1;

	while(nbVisited < N)
	{
		for(int i = 0, nValue=0; i < N; i++)
		{
			if((nValue < D[i]) && (Visited[i]==false))
			{
				nValue = D[i];
			}
		}
		//TODO:complete this shiet
		/*Nearest = nValue;

		nbVisited++;
		for(auto it = tree.begin(); it!=tree.end(); it++)
		{
			if(it.)
		}*/
	}
}
















