#include "../shortest_path.hpp"
#include "../../data_structure/radix_heap.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"
using namespace std;

int main() {
    int N, M, s, t;
    cin >> N >> M >> s >> t;
    constexpr long long INF = 1LL << 60;
    shortest_path<long long, INF> graph(N);
    while (M--) {
        int a, b, c;
        cin >> a >> b >> c;
        graph.add_edge(a, b, c);
    }

    graph.dijkstra<radix_heap<unsigned long long, int>>(s, t);
    auto d_radix = graph.dist;

    graph.solve(s);
    assert(graph.dist[t] == d_radix[t]);

    if (graph.dist[t] == INF) {
        cout << "-1\n";
        return 0;
    }

    vector<int> path;
    int now = t;
    while (true) {
        path.push_back(now);
        if (now == s) break;
        now = graph.prev[now];
    }
    std::reverse(path.begin(), path.end());
    cout << graph.dist[t] << ' ' << path.size() - 1 << '\n';
    for (unsigned i = 0; i + 1 < path.size(); i++) cout << path[i] << ' ' << path[i + 1] << '\n';
}
