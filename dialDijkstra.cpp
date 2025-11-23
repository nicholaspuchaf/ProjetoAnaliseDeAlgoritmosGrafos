#include <iostream>
#include <vector>
#include <deque>
#include <cmath>
#include <limits>
#include <numeric>

#include <chrono>

using namespace std;

const int INF = numeric_limits<int>::max();

// Lê o grafo e já converte pesos double para int
void create_graph_converted(int &n, int &m, int &s, int &d, vector<vector<pair<int, int>>> &graph, int &max_weight) {
    cin >> n >> m >> s >> d;
    graph.assign(n, vector<pair<int, int>>());
    max_weight = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        int iw = static_cast<int>(round(w));
        graph[u].push_back({iw, v});
        graph[v].push_back({iw, u});
        if (iw > max_weight)
            max_weight = iw;
    }
}

double dijkstra_dial(int n, int source, int dest,
                     const vector<vector<pair<int, int>>> &graph,
                     int max_weight) {
    
    // Estruturas para busca a partir do source
    vector<int> dist_f(n, INF);
    vector<deque<int>> buckets_f(max_weight + 1); 
    dist_f[source] = 0;
    buckets_f[0].push_back(source);
    
    int processed = 0;
    int idx = 0;
    
    while(processed < n){
        while(buckets_f[idx].empty())
            idx = (idx+1) % (max_weight+1);

        auto t = buckets_f[idx].back();
        buckets_f[idx].pop_back();

        processed++;

        for(auto &k : graph[t]){

            if(dist_f[k.second] > dist_f[t] + k.first){
                dist_f[k.second] = dist_f[t] + k.first;
                int d = dist_f[k.second];
                buckets_f[d % (max_weight+1)].push_back(k.second);
            }
        }
    }

    return dist_f[dest];
}

int main() {
    int n, m, s, d, max_weight;
    vector<vector<pair<int, int>>> graph;
    create_graph_converted(n, m, s, d, graph, max_weight);

    auto start = chrono::high_resolution_clock::now();    

    double dist = dijkstra_dial(n, s, d, graph, max_weight);
    
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    
    cout << dist;

    cout << "\nElapsed time: " << elapsed.count() << " seconds\n";
    return 0;
}