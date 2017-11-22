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

#include "graph.h"
using namespace std;

int main() {

	int idDepart;


	CGraph * G = new(CGraph);

	auto start_time = std::chrono::high_resolution_clock::now();

	G->displayNodes();

	auto end_time = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> time_count = end_time - start_time;

	std::cout << "\nElapsed time: " << time_count.count() << "s\n";

	delete G;

	return 0;
}
