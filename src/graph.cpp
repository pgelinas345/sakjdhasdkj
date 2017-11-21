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

CGraph::CGraph(){
	this->N=0;
	char user;
	int ** L = NULL;
	std::string file_name;


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

    		//L = ReadFromFile("./src/Londres.txt");

			if(L == NULL) printf("\nFile not found!");
    	}
    }
    else
    {
        cout << "\nEnter valid number of nodes:";
        cout << "\n=>";

        cin >> this->N;


    }

    CreateFromMatrice(L);

}

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
			numL[i] = minL + (rand()%(maxL-minL));
		}
	}

	for(int k = 0; k<minL;k++)
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
						tpL[k] = p;
						K++;
					}
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


















