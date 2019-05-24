struct Graph;

void printArray(double arr[], int arr_size);


class GraphClassMatrix
{
private:
	struct Graph* graph;

	void createGraph(int V);
public:
	GraphClassMatrix(int V);

	~GraphClassMatrix();

	
	void addDirectedEdge(int source, int dest, double weight);

	void addEdge(int source, int dest, double weight);

	bool canAddDirectedEdge(int source, int dest);

	bool canAddEdge(int source, int dest);

	void printEdges();

	inline int getV();
	inline double getEdge(int src, int dest);
};

void getDistance(GraphClassMatrix *graph, int source, bool debug = false);

void getRandomGraph(GraphClassMatrix* graph, int V, double Density);