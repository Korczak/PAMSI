#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <fstream>

using namespace std;


struct Graph
{
	int V, E;

	double** edge;
};

void printArray(double arr[], int arr_size) {
	for(int i = 0; i < arr_size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}


class GraphClassMatrix
{
private:
	struct Graph* graph;

	void createGraph(int V) {
		graph->V = V;
		graph->E = 0;
		
		graph->edge = new double*[V];

		for(int i = 0; i < V; i++) {
			graph->edge[i] = new double[V];
			for(int j = 0; j < V; j++){
				graph->edge[i][j] = 0;
			}
		}
	}
public:
	GraphClassMatrix(int V) {
		graph = new Graph;
		createGraph(V);
	}

	~GraphClassMatrix() {
		for(int i = 0; i < graph->V; i++) 
			delete[] graph->edge[i];

		delete[] graph->edge;
		delete graph;
	}

	
	/*
		Adding direct Edge to graph

		:param source: vertex from which is going to add edge
		:param dest: destination vertex of edge
	*/
	void addDirectedEdge(int source, int dest, double weight) {
		if(graph->edge[source][dest] != 0)
			return;
		
		graph->E++;
		graph->edge[source][dest] = weight;
	}

	void addEdge(int source, int dest, double weight) {	
		addDirectedEdge(source, dest, weight);
		addDirectedEdge(dest, source, weight);
	}

	bool canAddDirectedEdge(int source, int dest) {
		return (graph->edge[source][dest] == 0);
	}

	bool canAddEdge(int source, int dest) {
		return canAddDirectedEdge(source, dest) && canAddDirectedEdge(dest, source);
	}

	/*
		Print all connections from all Vertex to any other Vertex
		No edge = 0, any other value means that there is edge
	*/
	void printEdges() {
		cout << "Print Edges" << endl;
		int V = graph->V;
		for(int i = 0; i < V; i++) {
			cout << i << ": ";
			for(int j = 0; j < V; j++) {
				cout << graph->edge[i][j] << " ";
			}
			cout << endl;
		}
	}

	inline int getV() { return graph->V; }
	inline double getEdge(int src, int dest) { return graph->edge[src][dest]; }
};

/*
	Calculates distance from source to any other vertex

	:param source: source vertex from where calculate dist
	:param debug:  show array of distance to every vertex (starting from 0 to V) 

	!!! if graph has negative cycle, algorithm print message !!! 
*/
void getDistance(GraphClassMatrix *graph, int source, bool debug = false) {
	int V = graph->getV();
	double cost[V];
	int prev[V];
	int maxCost = 99999;


	for(int i = 0; i < V; i++) { 
		cost[i] = maxCost;
		prev[i] = -1;
	}
	cost[source] = 0;


	bool isChange = true;
	for(int v = 0; v < V && isChange; v++) {
		isChange = false;
		for(int i = 0; i < V; i++) {
			for(int j = 0; j < V; j++) {
				if(graph->getEdge(i, j) != 0) {
					if(cost[j] > cost[i] + graph->getEdge(i, j)) {
						cost[j] = cost[i] + graph->getEdge(i, j);
						prev[i] = j;
						isChange = true;
					}
				}
			}		
		}
	}

	for(int i = 0; i < V; i++) {
		for(int j = 0; j < V; j++) {
			if(graph->getEdge(i, j) != 0) {
				if(cost[i] != maxCost && cost[i] + graph->getEdge(i, j) < cost[j]) {
					cout << "Graph has negative cycle" << endl;
					return;
				}
			}
		}
	}

	if(debug)
		printArray(cost, V);
}

/*
	Creates randomized edges to graph

	:param graph: initialized graph of V vertex
	:param V: number of graph Vertex
	:param Density: density of graph edges
*/
void getRandomGraph(GraphClassMatrix* graph, int V, double Density) {
	int source = 0;
	int dest = 0;
	double weight = 0;

	int E = (int)(Density * V * (V-1)) / 2;


	for(int i = 0; i < E; i++) {
		while(true) {
			source = rand() % V;
			dest = rand() % V;
			weight = rand() % 20;
			if(source == dest)
				continue;			
			if(!graph->canAddEdge(source, dest))
				continue;
			graph->addEdge(source, dest, weight);
			break;
		}
	}
}

