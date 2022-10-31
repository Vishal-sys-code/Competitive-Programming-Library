#pragma once
#include "../acl_beats.hpp"

// CUT begin
// Verified: https://yukicoder.me/submissions/611774
namespace yuki880 {
constexpr uint32_t BINF = 1 << 30;

struct S {
    uint32_t max;
    uint32_t lcm;
    uint32_t sz;
    uint64_t sum;
    bool fail;
    bool all_same;
    S() : max(0), lcm(1), sz(1), sum(0), fail(0), all_same(0) {}
    S(uint32_t x, uint32_t sz_ = 1)
        : max(x), lcm(x), sz(sz_), sum((uint64_t)x * sz_), fail(0), all_same(1) {}
};

S e() { return S(); }

S op(S l, S r) {
    if (r.sz == 0) return l;
    if (l.sz == 0) return r;
    S ret;
    ret.max = std::max(l.max, r.max);
    ret.sum = l.sum + r.sum;
    ret.lcm = (l.lcm >= BINF or r.lcm >= BINF)
                  ? BINF
                  : std::min<uint64_t>(BINF, (uint64_t)l.lcm * r.lcm / std::__gcd(l.lcm, r.lcm));
    ret.sz = l.sz + r.sz;
    if (l.all_same and r.all_same and l.max == r.max) ret.all_same = true;
    return ret;
}

struct F {
    uint32_t dogcd, reset;
    F() : dogcd(0), reset(0) {}
    F(uint32_t g, uint32_t upd) : dogcd(g), reset(upd) {}
    static F gcd(uint32_t g) noexcept { return F(g, 0); }
    static F update(uint32_t a) noexcept { return F(0, a); }
};

F composition(F fnew, F fold) {
    return fnew.reset ? fnew : F(std::__gcd(fnew.dogcd, fold.dogcd), fold.reset);
}

F id() { return F(); }

S mapping(F f, S x) {
    if (x.fail) return x;
    if (f.reset) x = S(f.reset, x.sz);
    if (f.dogcd) {
        if (x.all_same)
            x = S(std::__gcd(f.dogcd, x.max), x.sz);
        else if (f.dogcd and (x.lcm == BINF or f.dogcd % x.lcm))
            x.fail = true;
    }
    return x;
}
using segtree = segtree_beats<S, op, e, F, mapping, composition, id>;
} // namespace yuki880
