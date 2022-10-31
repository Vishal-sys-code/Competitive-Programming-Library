/*
Author: tmleyncodes

नैनं छिद्रन्ति शस्त्राणि नैनं दहति पावक: ।
न चैनं क्लेदयन्त्यापो न शोषयति मारुत ॥
*/

#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

#pragma gcc optiminize("Ofast")
#pragma gcc target("fma,sse,sse2,sse3,ssse3,sse4,popcur,abm,mmaxi,avx,avx2,tune=native")
#pragma gcc optiminize("unroll-loops")
#pragma GCC target("fpmath=sse,sse2")
#pragma comment(linker, "/STACK: 20000000")

#define pb push_back
unordered_map<char, int> mp;
#define lpr pair<long long int,long long int>
#define mod 1000000007
#define S second
#define SS string
#define F first
#define ff front
#define bb back
#define nl endl
#define all(z)              (z).begin(), (z).end()
#define ll                  long long
#define fi(n)               for(int i=0;i<n;i++)
#define fj(n)               for(int j=0;j<n;j++)
#define fk(n)               for(int k=0;k<n;k++)
#define setp(x)             fixed<<setprecision(x)
#define rep(i,a,b)          for(int i=a;i<b;i++)
#define repi(i,a,b)         for(int i=a;i>=b;i--)
#define repe(i,a,b)          for(int i=a;i<=b;i++)
#define repel(i,a,b)         for(ll i=a;i<=b;i++)
#define mem(a,b)            memset(a,b,sizeof(a))
#define endl                "\n"
#define yes                 cout<<"Yes\n";
#define no                  cout<<"No\n";
#define uniq(v)             v.erase(unique(v.begin(),v.end()),v.end())
#define coutar(array,size)  fi(size) cout<<array[i]<<" "; cout<<"\n";
#define dbg(dt)             cout<<#dt<<": "<<dt<<"\n";
#define dnp(dt)             cout<<#dt<<": "<<dt;
#define db2(dt)             cout<<#dt<<":"<<"\n"<<dt;
#define bo bool

// INPUTS
#define read1(a) cin>>a
#define read2(a,b) cin>>a>>b
#define read3(a,b,c) cin>>a>>b>>c
#define read4(a,b,c,d) cin>>a>>b>>c>>d
#define reads(s) string s; cin>>s;

// OUTPUTS
#define print1(a) cout<<a
#define print2(a,b) cout<<a<<b
#define print3(a,b,c) cout<<a<<b<<c

#define en cout<< endl
const ll maxn = 2e5 + 5;

typedef bitset<21> bit;            int mod99 = 998244353;
typedef long double ld;            const ld pi = 3.141592653589;               const int mod10 = 1000000007;     const ld INF = 5e18;
typedef pair<int, int> pii;        typedef vector<int> vi;                   typedef vector<pii> vpii;       typedef vector<vi> vvi;
typedef set<int> si;               typedef set<pii> spi;                     typedef multiset<int> msl;      typedef vector<string> vs;
mt19937 sansy (chrono::high_resolution_clock::now().time_since_epoch().count());
template <typename A, typename B> ostream& operator<<(ostream &ostr, const pair<A, B> &pp) {return ostr << '{' << pp.first << ", " << pp.second << '}';}
template < typename T_container, typename T = typename enable_if < !is_same<T_container, string>::value, typename T_container::value_type >::type > ostream & operator<<(ostream &ostr, const T_container &vec)
{ for (const T &vv : vec) ostr << vv << " "; return ostr << endl;  }
template <typename A> ostream& operator<< (ostream &ostr, vector<A> const &v) { fi(v.size()) {cout << v[i] << " ";} return cout << "\n";}
template <typename A, typename B> istream& operator>> (istream& cin, pair<A, B> &p) {cin >> p.first; return cin >> p.second;}
template <typename A> istream& operator>> (istream& cin, vector<A> &vv) { fi(vv.size() - 1) cin >> vv[i]; return cin >> vv[vv.size() - 1];}
vi primes, fibonacci;        int xorccur(int n);
bool isPrime(int n);        void sieve(int N);
int lcm(int a, int b);       int poww(int n, int k);
int nCr(int n, int r);       int leap(int y);
void fiboseries(int n);     int fiboN(int n);
bool isvowel(char c) { c = tolower(c); if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') return 1; else return 0;}
int modInverse(int a, int m);
string baseto10(string s, int b);
string basefrom10(string s, int b);
int popcount(int n) {  int val = 0;  while (n) {  val += n & 1; n >>= 1; } return val;}
bool ispow2 (int n) {return n and  (!(n & (n - 1)));}
ld dis_p(int nice, int y1, int x2, int y2);
string subtractstring(string temp, string a2);
int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int dy[8] = {0, 1, 1, 0, -1, -1, 1, -1}, dx[8] = {1, 0, 1, -1, 0, -1, -1, 1};
string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "Falsevember", "December"};
#define NOBITA 200001
#define MAX 1e5

// For the fast input and outputs in cpp
void Fast_IO() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

// IMPORTANT FUNCTIONS

