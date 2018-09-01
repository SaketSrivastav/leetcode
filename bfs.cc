#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

class Graph {
  int V; // num of vertices;
  list<int> *adj; // adjacency list
public:
  Graph(int V) {
    this->V = V;
    adj = new list<int>[V]; // init the new adj list
  }

  void add_edge(int u, int v) {
    adj[u].push_back(v); // add v to u's adj list
  }

  void print_graph() {
    for(int v=0; v<V; v++) {
      cout << "Adj list of v = " << v << endl;
      for (auto & e : adj[v]) {
        cout << e << " ";
      }
      cout << endl;
    }
  }

  bool bfs(int s) {
    queue<int> pq;
    vector<bool> visit = {false};

    if(s >= V) return false;

    print_graph();

    visit.resize(V);

    visit[s] = true;
    pq.emplace(s);
    while(!pq.empty()) {
      s = pq.front();
      pq.pop();

      cout << "Check neighbors of " << s << ":\n" ;
      for(auto e : adj[s]) {
        if(!visit[e]) {
          visit[e] = true;
          cout << "Append: " << e << endl;
          pq.emplace(e);
        } else {
          cout << "Already visited " << e << endl;
        }
      }
    }
    cout << endl;

    return true;
  }
};

void test_bfs() {
  bool pass = false;

  do{
    Graph g(4);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 2);
    g.add_edge(2, 0);
    g.add_edge(2, 3);
    g.add_edge(3, 3);

    pass = g.bfs(2);

  }while(0);

  if(!pass) {
    cout << "BFS failed for graph" << endl;
  }
}

int main(int argc, char *argv[])
{
  test_bfs();
  return 0;
}
