#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <fstream>

struct Edge;
struct Graph;
void printArray(double arr[], int arr_size);


class GraphClassList
{
private:
	struct Graph* graph;

	void createGraph(int V);
public:
	GraphClassList(int V);

	~GraphClassList();

	void addDirectedEdge(int source, int dest, double weight);

	void addEdge(int source, int dest, double weight);

	bool canAddDirectedEdge(int src, int dest);

	bool canAddEdge(int src, int dest);

	void printEdges();

	inline int getV();
	inline Edge* getEdge(int i);
};

void getDistance(GraphClassList *graph, int source, bool debug = false);

void getRandomGraph(GraphClassList* graph, int V, double Density);