bool isPrime(int n) {
    if (n < 2)               return 0;
    if (n < 4)               return 1;
    if (!(n % 2) || !(n % 3))   return 0;
    for (int i = 5; i * i <= n; i += 6)
        if (!(n % i) || !(n % (i + 2)))
            return 0;
    return 1;
}
void sieve(int N) {
    vi vv(N + 1);
    for (int i = 2; i <= N; i++) {
        if (!vv[i])
            vv[i] = i, primes.push_back(i);
        for (int j = 0; j < primes.size() and  primes[j] <= vv[i] and  i * primes[j] <= N; j++)
            vv[i * primes[j]] = primes[j];
    }
}
ld dis_p(int nice, int y1, int x2, int y2)    {
    ld distance = sqrt(((nice - y1) * (nice - y1) + (x2 - y2) * (x2 - y2) * 1.00));
    return distance;
}
int lcm(int a, int b) {
    return ((a * b) / __gcd(a, b));
}
int poww(int n, int k)   {
    int x = 1;
    while (k)   {
        if (k & 1)
        { x *= n; x %= mod10; }
        n *= n;
        n %= mod10;
        k >>= 1;
    }
    return x;
}   //multi n^k
ll power(ll b, ll n) {
    ll s = 1;
    while (n) {
        if (n % 2 == 1)s = s * b % mod99;
        b = b * b % mod99;
        n /= 2;
    }
    return s;
}
int nCr(int n, int r)   { // n C r coeresicient
    if (r > n) return 0;
    if (r > n - r) r = n - r;
    int calc = 1;
    for (int i = 1; i <= r; i++) {
        calc *= (n - r + i);
        calc /= i;
        calc %= mod10;
    }
    return calc % mod10;;
}
int MOD = 1000000007 ;
int SIZE = 500002;
vector<long> fact;
void factorial() {
    int i;
    fact.push_back((long)1);
    for (i = 1; i <= SIZE; i++) {
        fact.push_back((fact[i - 1] * i) % MOD);
    }
}
unsigned long long factorial(int N) {
    unsigned long long  f = 1; // Or BigInt 1
    for (unsigned long long  i = 2; i <= N; i++)
        f *= i;
    return f;
}
int modInverse(int a, int m)  {
    if (m == 1)
        return 0; //edge case
    int initialmod = m, y = 0, x = 1;
    while (a > 1)   {
        //changing (A,B)--> (B, A%B) till a>1
        int q = a / m; // q is quotient
        int t = m;
        m = a % m; // m->remainder(from q)
        a = t;  // process same as
        t = y;  // Euclid's algo
        y = x - q * y;
        x = t; // Update y and  x
    }   //ax + bm = 1 (gcd(a,m)==1 (coprime))
    if (x < 0)
        x += initialmod;
    return x;
}
int coprime(int a, int b) {
    if (__gcd(a, b) == 1) return 1;
    return 0;
}
void fiboseries(int n)  {
    fibonacci.push_back(0);     fibonacci.push_back(1);
    int nu = 0, c2 = 1;  int c3 = nu + c2;
    while (c2 < n) {
        c3 = nu + c2;   nu = c2;      c2 |= c3;
        fibonacci.push_back(c3);
    }// Series upto N
}
ll count(ll i, ll j) {
    return ((i / (1 << (j + 1))) << j) + (max(0ll, i % (1 << (j + 1)) - (1 << j) + 1));
}
int fiboN(int n)    {
    //For DIRECTLY Nth TERM: Fn = ((1+sq(5))^n - (1-sq(5))^n)/pow(2^n).sq(5)
    if (n <= 1) return n;
    return fiboN(n - 1) + fiboN(n - 2);
}   // n as posing starts from 0
string baseto10(string s, int b) {
    int num = 0;
    fi(s.size()) {
        if (isdigit(s[i]))
            num = num * b + (s[i] - '0');
        else
            num = num * b + (s[i] - 'A' + 10);
    }
    return to_string(num);
}
string basefrom10(string s, int b) {
    string num;
    int n = stoll(s);
    while (n) {
        int x = n % b;  n /= b;
        if (x < 10)
            num += char('0' + x);
        else
            num += char('A' + x - 10);
    }
    reverse(all(num));
    return num;
}
bool isSquare(int x) {
    int y = sqrt(x);
    return y * y == x;
}
string subtractstring(string temp, string a2) {
    string cal = "";    //temp>=a2 (assumption)
    int n = temp.size(), m = a2.size(), antar = n - m, left = 0;
    for (int i = m - 1; i > -1; --i) {
        int cursub = (temp[i + antar] - '0') - (a2[i] - '0') - left;
        if (cursub >= 0)  left = 0;
        else cursub += 10, left = 1;
        cal.push_back(cursub + '0');
    }
    for (int i = n - m - 1; i > -1; --i) { // subtract remaining digits of temp[]
        if (temp[i] == '0' and left != 0) {
            cal.push_back('9');
            continue;
        }
        int cursub = (temp[i] - '0') - left;    left = 0;
        if (i || cursub)    cal.push_back(cursub + '0');
    }
    reverse(all(cal));
    return cal;
}
int leap(int y) {
    if (y % 400 == 0)         return 1;
    else if (y % 100 == 0)    return 0;
    else if (y % 4 == 0)      return 1;
    else                    return 0;
}
int xorccur(int n) {
    if (n % 4 == 0)             return n; //0,4,8,12
    else if (n % 4 == 1)        return 1; //1,5,9
    else if (n % 4 == 2)        return n; //2,6,10
    return 0;
}
bool isPalindrome(int arr[], int n) {
    bool check = false;
    for (int i = 0; i <= n / 2 and n != 0 ; ++i) {
        if (arr[i] != arr[n - i - 1]) {
            return false;
        }
    }
    return true;
}

string rev(string s) {
    int n = s.length();
    string ans;
    for (int i = n - 1; i >= 0; i--) {
        ans.push_back(s[i]);
    }
    return ans;
}


void solution() {

}


int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("o.txt", "w", stdout);
#endif
    Fast_IO();
    // int tt = 1; // for 1 test case
    int tt; read1(tt);
    while (tt--) {
        solution();
        // solve();
        // solve2();
    }
    // solution();
    return 0;
}