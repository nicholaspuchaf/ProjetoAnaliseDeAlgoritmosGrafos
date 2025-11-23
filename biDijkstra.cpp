#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <limits>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <cmath>

#include <chrono>

using namespace std;

const double INF = numeric_limits<double>::infinity();

// Função para ler o grafo
void create_graph(int &n, int &m, int &s, int &d,
                  vector<vector<pair<double, int>>> &graph) {
    cin >> n >> m >> s >> d;
    graph.assign(n, vector<pair<double, int>>());

    for (int i = 0; i < m; i++) {
        int u, v;
        double w; 
        cin >> u >> v >> w;
        graph[u].push_back({w, v});
        graph[v].push_back({w, u});
    }
}

bool relax_dijkstra(
    vector<double>& dist_A, 
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>>& heap_A, 
    const vector<double>& dist_B, 
    const priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>>& heap_B,
    double& min_dist, 
    const vector<vector<pair<double, int>>>& graph) {
    
    auto t = heap_A.top();
    heap_A.pop();
    
    if(dist_A[t.second] < t.first)
        return true;
    
    for(auto &k : graph[t.second]){
        if(dist_A[k.second] > dist_A[t.second] + k.first){
            dist_A[k.second] = dist_A[t.second] + k.first;
            heap_A.push({dist_A[k.second], k.second});
        }
    }

    min_dist = min(min_dist, dist_A[t.second] + dist_B[t.second]);

    return true;
}

double dijkstra_bidirectional(int n, int source, int dest,
                              const vector<vector<pair<double, int>>> &graph) {
    if (source == dest) return 0.0;
    
    // Estruturas para busca a partir do source
    vector<double> dist_f(n, INF);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> heap_f;
    dist_f[source] = 0.0;
    heap_f.push({0.0, source});
    
    // Estruturas para a busca a partir do destination
    vector<double> dist_b(n, INF);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> heap_b;
    dist_b[dest] = 0.0;
    heap_b.push({0.0, dest});

    double min_dist = INF; 
    
    while (!heap_f.empty() && !heap_b.empty()) {
        if (min_dist <= heap_f.top().first + heap_b.top().first) {
            break; 
        }
        
        // relaxar heap com melhor prioridade
        if (heap_f.top().first < heap_b.top().first) {
             if (!relax_dijkstra(dist_f, heap_f, dist_b, heap_b, min_dist, graph)) break;
        } else {
             if (!relax_dijkstra(dist_b, heap_b, dist_f, heap_f, min_dist, graph)) break;
        }
    }

    return min_dist;
}

string format3(double x) {
    double r = round(x * 1000.0) / 1000.0;

    std::ostringstream out;
    out << std::fixed << std::setprecision(3) << r;

    std::string s = out.str();


    int zeros = 0;
    // remove zeros à direita
    while (s.back() == '0') 
    {
        s.pop_back();
        zeros++;
    }

    // se terminar com ponto, remove o ponto
    if (s.back() == '.')
        s.pop_back();
    else{
        while(zeros-- > 0)
            s.push_back('0');
    }
    return s;
}


int main() {
    int n, m, s, d;
    vector<vector<pair<double, int>>> graph;
    create_graph(n, m, s, d, graph);

    auto start = chrono::high_resolution_clock::now();

    double dist = dijkstra_bidirectional(n, s, d, graph);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << format3(dist);

    cout << "\nElapsed time: " << elapsed.count() << " seconds\n";
    
    return 0;
}