#include <iostream>
using namespace std;
#define INT_MAX 2147483647

class Graph
{
    int adjMatrix[20][20];
    int Nodes;
    int Edges;
    int weight;

    void addEdge(int source, int destination, int weight)
    {
        adjMatrix[source][destination] = weight;
    }

public:
    Graph(int Nodes, int Edges)
    {
        this->Nodes = Nodes;
        this->Edges = Edges;
        for (int i = 0; i < Nodes; i++)
        {
            for (int j = 0; j < Nodes; j++)
            {
                adjMatrix[i][j] = 0;
            }
        }
        weight = 0;
    }
    void Display()
    {
        for (int i = 0; i < Nodes; i++)
        {
            for (int j = 0; j < Nodes; j++)
            {
                if (adjMatrix[i][j] != 0)
                {
                    cout << i << " - " << j << " :  " << adjMatrix[i][j] << endl;
                }
            }
        }
    }
    void Create()
    {
        int source;
        int destination;
        int weight;
        for (int i = 0; i < Edges; i++)
        {
            cout << "Enter Source: ";
            cin >> source;
            cout << "Enter Destination: ";
            cin >> destination;
            cout << "Enter Weight: ";
            cin >> weight;
            addEdge(source, destination, weight);
            addEdge(destination, source, weight);
        }
    }
    void Prims()
    {
        int edges_no = 0;
        int selected[Nodes];

        // initialize all the postions to false initially
        for (int i = 0; i < Nodes; i++)
        {
            selected[i] = false;
        }
        // Start from the first element
        // so mark the first element to be visited
        selected[0] = true;
        int min = INT_MAX;
        int x = 0;
        int y = 0;

        // from each edge traverse to all other edges
        // E = < V - 1
        while (edges_no < Nodes - 1)
        {
            // Let the min value be the maximum element that is present
            min = INT_MAX; // holds the min weight
            x = 0;         // row of the MST element that we need to display
            y = 0;         // Column of MST element that we need to display

            // traverse the row
            for (int i = 0; i < Nodes; i++)
            {
                // traverse the column elements only for the vertex that we are visiting
                if (selected[i])
                {
                    // traverse the column
                    for (int j = 0; j < Nodes; j++)
                    {
                        // Select only Non-Zero and Non-Visited element to display
                        if (!selected[j] && adjMatrix[i][j])
                        {
                            // Find out the min element from the column
                            if (min > adjMatrix[i][j])
                            {
                                min = adjMatrix[i][j];
                                // Store the position of Min Element in X and Y
                                x = i;
                                y = j;
                            }
                        }
                    }
                }
            }
            // The Minimum element will be G[X][Y]
            cout << x << " - " << y << " :  " << adjMatrix[x][y];
            weight += adjMatrix[x][y];
            cout << endl;

            // Make the selected column element to be visited
            selected[y] = true;

            // Increment the edge_no
            edges_no++;
        }
        cout << "Weight of minimum spanning tree: " << weight << endl;
    }
};

int main()
{
    int vertices;
    int edges;
    cout << "Enter No of Vertices: ";
    cin >> vertices;
    cout << "Enter No of Edges: ";
    cin >> edges;
    Graph g1(vertices, edges);
    g1.Create();
    cout << "\n\nGRAPH" << endl;
    g1.Display();
    cout << "\n\nMIN SPANNING TREE" << endl;
    g1.Prims();
    return 0;
}