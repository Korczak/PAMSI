#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <fstream>

using namespace std;

ofstream minFile;
ofstream maxFile;
ofstream avgFile;

struct Edge 
{ 
    int dest;
    double weight; 

    Edge* next;
    void addVertex(int, double);
}; 

void Edge::addVertex(int dest, double weight) {
	this->dest = dest;
	this->weight = weight;
}

struct Graph
{
	int V, E;

	struct Edge* edge;
};

void printArray(double arr[], int arr_size) {
	for(int i = 0; i < arr_size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}


class BellmanFord
{
private:
	struct Graph* graph;

	void createGraph(int V) {
		graph->V = V;
		graph->E = 0;
		graph->edge = new Edge[V];
		for(int i = 0; i < V; i++) {
			graph->edge[i].dest = -1;
		}
	}
public:
	BellmanFord(int V) {
		graph = new Graph;
		createGraph(V);
	}	

	~BellmanFord() {
		for(int V = 0; V < graph->V; V++) {
			Edge* edges[graph->V];
			Edge* edge = &graph->edge[V];
			int i = -1;
			while(edge->dest != -1) {
				edge = edge->next;
				edges[++i] = edge;
			}
			for(; i >= 0; i--)
				delete edges[i];
		}

		delete[] graph->edge;
		delete graph;
	}

	void addDirectedEdge(int source, int dest, double weight) {
		graph->E++;
		struct Edge* edge = &graph->edge[source];

		while(edge->dest != -1) {
			edge = edge->next;
		}

		struct Edge* newEdge = new Edge;
		newEdge->dest = -1;
		edge->addVertex(dest, weight);
		edge->next = newEdge;
	}

	void addEdge(int source, int dest, double weight) {
		addDirectedEdge(source, dest, weight);
		addDirectedEdge(dest, source, weight);
	}

	bool canAddDirectedEdge(int src, int dest) {
		struct Edge* edge = &graph->edge[src];

		while(edge->dest != -1) {
			if(edge->dest == dest)
				return false;
			edge = edge->next;
		}

		return true;
	}

	bool canAddEdge(int src, int dest) {
		bool canAddDirectedEdge_1 = canAddDirectedEdge(src, dest);
		bool canAddDirectedEdge_2 = canAddDirectedEdge(dest, dest);

		return canAddDirectedEdge_1 && canAddDirectedEdge_2;
	}

	void printEdges() {
		cout << "Print Edges" << endl;
		int V = graph->V;
		for(int i = 0; i < V; i++) {
			struct Edge* edge = &graph->edge[i];
			while(edge->dest != -1) {
				edge = edge->next;
			}
		}
	}

	void getDistance(int source, bool debug = false) {
		int V = graph->V;
		double cost[V];
		int maxCost = 99999;


		for(int i = 0; i < V; i++) 
			cost[i] = maxCost;
		cost[source] = 0;


		bool isChange = true;
		for(int v = 0; v < V && isChange; v++) {
			isChange = false;
			for(int i = 0; i < V; i++) {
		
				Edge* edge = &graph->edge[i];
				while(edge->dest != -1) {

					if(cost[edge->dest] > cost[i] + edge->weight) {
						cost[edge->dest] = cost[i] + edge->weight;
						isChange = true;
					}
					edge = edge->next;
				}
			}
		}

		for(int i = 0; i < V; i++) {
			Edge* edge = &graph->edge[i];
			while(edge->dest != -1) {
				if(edge->weight != 0) {
					if(cost[i] != maxCost && cost[i] + edge->weight < cost[edge->dest]) {
						cout << "Graph has negative cycle" << endl;
						return;
					}
				}
				edge = edge->next;
			}
		}
		if(debug)
			printArray(cost, V);
	}

};


void getRandomGraph(BellmanFord* graph, int V, double Density) {
	int source = 0;
	int dest = 0;
	double weight = 0;

	int E = (int)(Density * V * (V-1)) / 2;


	bool canAddEdge = false;
	for(int i = 0; i < E; i++) {
		canAddEdge = false;
		while(!canAddEdge) {
			source = rand() % V;
			dest = rand() % V;
			weight = rand() % 20;
			if(source == dest)
				continue;
			canAddEdge = graph->canAddEdge(source, dest);
			if(!canAddEdge)
				continue;
			graph->addEdge(source, dest, weight);
		}
	}
}

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
				BellmanFord* graph = new BellmanFord(numVertex[i]);
				clock_t start2 = clock();
				getRandomGraph(graph, numVertex[i], density[j]);
				cout << ((clock() - start2) / (double) CLOCKS_PER_SEC) << " " << numVertex[i] << endl;
				clock_t start = clock();
				graph->getDistance(0);
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

istream& readGraph(istream& input) {
	int V, E, source;
	input >> V >> E >> source;
	BellmanFord* graph = new BellmanFord(V);

	for(int i = 0; i < E; i++) {
		int src, dst;
		double weight; 
		input >> src >> dst >> weight;
		graph->addDirectedEdge(src, dst, weight);
	}

	graph->getDistance(source, true);
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
	BellmanFord graph(V);

	graph.addEdge(0, 1, 1);
	graph.addEdge(0, 2, 1);
	graph.addEdge(1, 3, 1);
	graph.addEdge(2, 3, 1);
	graph.addEdge(2, 4, 1);
	graph.addEdge(3, 4, 1);
	graph.printEdges();
	int source = 0;
	cout << "Distance from " << source << " is: " << endl;
	graph.getDistance(0);
	*/
}