#pragma once
/*
Convex Hull Trick
- y = ax + b が順次追加されつつ，最大値/最小値クエリに答える
- y = c(x - a)^2 + b 型の関数を表す(a, b)たちが順次追加されつつ，最小値クエリに答える
Verify:
CF 1179D https://codeforces.com/contest/1179/submission/59448330
CF 1137E https://codeforces.com/contest/1137/submission/59448399
*/
#include <limits>
#include <set>
#include <utility>
#include <vector>
// CUT begin
// Convex Hull Trick
// Implementation Idea:
// https://github.com/satanic0258/Cpp_snippet/blob/master/src/technique/ConvexHullTrick.cpp
// #include <boost/multiprecision/cpp_int.hpp>
// using mpint = boost::multiprecision::cpp_int;
namespace CHT {
using T_CHT = long long;
static const T_CHT T_MIN = std::numeric_limits<T_CHT>::lowest() + 1;
struct Line {
    T_CHT a, b; // y = ax + b
    mutable std::pair<T_CHT, T_CHT>
        rp; // (numerator, denominator) `x` coordinate of the crossing point with next line
    Line(T_CHT a, T_CHT b) : a(a), b(b), rp(T_MIN, T_MIN) {}
    static std::pair<T_CHT, T_CHT> cross(const Line &ll, const Line &lr) {
        return std::make_pair(ll.b - lr.b, lr.a - ll.a); // `ll.a < lr.a` is assumed implicitly
    }
    bool operator<(const Line &r) const {
        if (b == T_MIN) {
            return r.rp.first == T_MIN ? true : a * r.rp.second < r.rp.first;
        } else if (r.b == T_MIN) {
            return rp.first == T_MIN ? false : !(r.a * rp.second < rp.first);
        } else {
            return a < r.a;
        }
    }
};
template <typename T_MP> struct Lines : std::multiset<Line> {
    bool flg_min; // true iff for minimization
    inline bool isNeedless(iterator itr) {
        if (size() == 1) return false;
        auto nxt = std::next(itr);
        if (itr == begin())
            return itr->a == nxt->a and itr->b <= nxt->b;
        else {
            auto prv = std::prev(itr);
            if (nxt == end())
                return itr->a == prv->a and itr->b <= prv->b;
            else
                return T_MP(prv->b - itr->b) * (nxt->a - itr->a) >=
                       T_MP(itr->b - nxt->b) * (itr->a - prv->a);
        }
    }
    void add_line(T_CHT a, T_CHT b) {
        if (flg_min) a = -a, b = -b;
        auto itr = insert({a, b});
        if (isNeedless(itr))
            erase(itr);
        else {
            while (std::next(itr) != end() and isNeedless(std::next(itr))) {
                erase(std::next(itr));
            }
            while (itr != begin() and isNeedless(std::prev(itr))) { erase(std::prev(itr)); }
            if (std::next(itr) != end()) { itr->rp = CHT::Line::cross(*itr, *std::next(itr)); }
            if (itr != begin()) { std::prev(itr)->rp = CHT::Line::cross(*std::prev(itr), *itr); }
        }
    }
    Lines(bool is_minimizer) : flg_min(is_minimizer) {}
    std::pair<T_CHT, T_CHT> get(T_CHT x) {
        auto itr = lower_bound({x, CHT::T_MIN});
        T_CHT retval = CHT::T_MIN, reta = CHT::T_MIN;
        if (itr != end()) { retval = itr->a * x + itr->b, reta = itr->a; }
        if (itr != begin()) {
            T_CHT tmp = std::prev(itr)->a * x + std::prev(itr)->b;
            if (tmp >= retval) { retval = tmp, reta = std::max(reta, std::prev(itr)->a); }
        }
        return std::make_pair(flg_min ? -retval : retval, flg_min ? -reta : reta);
    }
};
} // namespace CHT

template <typename T_MP> struct ConvexHullTrick {
    using T_CHT = CHT::T_CHT;
    CHT::Lines<T_MP> lines;
    ConvexHullTrick(bool is_minimizer) : lines(is_minimizer) {}
    void add_line(T_CHT a, T_CHT b) { lines.add_line(a, b); } // Add y = ax + b
    std::pair<T_CHT, T_CHT> get(T_CHT x) { return lines.get(x); }
    void add_convex_parabola(T_CHT c, T_CHT a, T_CHT b) {
        add_line(c * a * (-2), c * a * a + b);
    } // Add y = c(x - a)^2 + b
    T_CHT parabola_lower_bound(T_CHT c, T_CHT x) { return lines.get(x).first + c * x * x; }
};
