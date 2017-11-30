//
// Created by jf on 11/21/17.
//

#include "algorithm.h"

#define ADDITION_INF(x,y) (((unsigned int)(x+y)) > 0x7FFF) ? 0x7FFF : (x+y)
#define SAME_NODE_CHECK(x,y,z) (x==y) ? 0 : z
#define INF_CHECK(x)	(x == (-1)) ? 0x7FFF : x

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
    int i=0,current_objective=source, parent;
    bool found=false;
    std::list<int> child;
    std::vector<int> x;;
    x.resize(tree->N);
    std::fill(x.begin(), x.end(), -1);
    child.clear();
    tree->graph[current_objective].PassedOn=true;
    tree->graph[current_objective].Distance=0;
    do {

        if (!child.empty()) {
            current_objective = child.front();
            child.pop_front();


        }
        for (auto it = tree->graph[current_objective].nodes.begin();
             it != tree->graph[current_objective].nodes.end(); it++) {
            if (it->id == dest) {
                if(tree->graph[it->id].Distance<0){
                    tree->graph[it->id].Distance=tree->graph[current_objective].Distance+1;
                    pth.resize(tree->graph[it->id].Distance+1);//afin dajouter le noeud de depart
                    cout<<"chemin plus court trouver"<<tree->graph[current_objective].Distance+1<<'\n';
                    cout<<"Courant :"<<it->id<<" Parent:"<<current_objective<<'\n';
                    x[dest]=current_objective;
                    parent=dest;
                    pth[tree->graph[it->id].Distance]=it->id;
                    pth[0]=source;
                    for(i=1;i<(tree->graph[it->id].Distance);i++){
                        pth[tree->graph[it->id].Distance-i]=x[parent];
                        parent=x[parent];
                    }
                }
                else if(tree->graph[it->id].Distance>tree->graph[current_objective].Distance+1){
                    cout<<"chemin plus court trouver"<<tree->graph[current_objective].Distance+1<<'\n';
                }
                found =true;

            } else if (tree->graph[it->id].PassedOn) {
                continue;
            } else {
                child.push_back(it->id);
                tree->graph[it->id].PassedOn=true;
                if(x[it->id]=-1){
                    x[it->id]=current_objective;
                    tree->graph[it->id].Distance=tree->graph[current_objective].Distance+1;
                }

            }
        }
    }while(!child.empty());


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
			pth.insert(pth.begin(),destination);
			nNext = destination;
			do
			{
				nNext = from[nNext];
				pth.insert(pth.begin(),nNext);

			}while(nNext != source);
			found = true;
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

	return found;
}


bool algorithm::floyd_warshal_search(CGraph *tree, int source, int destination,std::vector<int> &pth){

	int N = tree->N;

	int ** D = new int*[N];
	int ** path = new int*[N];
	int n2nValue = 0;
	unsigned int check;

	int u = source;
	int v = destination;

	for(int i = 0; i<N; i++)
	{
		D[i] = new int[N];
		path[i] = new int[N];
	}

	for(int i = 0; i<N ; i++)
	{
		for(int j = 0; j<N; j++)
		{
			n2nValue = SAME_NODE_CHECK(i,j,tree->nodeToNodeValue(tree->graph,i,j));

			n2nValue = INF_CHECK(n2nValue);
			D[i][j] = n2nValue;
			path[i][j] = j;
		}
	}

	for(int i = 0; i<N ; i++)
	{
		printf("\n");
		for(int j = 0; j<N; j++)
		{
			printf("%d\t",D[i][j]);
		}
	}

	for(int k = 0; k<N; k++)
	{
		for(int i = 0; i<N ; i++)
		{
			for(int j = 0; j<N; j++)
			{
				check = ADDITION_INF(D[i][k],D[k][j]);

				if(D[i][j] > (int)check)
				{
					D[i][j] = check;
					path[i][j] = path[i][k];
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

	printf("\n");

	for(int i = 0; i<N ; i++)
	{
		printf("\n");
		for(int j = 0; j<N; j++)
		{
			printf("%d\t",path[i][j]);
		}
	}

	pth.clear();
	pth.push_back(u);
	do
	{
		u = path[u][v];
		pth.push_back(u);

	}while(u != v);


 }










