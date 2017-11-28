//
// Created by jf on 11/21/17.
//

#include "algorithm.h"

#define ADDITION_INF(x,y) ((x+y) > 0x7FFF) ? 0x7FFF: (x+y)


bool algorithm::deep_search(CGraph *tree, int source, int dest,std::vector<int> &pth, int start_ind  ){
    int i,j;
    bool found;
    std::list<CGraph::Node> neighbord;
    std::vector<CGraph::Graph> graph=tree->graph;
    
    for(i=0;graph[i].id!=source && i<graph.size();i++);
    if(graph[i].PassedOn){
        return false;
    }
    graph[i].PassedOn= false;
    found= false;
    neighbord=graph[i].nodes;
    for(auto it=neighbord.begin();it!=neighbord.end(),found!= true;it++){
        for(j=0;graph[j].id!=it->id && j<graph[i].nb_nodes;j++);
        if(graph[j].id==dest){
            found=true;
            pth[start_ind+1]=graph[j].id;
        }
        else{
            found=algorithm::deep_search(tree,graph[j].id,dest,pth,(start_ind+1));
        }
    }

    if(found){
        pth[start_ind]=graph[i].id;
    }
    graph[i].PassedOn=found;
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
    int i,j;
    bool found=false;
    std::vector<CGraph::Graph> working_queue;
    std::vector<CGraph::Graph> graph=tree->graph;
    CGraph::Graph current;
    for (i = 0; graph[i].id != source && i < graph.size(); i++);
    graph[i].PassedOn = true;
    current=graph[i];

    while(!working_queue.empty() && !found) {
        if(!working_queue.empty()){
            current=working_queue.back();
            working_queue.pop_back();
        }
        for (i = 0; graph[i].id != current.id && i < graph.size(); i++);
        graph[i].PassedOn = true;
        for (auto it = graph[i].nodes.begin(); it != graph[i].nodes.end() && !found; it++) {
            for (j = 0; graph[j].id != it->id && j < graph.size(); j++);
            if (!graph[j].PassedOn) {
                graph[j].PassedOn = true;
                working_queue.push_back(graph[j]);
            }
            if(graph[j].id==dest){
                found=true;
            }
        }
    }
    for(auto it=working_queue.begin();it<working_queue.end();it++){
        pth.push_back(it->id);
    }

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

	bool found = false;

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


	for(int nbVisited = 0; nbVisited < N && found==false; nbVisited++)
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

		if(nNearest == destination)
		{
			found = true;
			pth.insert(pth.begin(),destination);
			nNext = destination;
			do
			{
				nNext = from[nNext];
				pth.insert(pth.begin(),nNext);

			}while(nNext != source);
		}

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



	return true;
}


bool algorithm::floyd_warshal_search(CGraph *tree, int source, int destination,std::vector<int> &pth){

	int N = tree->N;

	int ** D = new int*[N];
	int ** path = new int*[N];
	int n2nValue = 0;

	for(int i = 0; i<N; i++)
	{
		D[i] = new int[N];
		path[i] = new int[N];
	}

	for(int i = 0; i<N ; i++)
	{
		for(int j = 0; j<N; j++)
		{
			n2nValue = tree->nodeToNodeValue(tree->graph,i,j);
			D[i][j] = n2nValue;
			path[i][j] = -1;
		}
	}

	for(int k = 0; k<N; k++)
	{
		for(int i = 0; i<N ; i++)
		{
			for(int j = 0; j<N; j++)
			{
				if(D[i][j] > ADDITION_INF(D[i][k],D[k][i]))
				{
					D[i][j] = ADDITION_INF(D[i][k],D[k][i]);
					path[i][j] = k;
				}

			}
		}
	}

	printf("\n");

	for(int i = 0; i<N ; i++)
	{
		printf("\n");
		for(int j = 0; j<N; j++)
		{
			printf("%d\t",D[i][j]);
		}
	}



}












