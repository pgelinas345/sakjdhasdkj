//============================================================================
// Name        : lab3.cpp
// Author      : Philippe Gelinas
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <chrono>
#include "algorithm.h"
#include "graph.h"
using namespace std;



int main() {

	int z;
    int choice,start,stop,method;
    std::chrono::system_clock::time_point start_time,end_time;
    std::chrono::duration<double> time_count;

	std::vector<int> x;;

	CGraph * G = new(CGraph);

	G->createNewGraph();

	algorithm Al;

	std::cout << "\033[2J\033[1;1H";
	while(choice !='q' && method!='q' && start !='q' && stop !='q'){
        std::cout<<"=====LAB3 Testbench=====\n";
        std::cout<<"Veuillez entrer le type de probleme a resoudre\n";
        std::cout<<"1. Labyrinthe/TL\n2. Carte routiere\n";
        std::cin>>choice;
        std::cout<<"Veuillez entrer le noeud de depart\n";
        std::cin>>start;
        std::cout<<"Veuillez entrer le noeud d'arriver\n";
        std::cin>>stop;
        std::cout<<"Veuillez entrer le type d'algorithm\n";
        if(choice=='1'){
            std::cout<<"1. Recherche en profondeur\n2. Recherche en largeur\n";
            std::cin>>method;
            switch(method){
                case '1':
                    G->resetVisited();
                    x.resize(G->N);

                    start_time = std::chrono::high_resolution_clock::now();

                    Al.deep_search(G,start,stop,x,0);

                    G->displayViewedNodes();

                    G->displayPath(x);

                    end_time = std::chrono::high_resolution_clock::now();

                    time_count = end_time - start_time;

                    std::cout << "\nElapsed time: " << time_count.count() << "s\n";

                    break;
                case '2':
                    G->resetVisited();
                    x.resize(G->N);

                    start_time = std::chrono::high_resolution_clock::now();

                    Al.wide_search(G,start,stop,x);

                    G->displayViewedNodes();

                    G->displayPath(x);

                    end_time = std::chrono::high_resolution_clock::now();

                    time_count = end_time - start_time;

                    std::cout << "\nElapsed time: " << time_count.count() << "s\n";
                    break;
                default:
                    break;
            }
        }
        else{
            std::cout<<"1. Recherche en profondeur\n2. Dijkstra\n3. Floyd-Warshall\n";
            std::cin>>method;
            switch(method){
                case '1':
                    break;
                case '2':
                    break;
                case '3':
                    break;
                default:
                    break;
            }
        }





    }
//    x.resize(G->N);
//
//    start_time = std::chrono::high_resolution_clock::now();
//
//    Al.floyd_warshal_search(G,0,4,x);
//
//    G->displayViewedNodes();
//
//    G->displayPath(x);
//
//    z = G->countSolutionCost(x);
//
//    cout << "\nTotal cost = " << z;
//
//    end_time = std::chrono::high_resolution_clock::now();
//
//    time_count = end_time - start_time;
//
//    std::cout << "\nElapsed time: " << time_count.count() << "s\n";

    delete G;

	return 0;
}
