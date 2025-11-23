#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <limits>
#include <numeric>
#include <iomanip>
#include <cmath>

#include <chrono>

using namespace std;

// Função para ler o grafo do arquivo e trasnformar em uma lista de adjacência
void create_graph(int &n, int &m, int &s, int &d, vector<vector<pair<double,int>>> &graph) {
    cin >> n >> m >> s >> d;
    graph.assign(n, vector<pair<double,int>>());

    for (int i = 0; i < m; i++) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        graph[u].push_back({w, v});
        graph[v].push_back({w, u});
    }
}

double dijkstra(int n, int source, int dest, const vector<vector<pair<double,int>>> &graph) {

    vector<double> dist(n, numeric_limits<double>::infinity());
    dist[source] = 0.0;

    priority_queue<pair<double,int>, vector<pair<double,int>>, greater<pair<double,int>>> minpq;
    minpq.push(pair<double,int>(dist[source], source));

    while(!minpq.empty()){
        auto t = minpq.top();
        minpq.pop();

        if(dist[t.second] < t.first)
            continue;

        for(auto &k : graph[t.second]){

            if(dist[k.second] > dist[t.second] + k.first){
                dist[k.second] = dist[t.second] + k.first;
                minpq.push({dist[k.second], k.second});
            }
        }
    }

    return dist[dest];
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
    vector<vector<pair<double,int>>> graph;
    create_graph(n, m, s, d, graph);

    auto start = chrono::high_resolution_clock::now();    

    double dist = dijkstra(n, s, d, graph);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << format3(dist);
    cout << "\nElapsed time: " << elapsed.count() << " seconds\n";

    return 0;
}