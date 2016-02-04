// TCR
// (Generalised) Chinese remainder theorem (for arbitrary moduli):
// Solves x from system of equations x == a_i (mod m_i), giving answer modulo m = lcm(m_1,...,m_n)
// Runs in O(log(m)+n) time
// Overflows only if m overflows
// Returns {1, {x, m}} if solution exists, and {-1, {0,0}} otherwise
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;
typedef __int128 lll;

ll ee(ll a, ll b, ll ca, ll cb, ll xa, ll xb, ll&x, ll&y) {
    if (cb==0) {
        x=xa;
        if (b==0) y=0;
        else y=(ca-a*xa)/b;
        return ca;
    }
    else return ee(a, b, cb, ca%cb, xb, xa-(ca/cb)*xb, x, y);
}

pair<int, pair<ll, ll>> crt(vector<ll> as, vector<ll> ms) {
    ll aa = as[0]%ms[0], mm = ms[0], d, a, b, x;
    for (int i = 1; i < (int) as.size(); i++) {
        d = __gcd(mm, ms[i]);
        if ((aa-as[i])%d != 0) return {-1,{0,0}};
        if (d == ms[i]) continue;
        a = mm/d;
        b = ms[i]/d;
        ee(a, b, a, b, 1, 0, x, b);
        mm = a*(lll)ms[i];
        aa = ((lll)aa + ((lll)as[i]-(lll)aa)*(lll)(((lll)a*(lll)(x%mm))%mm))%mm;
    }
    if (aa < 0) aa += mm;
    return {1, {aa, mm}};
}
