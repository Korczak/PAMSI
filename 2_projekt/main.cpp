#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <fstream>

#include "GraphClassMatrix.h"
#include "GraphClassList.h"

using namespace std;

ofstream minFile;
ofstream maxFile;
ofstream avgFile;

/*
	Test algorithm and saves scores in files (avgFile, minFile, maxFile)
*/
void testAlgorithm() {
	double density[] = {0.25, 0.5, 0.75, 1};
	int numVertex[] = {10, 50, 100, 500, 1000};
	int numTests = 100;
	double minTime = 999;
	double maxTime = 0;
	double duration;
	double totalTime = 0;

	for(int i = 0; i < sizeof(numVertex)/sizeof(numVertex[0]); i++) {
		for(int j = 0; j < sizeof(density)/sizeof(density[0]); j++) {
			minTime = 999;
			maxTime = 0;
			totalTime = 0;

			for(int k = 0; k < numTests; k++) {
				GraphClassList* graph = new GraphClassList(numVertex[i]);
				getRandomGraph(graph, numVertex[i], density[j]);
				clock_t start = clock();
				getDistance(graph, 0);
				duration = ((clock() - start) / (double) CLOCKS_PER_SEC);
				if(minTime > duration)
					minTime = duration;
				if(maxTime < duration)
					maxTime = duration;
				totalTime += duration;
				delete graph;
			}
			double avgTime = totalTime / numTests;
			avgFile << "AVG::Num vertex " << numVertex[i] << " density " << density[j] << ": " << avgTime << endl;
			minFile << "MIN::Num vertex " << numVertex[i] << " density " << density[j] << ": " << minTime << endl;
			maxFile << "MAX::Num vertex " << numVertex[i] << " density " << density[j] << ": " << maxTime << endl;
		} 
	}
}


/*
	Read graph from input

	INPUT:
		Vertex   Edges   Source

	INPUT of every edge:
		Source   Destination   Weight

	OUTPUT:
		Distance to each vertex of graph from source vertex
*/
istream& readGraph(istream& input) {
	int V, E, source;
	input >> V >> E >> source;
	GraphClassList* graph = new GraphClassList(V);

	for(int i = 0; i < E; i++) {
		int src, dst;
		double weight; 
		input >> src >> dst >> weight;
		graph->addDirectedEdge(src, dst, weight);
	}

	getDistance(graph, source, true);
	return input;
}


int main() {
	srand(time(NULL));
	minFile.open("min_1.txt");
	maxFile.open("max_1.txt");
	avgFile.open("avg_1.txt");


	testAlgorithm();
	/*
	int V = 5;
	GraphClass graph(V);

	graph.addEdge(0, 1, 1);
	graph.addEdge(0, 2, 1);
	graph.addEdge(1, 3, 1);
	graph.addEdge(2, 3, 1);
	graph.addEdge(2, 4, 1);
	graph.addEdge(3, 4, 1);
	graph.printEdges();
	int source = 0;
	cout << "Distance from " << source << " is: " << endl;
	getDistance(&graph, 0, true);
	*/
}