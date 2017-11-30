//
// Created by jf on 11/21/17.
//

#include "algorithm.h"


bool algorithm::deep_search(std::vector<CGraph::Graph> &tree, int source, int dest,std::vector<int> &pth){
    int i=0,j=0;
    bool found=false;
    if(tree[source].PassedOn){
        return false;
    }
    tree[source].PassedOn= true;
    pth.push_back(source);
    for(auto it=tree[source].nodes.begin();it!=tree[source].nodes.end(),!found;it++){
        if(it->id==dest){
            found=true;
            tree[it->id].PassedOn=true;
            pth.push_back(it->id);
        }
        if(tree[it->id].PassedOn){
            continue;
        }
        else{
            found=deep_search(tree,it->id,dest,pth);
        }
    }
    return found;
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

bool algorithm::wide_search(CGraph *tree, int source, int dest,std::vector<int> &pth){
    int i,current_objective=source;
    bool found=false;
    std::list<int> child;
    child.clear();
    pth.push_back(source);
    tree->graph[current_objective].PassedOn=true;
    do {

        if (!child.empty()) {
            current_objective = child.front();
            child.pop_front();

        }
        for (auto it = tree->graph[current_objective].nodes.begin();
             it != tree->graph[current_objective].nodes.end() && !found; it++) {
            if (it->id == dest) {
                tree->graph[it->id].PassedOn = true;
                pth.push_back(it->id);
                found = true;
            } else if (tree->graph[it->id].PassedOn) {
                continue;
            } else {
                child.push_back(it->id);
                tree->graph[it->id].PassedOn=true;
                pth.push_back(it->id);
            }
        }
    }while(!found && !child.empty());


    return found;
}






bool algorithm::dijkstra_search(CGraph *tree , int source, int destination,std::vector<int> &pth){

	int N = tree->graph.size();

	std::vector<int> D;
	std::vector<int> from;
	std::vector<bool> Visited;
	D.resize(N);
	from.resize(N);
	Visited.resize(N);

	int nValue = 0;
	int nNearest = 0;
	int nNext = 0;

	pth.clear();

	int n2nValue = 0;

	for (int i=0; i<N; i++){

		D[i] = 0x7FFF;
		from[i]=source;
		Visited[i] = false;

		if(i==source)
		{
			D[i] = 0;
		}
	}


	for(int nbVisited = 0; nbVisited < N; nbVisited++)
	{
		nValue = 0x7FFF;

		for(int i = 0; i<N; i++)
		{
			if(D[i] < nValue && Visited[i]==false)
			{
				nValue = D[i];
				nNearest = i;
			}
		}

		Visited[nNearest] = true;


		for(auto it = tree->graph.begin(); it!=tree->graph.end() ; it++)
		{
			if(it->id == nNearest)
			{
				it->PassedOn=true;
				for(auto itl=it->nodes.begin() ; itl!=it->nodes.end() ; itl++)
				{
					n2nValue = tree->nodeToNodeValue(tree->graph,nNearest,itl->id);

					if(D[itl->id] > n2nValue + D[nNearest])
					{
						D[itl->id] = n2nValue + D[nNearest];
						from[itl->id] = nNearest;
					}

				}
				break;
			}
		}
	}

	pth.insert(pth.begin(),destination);
	nNext = destination;
	do
	{
		nNext = from[nNext];
		pth.insert(pth.begin(),nNext);

	}while(nNext != source);

	return true;
}













