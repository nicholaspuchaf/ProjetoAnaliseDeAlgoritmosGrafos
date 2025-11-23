#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <limits>
#include <numeric>
#include <cmath>
#include <algorithm>

#include <chrono>

using namespace std;

const int INF = numeric_limits<int>::max();

void create_graph_converted(int &n, int &m, int &s, int &d,
                            vector<vector<pair<int, int>>> &graph, int &max_weight) {
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

bool relax_dial(
    vector<int>& dist_A, 
    vector<deque<int>>& buckets_A, 
    const vector<int>& dist_B, 
    int& idx_A,
    int& min_dist,
    const vector<vector<pair<int, int>>>& graph,
    int max_weight) {
    
    
    while(buckets_A[idx_A].empty())
        idx_A = (idx_A+1) % (max_weight+1);
    
    auto t = buckets_A[idx_A].back();
    buckets_A[idx_A].pop_back();

    for(auto &k : graph[t]){
        if(dist_A[k.second] > dist_A[t] + k.first){
            dist_A[k.second] = dist_A[t] + k.first;
            int d = dist_A[k.second];
            buckets_A[d % (max_weight+1)].push_back(k.second);
        }
    }
    if(dist_B[t] != INF)
        min_dist = min(min_dist, dist_A[t] + dist_B[t]);
    return true;
}

int bidirectional_dijkstra_dial(int n, int source, int dest,
                                 const vector<vector<pair<int, int>>> &graph,
                                 int max_weight) {
    if (source == dest) return 0;

    // Estruturas para busca a partir do source
    vector<int> dist_f(n, INF);
    vector<deque<int>> buckets_f(max_weight + 1); 
    dist_f[source] = 0;
    buckets_f[0].push_back(source);

    // Estruturas para a busca a partir do destination
    vector<int> dist_b(n, INF);
    vector<deque<int>> buckets_b(max_weight + 1); 
    dist_b[dest] = 0;
    buckets_b[0].push_back(dest);
    
    int min_dist = INF; 
    int idx_f = 0;
    int idx_b = 0;

    // Alterna as buscas. O algoritmo para quando min_dist <= idx_f + idx_b.
    while (min_dist > idx_f + idx_b) {
        
        // Expande a busca que está na menor fronteira
        if (idx_f <= idx_b) {
            if (!relax_dial(dist_f, buckets_f, dist_b, idx_f, min_dist, graph, max_weight)) break;
        } else {
            if (!relax_dial(dist_b, buckets_b, dist_f, idx_b, min_dist, graph, max_weight)) break;
        }
    }

    return min_dist;
}

int main() {
    int n, m, s, d, max_weight;
    vector<vector<pair<int, int>>> graph;
    create_graph_converted(n, m, s, d, graph, max_weight);

    auto start = chrono::high_resolution_clock::now();

    int dist = bidirectional_dijkstra_dial(n, s, d, graph, max_weight);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << dist;
    cout << "\nElapsed time: " << elapsed.count() << " seconds\n";
    return 0;
}