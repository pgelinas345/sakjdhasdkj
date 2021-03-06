/*
 * graphe.cpp
 *
 *  Created on: Nov 20, 2017
 *      Author: phil
 */

#include "graph.h"
#include <time.h>
#include <string.h>
#include <string>

//#define test
//#define JF
CGraph::CGraph(){
	this->N=0;
	this->graph.resize(this->N);
}

bool CGraph::createNewGraph(void){
	char user;
	int ** L = NULL;
	int minL=0,maxL=0,minP=0,maxP=0;
	std::string file_name;

#ifndef test
	cout << "\nChoose how to create graph: ";
	cout << "\n1.Create from file.";
    cout << "\n2.Generate randomly.";
    cout << "\n=>";
    cin >> user;



    if(user == '1')
    {
    	while(L == NULL)
    	{
			cout << "\nEnter valid path:";
			cout << "\n=>";
			cin >> file_name;


            L = ReadFromFile((char *)file_name.data());

			if(L == NULL) printf("\nFile not found!");
    	}
    }
    else
    {

    	while((this->N<MIN_NUMBER_OF_NODES) || (this->N>MAX_NUMBER_OF_NODES))
    	{
			cout << "\nEnter valid number of nodes:";
			cout << "\n=>";
			cin >> this->N;
			if((this->N<MIN_NUMBER_OF_NODES) || (this->N>MAX_NUMBER_OF_NODES))
			{
				cout << "\nEntered value is not valid!";
			}
    	}
    	while(minL < MIN_NUMBER_OF_EDGES || minL>MAX_NUMBER_OF_EDGES(this->N))
    	{
    		cout << "\nEnter valid ";
    		printf("minimum number of edges (min=%d):",MIN_NUMBER_OF_EDGES);
			cout << "\n=>";
			cin >> minL;
			if(minL < MIN_NUMBER_OF_EDGES)
			{
				cout << "\nEntered value is not valid!";
			}
    	}
    	while(maxL > MAX_NUMBER_OF_EDGES(this->N) || maxL < minL)
    	{
    		cout << "\nEnter valid ";
    		cout << "maximum number of edges (max=%d):" << MAX_NUMBER_OF_EDGES(this->N);
			cout << "\n=>";
			cin >> maxL;
			if(maxL > MAX_NUMBER_OF_EDGES(this->N) || maxL < minL)
			{
				cout << "\nEntered value is not valid!";
			}
    	}
    	while(minP < MIN_EDGES_VALUE || minP > MAX_EDGES_VALUE)
    	{
    		cout << "\nEnter valid ";
    		cout << "minimum edges value(min=%d):" << MIN_EDGES_VALUE;
			cout << "\n=>";
			cin >> minP;
			if(minP < MIN_EDGES_VALUE)
			{
				cout << "\nEntered value is not valid!";
			}
    	}
    	while(maxP > MAX_EDGES_VALUE || maxP < minP)
    	{
    		cout << "\nEnter valid ";
    		cout << "maximum edges value (max=%d):" << MAX_EDGES_VALUE;
			cout << "\n=>";
			cin >> maxP;
			if(maxP > MAX_EDGES_VALUE)
			{
				cout << "\nEntered value is not valid!";
			}
    	}

    	L = Generate(minL,maxL,minP,maxP);
    }
#endif
#ifdef JF
	L = ReadFromFile("./src/jf.txt");

	if(L == NULL) printf("\nFile not found!");
#endif
#ifndef JF
#ifdef test
    L = ReadFromFile("./src/test.txt");

	if(L == NULL) printf("\nFile not found!");
#endif
#endif

    CreateFromMatrice(L);

    return true;

}


CGraph::~CGraph(void){

	for(auto it = this->graph.begin();it!=this->graph.end();it++)
	{
		it->nodes.clear();
	}

	this->graph.clear();
}

/**
 *
 * @param file_name
 * @return
 */
int ** CGraph::ReadFromFile(char * file_name){

    char *p;
    int ** L;
    char line[1024];
    FILE *file;
    int i, j;

    file = fopen(file_name, "r");

    if (file == 0){
        //fopen returns 0, the NULL pointer, on failure
        perror("Canot open input file\n");
        return NULL;
    }
    else{

    	fgets(line, 1024, file);

    	p = strtok(line, "\t");

    	this->N = atoi(p);

    	L = (int**) malloc(sizeof(int*) * this->N);

    	for (i=0; i<N; i++){
            L[i] = (int *) malloc(sizeof(int) * this->N);
        }

    	i = 0;



        while ((fgets(line, 1024, file)) != NULL ){

        	j=0;

        	p = strtok(line, "\t");

            while(p!=NULL){

            	L[i][j] = atoi(p);

            	p = strtok(NULL, "\t");

            	j++;
            }

            i++;
        }
    }

    return L;
}

void CGraph::CreateFromMatrice(int ** L){

	this->graph.resize(this->N);


	for(int i=0; i<this->N; i++)
	{
		this->graph[i].id = i;
		this->graph[i].nb_nodes = 0;
		this->graph[i].PassedOn = false;
        this->graph[i].Distance = -1;
		for(int j=0; j<this->N; j++)
		{
			if(L[i][j] > 0)
			{
				this->graph[i].nodes.push_back(Node(j,L[i][j]));
				this->graph[i].nb_nodes++;
			}
		}
	}
}

