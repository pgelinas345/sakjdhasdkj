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













