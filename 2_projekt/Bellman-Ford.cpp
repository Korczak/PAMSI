#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <fstream>

using namespace std;


ofstream minFile[2];
ofstream maxFile[2];
ofstream avgFile[2];

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


class GraphClass
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
	GraphClass(int V) {
		graph = new Graph;
		createGraph(V);
	}	

	~GraphClass() {
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
				cout << edge->dest << " ";
				edge = edge->next;
			}
			cout << endl;
		}
	}

	inline int getV() { return graph->V; }
	inline Edge* getEdge(int i) { return &graph->edge[i]; }
};

void BellmanFord(GraphClass *graph, int source, bool debug = false) {
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

void Dijkstra(GraphClass *graph, int source, bool debug = false) {
	int V = graph->getV();
	double cost[V];
	bool visited[V];
	int maxCost = 99999;


	for(int i = 0; i < V; i++) { 
		cost[i] = maxCost;
		visited[i] = false;
	}
	cost[source] = 0;
	visited[source] = true;

	for(int i = 0; i < V; i++) {
		double min = maxCost;
		int index = 0;
		for(int j = 0; j < V; j++) {
			if(min > cost[j] && !visited[j]) {
				min = cost[j];
				index = j;
			}
		}

		Edge* edge = graph->getEdge(index);
		while(edge->dest != -1) {
			if(edge->weight != 0) {
				if(cost[index] + edge->weight < cost[edge->dest]) {
					cost[edge->dest] = cost[index] + edge->weight;
				}
			}
			edge = edge->next;
		}
		visited[index] = true;
	}

	if(debug)
		printArray(cost, V);
}

void getRandomGraph(GraphClass* graph, int V, double Density) {
	int source = 0;
	int dest = 0;
	double weight = 0;

	int E = (int)(Density * V * (V-1)) / 2;

	if(Density == 1) {
		for(int i = 0; i < V; i++) {
			for(int j = i + 1; j < V; j++) {
				weight = rand() % 20;
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

void testAlgorithm() {
	double density[] = {0.25, 0.5, 0.75, 1};
	int numVertex[] = {10, 50, 100, 500, 1000};
	int numTests = 100;
	double minTime[2] = {999, 999};
	double maxTime[2] = {0, 0};
	double duration;
	double totalTime[2] = {0, 0};

	for(int i = 0; i < sizeof(numVertex)/sizeof(numVertex[0]); i++) {
		for(int j = 0; j < sizeof(density)/sizeof(density[0]); j++) {
			for(int k = 0; k < 2; k++) {
				minTime[k] = 999;
				maxTime[k] = 0;
				totalTime[k] = 0;
			}

			for(int k = 0; k < 100; k++) {
				GraphClass* graph = new GraphClass(numVertex[i]);
				getRandomGraph(graph, numVertex[i], density[j]);
				
				clock_t start = clock();
				BellmanFord(graph, 0);
				duration = ((clock() - start) / (double) CLOCKS_PER_SEC);
				if(minTime[0] > duration)
					minTime[0] = duration;
				if(maxTime[0] < duration)
					maxTime[0] = duration;
				totalTime[0] += duration;

				start = clock();
				Dijkstra(graph, 0);
				duration = ((clock() - start) / (double) CLOCKS_PER_SEC);
				if(minTime[1] > duration)
					minTime[1] = duration;
				if(maxTime[1] < duration)
					maxTime[1] = duration;
				totalTime[1] += duration;

				delete graph;
			}


			double avgTime = totalTime[0] / numTests;
			avgFile[0] << "AVG::Num vertex " << numVertex[i] << " density " << density[j] << ": " << avgTime << endl;
			minFile[0] << "MIN::Num vertex " << numVertex[i] << " density " << density[j] << ": " << minTime[0] << endl;
			maxFile[0] << "MAX::Num vertex " << numVertex[i] << " density " << density[j] << ": " << maxTime[0] << endl;

			avgTime = totalTime[1] / numTests;
			avgFile[1] << "AVG::Num vertex " << numVertex[i] << " density " << density[j] << ": " << avgTime << endl;
			minFile[1] << "MIN::Num vertex " << numVertex[i] << " density " << density[j] << ": " << minTime[1] << endl;
			maxFile[1] << "MAX::Num vertex " << numVertex[i] << " density " << density[j] << ": " << maxTime[1] << endl;
		} 
	}
}

istream& readGraph(istream& input) {
	int V, E, source;
	input >> V >> E >> source;
	GraphClass* graph = new GraphClass(V);

	for(int i = 0; i < E; i++) {
		int src, dst;
		double weight; 
		input >> src >> dst >> weight;
		graph->addDirectedEdge(src, dst, weight);
	}

	BellmanFord(graph, source, true);
	return input;
}


int main() {
	srand(time(NULL));
	minFile[0].open("min_1_BF.txt");
	maxFile[0].open("max_1_BF.txt");
	avgFile[0].open("avg_1_BF.txt");

	minFile[1].open("min_1_DIJ.txt");
	maxFile[1].open("max_1_DIJ.txt");
	avgFile[1].open("avg_1_DIJ.txt");


	testAlgorithm();
	
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
	Dijkstra(&graph, 0, true);
	
}