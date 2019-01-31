#include <iostream>
#include <list>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, int> int_pair;

class Graph
{
    int num_vertex;
    list<int_pair> *adj; // adjacency list
public:
    Graph(int vertices) {
        num_vertex = vertices;
        adj = new list<int_pair>[num_vertex];
    }

    // make_pair with weight as first and vertex as second so that we always sort based on weight
    void addEdge(int u, int v, int w) {
        adj[u].push_back(make_pair(w, v));
        adj[v].push_back(make_pair(w, u));
    }

    // Find shortest path from s to all other vetices
    vector<int> shortest_path(int s) {
        // stores min weight edges between s and its neighbors
        priority_queue<int_pair, vector<int_pair>, greater<int_pair>> min_heap;
        vector<int> dist(num_vertex, INT_MAX);

        // Add source to heap, 0 because distance from source to source = 0
        min_heap.push(make_pair(0, s));
        dist[s] = 0;
        while(!min_heap.empty()) {
            int u = min_heap.top().second; // Get the adj node
            min_heap.pop();

            list<pair<int, int>>::iterator i;
            // Visit each neighbor BFS way and update distance to v through u
            for(i = adj[u].begin(); i != adj[u].end(); i++) {
                int v = i->first;
                int weight = i->second;
                if(dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    min_heap.push(make_pair(dist[v], v));
                }
            }
        }
        // Print shortest distances stored in dist[]
        printf("Vertex   Distance from Source\n");
        for (int i = 0; i < num_vertex; ++i)
            printf("%d \t\t %d\n", i, dist[i]);

        return dist;
    }
};
int main()
{
    // create the graph given in above fugure
    int V = 9;
    Graph g(V);

    //  making above shown graph
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    g.shortest_path(0);

    return 0;
}
