#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <fstream>

using namespace std;

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
	struct Edge** lastEdge;
};

void printArray(double arr[], int arr_size) {
	for(int i = 0; i < arr_size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}


class GraphClassList
{
private:
	struct Graph* graph;

	void createGraph(int V) {
		graph->V = V;
		graph->E = 0;
		graph->edge = new Edge[V];
		graph->lastEdge = new Edge*[V];
		for(int i = 0; i < V; i++) {
			graph->edge[i].dest = -1;
			graph->lastEdge[i] = &graph->edge[i];
		}
	}
public:
	GraphClassList(int V) {
		graph = new Graph;
		createGraph(V);
	}	

	~GraphClassList() {
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
		delete[] graph->lastEdge;
		delete graph;
	}

	void addDirectedEdge(int source, int dest, double weight) {
		graph->E++;
		struct Edge* edge = graph->lastEdge[source];

		struct Edge* newEdge = new Edge;
		newEdge->dest = -1;
		edge->addVertex(dest, weight);
		edge->next = newEdge;
		graph->lastEdge[source] = newEdge;
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
				cout << edge->dest << " ";
				edge = edge->next;
			}
			cout << endl;
		}
	}

	inline int getV() { return graph->V; }
	inline Edge* getEdge(int i) { return &graph->edge[i]; }
};

void getDistance(GraphClassList *graph, int source, bool debug = false) {
	int V = graph->getV();
	double cost[V];
	int maxCost = 99999;


	for(int i = 0; i < V; i++) 
		cost[i] = maxCost;
	cost[source] = 0;


	bool isChange = true;
	for(int v = 0; v < V && isChange; v++) {
		isChange = false;
		for(int i = 0; i < V; i++) {
	
			Edge* edge = graph->getEdge(i);
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
		Edge* edge = graph->getEdge(i);
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


void getRandomGraph(GraphClassList* graph, int V, double Density) {
	int source = 0;
	int dest = 0;
	double weight = 0;

	int E = (int)(Density * V * (V-1)) / 2;

	if(Density == 1) {
		for(int i = 0; i < V; i++) {
			for(int j = i + 1; j < V; j++) {
				graph->addEdge(i, j, weight);
			}
		}
		return;
	}

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
