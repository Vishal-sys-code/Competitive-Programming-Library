// パス上の頂点更新・パス上の頂点積取得が可能な Link-Cut tree
// 各頂点に 2x2 行列を載せ，演算として行列積が入る非可換・パス上更新の例．
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A" // DUMMY
#include "../link_cut_tree.hpp"
#include "../../linear_algebra_matrix/matrix.hpp"
#include "../../modint.hpp"
#include "../../random/xorshift.hpp"

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <unordered_set>
#include <utility>
using namespace std;

constexpr int md = 998244353;
const int NTRY = 1000;
const int VMAX = 50;
const int QPERTRY = 1000;
const int dim = 2;
using mint = ModInt<md>;

using S = tuple<int, matrix<mint>, matrix<mint>>;
using F = pair<bool, matrix<mint>>;
S op(S l, S r) {
    int sl, sr;
    matrix<mint> ml1, ml2, mr1, mr2;
    tie(sl, ml1, ml2) = l;
    tie(sr, mr1, mr2) = r;
    return {sl + sr, mr1 * ml1, ml2 * mr2};
}
S mapping(F f, S x) {
    int sz = get<0>(x);
    if (sz) {
        auto m = f.second.pow(sz);
        return {sz, m, m};
    }
    return x;
}
S reversal(S x) { return {get<0>(x), get<2>(x), get<1>(x)}; }
F composition(F f, F g) { return f.first ? f : g; }
F id() { return {false, matrix<mint>::Identity(dim)}; }
using LCT = lazy_linkcuttree<S, F, op, reversal, mapping, composition, id>;

vector<int> connected_vertices(int N, int r, const vector<unordered_set<int>> &to) {
    vector<int> visited(N);
    vector<int> ret, tmp{r};
    while (tmp.size()) {
        int now = tmp.back();
        tmp.pop_back();
        ret.push_back(now);
        visited[now] = 1;
        for (auto nxt : to[now]) {
            if (!visited[nxt]) tmp.push_back(nxt);
        }
    }
    return ret;
}

vector<int> get_rev_path(int s, int t, int prv, const vector<unordered_set<int>> &to) {
    if (s == t) return {s};
    for (auto nxt : to[s]) {
        if (nxt == prv) continue;
        auto v = get_rev_path(nxt, t, s, to);
        if (v.size()) {
            v.push_back(s);
            return v;
        }
    }
    return {};
}

S gen_rand_a() {
    matrix<mint> ret(dim, dim);
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) ret[i][j] = rand_int() % md;
    }
    return {1, ret, ret};
}

int main() {
    for (int ntry = 0; ntry < NTRY; ntry++) {
        const int N = 2 + rand_int() % (VMAX - 1);

        vector<S> A(N);
        LCT tree;
        vector<LCT::Node *> nodes;

        for (int i = 0; i < N; i++) {
            A[i] = gen_rand_a();
            nodes.push_back(tree.make_node(A[i]));
        }
        vector<pair<int, int>> edges;
        vector<unordered_set<int>> to(N);

        auto try_to_add_edge = [&]() {
            int a = rand_int() % N;
            vector<int> is_cmp(N, 1);
            for (auto i : connected_vertices(N, a, to)) is_cmp[i] = 0;
            vector<int> cmp;
            for (int i = 0; i < N; i++) {
                if (is_cmp[i]) cmp.push_back(i);
            }
            if (cmp.empty()) return;
            int b = cmp[rand_int() % cmp.size()];

            edges.emplace_back(a, b);
            to[a].insert(b), to[b].insert(a);
            tree.link(nodes[a], nodes[b]);
        };

        for (int i = 0; i < N / 2; i++) try_to_add_edge();

        for (int q = 0; q < QPERTRY; q++) {
            const int tp = rand_int() % 6;
            if (tp == 0) {
                // cut() if possible
                if (edges.empty()) continue;
                int e = rand_int() % edges.size();
                int a = edges[e].first, b = edges[e].second;

                edges.erase(edges.begin() + e);
                to[a].erase(b), to[b].erase(a);
                tree.cut(nodes[a], nodes[b]);

            } else if (tp == 1) {
                // link() if possible
                try_to_add_edge();

            } else if (tp == 2) {
                // apply()
                const int u = rand_int() % N;
                auto conn = connected_vertices(N, u, to);
                int v = conn[rand_int() % conn.size()];
                const auto a = gen_rand_a();
                tree.apply(nodes[u], nodes[v], {true, get<1>(a)});

                for (auto i : get_rev_path(u, v, -1, to)) A[i] = a;

            } else if (tp == 3) {
                // prod()
                const int u = rand_int() % N;
                auto conn = connected_vertices(N, u, to);
                int v = conn[rand_int() % conn.size()];
                S ret1 = tree.prod(nodes[u], nodes[v]);

                auto ret2 = S(A[u]);
                for (auto i : get_rev_path(v, u, -1, to)) {
                    if (i != u) ret2 = op(ret2, A[i]);
                }
                assert(ret1 == ret2);

            } else if (tp == 4) {
                // set()
                const int u = rand_int() % N;
                const auto a = gen_rand_a();
                tree.set(nodes[u], a);
                A[u] = a;

            } else if (tp == 5) {
                // get()
                const int u = rand_int() % N;
                const S a = tree.get(nodes[u]);
                assert(a == A[u]);
            } else {
                exit(8);
            }
        }
    }
    puts("Hello World");
}
