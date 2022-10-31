#include "../bipartite_matching(slow).hpp"
#include <iostream>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A"

int main() {
    std::cin.tie(nullptr), std::ios::sync_with_stdio(false);

    int X, Y, E;
    std::cin >> X >> Y >> E;
    BipartiteMatching graph(X + Y);
    while (E--) {
        int s, t;
        std::cin >> s >> t;
        graph.add_edge(s, X + t);
    }
    std::cout << graph.solve() << '\n';
}