int ** CGraph::Generate(int minL, int maxL, int minP, int maxP){

	int K,a,v,p;

	int ** L = new int*[this->N];

	for(int i=0; i<this->N; i++)
	{
		L[i] = new int[this->N];
	}

	int * numL = new int[this->N];
	int * tpL = new int[this->N];



	srand(time(NULL));

	for(int i = 0; i<this->N;i++)
	{
		for(int j = 0; j<this->N; j++)
		{
			if(i == j)
			{
				L[i][j]=0;
			}
			else
			{
				L[i][j]=-1;
			}
		}
		numL[i] = minL + (rand()%(maxL-minL));
	}

	for(int k = 1; k<=minL;k++)
	{
		for(int n = 0; n<this->N; n++)
		{
			if(numL[n] > 0)
			{
				K=0;
				for(p=0; p<this->N;p++)
				{
					if((L[n][p] < 0) && (numL[p] > 0))
					{
						tpL[K] = p;
					}
					K++;
				}

				if(K>0)
				{
					v = rand()%K;
					a = tpL[v];
					p = minP + rand()%(maxP-minP+1);
					L[n][a] = p;
					L[a][n] = p;
					numL[n]--;
					numL[a]--;
				}
			}

		}
	}

	return L;
}


void CGraph::displayNodes(void){

	cout << "\nAvailable nodes:";

	for(auto it=this->graph.begin();it!=this->graph.end();it++)
	{
		cout << "\n" << it->id;
	}

}

int CGraph::countViewedNodes(void){

	int retVal = 0;

	for(auto it=this->graph.begin();it!=this->graph.end();it++)
	{
		if(it->PassedOn == true)
		{
			retVal++;
		}
	}
	return retVal;
}

void CGraph::displayViewedNodes(void){
    int nb_char=0;
	std::cout << "\nNodes passed on:\n";

	for(auto it=this->graph.begin();it!=this->graph.end();it++)
	{
		if(it->PassedOn == true)
		{
			std::cout << it->id;
            if((it+1)!=this->graph.end()){
                cout<<'-';
            }
            nb_char+=2;
		}
        if(nb_char>=100){
            std::cout<<'\n';
            nb_char=0;
        }
	}
}

void CGraph::displayPath(std::vector<int> v){

    int nb_char=0;
    if(!v.empty()) {
        cout << "\nPath taken to get from " << v.front() << " to " << v.back()<<'\n';
        for (auto it:v) {

            if(it==v.back()){
                cout<<it;
            }
            else{
                cout<<it<<"->";
                nb_char+=4;
            }
            if (nb_char >= 100) {
                std::cout << '\n';
                nb_char = 0;
            }
        }
        std::cout << '\n';
    }
}

int CGraph::countSolutionCost(std::vector<int> v){

	int retVal = 0;

	for(auto it = v.begin(); (it+1)!=v.end() ; it++)
	{
		for(auto itv = this->graph.begin(); itv!=this->graph.end();itv++)
		{
			if(itv->id == *it)
			{
				for(auto itl=itv->nodes.begin(); itl!=itv->nodes.end(); itl++)
				{
					if(itl->id == *(it+1))
					{
						retVal += itl->value;
						break;
					}
				}
				break;
			}
		}


	}

	return retVal;

}

void CGraph::addEdges(std::vector<Graph> &tree,int idSrc, int idDst, int Value){

	bool done = false;

	for(auto it = tree.begin(); it!=tree.end() && done==false; it++)
	{
		if(it->id == idSrc)
		{
			for(auto itl = it->nodes.begin(); itl != it->nodes.end() && done==false; itl++)
			{
				auto Next = itl;
				Next++;
				if(itl->id < idDst && ((Next->id > idDst) || (Next==it->nodes.end())))
				{
					it->nodes.insert(Next,Node(idDst,Value));
					it->nb_nodes++;
					done = true;
				}
				else if(itl->id == idDst)
				{
					done=true;
				}
			}
		}
	}



}

bool CGraph::isEdgeInList(std::list<Node> l, int id){

	bool retVal = false;

	for(auto it = l.begin(); (it != l.end()) && retVal==false; it++)
	{
		if(it->id==id)
		{
			retVal = true;
		}
	}

	return retVal;
}

int CGraph::nodeToNodeValue(std::vector<Graph> v, int id_from, int id_to){

	int retVal = -1;

	if(id_from == id_to)
	{
		retVal=0;
	}
	else
	{
		for (auto it = v.begin(); it != v.end(); it++) {
			if (it->id == id_from)
			{
				retVal=isIdInList(it->nodes,id_to);
			}
		}

	}

	return retVal;
}

int CGraph::isIdInList(std::list<Node> list, int id){

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

bool CGraph::isEdgeVisited(std::vector<Graph> v, int id){
	int retVal = false;

	for(auto it = v.begin(); it != v.end() ; it++)
	{
		if(it->id == id)
		{
			retVal = it->PassedOn;
			break;
		}
	}

	return retVal;
}

void CGraph::resetVisited() {
    for(auto it=this->graph.begin();it!=this->graph.end();it++)
    {
        it->PassedOn= false;
    }
}

void CGraph::resetDistance() {
    for(auto it=this->graph.begin();it!=this->graph.end();it++)
    {
        it->Distance= -1;
    }
}







