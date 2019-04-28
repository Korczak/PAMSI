#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <fstream>

using namespace std;

ofstream minFile;
ofstream maxFile;
ofstream avgFile;


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


class GraphClass
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
	GraphClass(int V) {
		graph = new Graph;
		createGraph(V);
	}

	~GraphClass() {
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
void getDistance(GraphClass *graph, int source, bool debug = false) {
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
void getRandomGraph(GraphClass* graph, int V, double Density) {
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
				GraphClass* graph = new GraphClass(numVertex[i]);
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
			avgFile << "Num vertex " << numVertex[i] << " density " << density[j] << ": " << avgTime << endl;
			minFile << "Num vertex " << numVertex[i] << " density " << density[j] << ": " << minTime << endl;
			maxFile << "Num vertex " << numVertex[i] << " density " << density[j] << ": " << maxTime << endl;
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
	GraphClass* graph = new GraphClass(V);

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
	//minFile.open("min_2.txt");
	//maxFile.open("max_2.txt");
	//avgFile.open("avg_2.txt");

	ifstream inputFile("input.txt");
	//readGraph(cin);

	//testAlgorithm();
	int V = 5;
	
	
	GraphClass graph(V);

	graph.addEdge(0, 1, 1);
	graph.addEdge(0, 2, 3);
	//graph.addEdge(0, 3, -1);
	graph.addDirectedEdge(0, 3, -2);
	graph.addEdge(1, 3, 1);
	graph.addEdge(2, 3, 5);
	graph.addEdge(2, 4, 1);
	graph.addEdge(3, 4, 1);
	
	//getRandomGraph(&graph, V, 0.75);
	graph.printEdges();
	int source = 0;
	cout << "Distance from " << source << " is: " << endl;
	getDistance(&graph, 0, true);
	
}