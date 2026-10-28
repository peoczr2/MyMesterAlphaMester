/*
Megoldás lényege:
A felosztásokat csökkenő lexikografikus sorrendben számozzuk, az első az [N] felosztás.
Ha az első tag f, a maradék N-f szám f-nél nem nagyobb tagokból áll, ezek száma egy
partíciószámláló táblából (p(n,k): n olyan felbontása, amelyben minden tag legfeljebb k)
kiszámolható. Az I-edik felosztást az első tagtól lefelé haladva, a csoportok méreteinek
levonásával (unrankeléssel) állítjuk elő. Egy felosztás sorszámát (rangját) pozíciónként
számoljuk: összeadjuk, hány nagyobb következő tagú felosztás áll előtte. A következő felosztás
a rang+1, az előző a rang-1 sorszámú, ezért mindkettőt unrankeléssel kapjuk. Az időigény
és a memória O(N²), N ≤ 150 esetén ez messze az időlimit alatt marad.
*/
/*
Hint 1: || Csoportosítsd a felosztásokat az első tag szerint: ha az első tag f, a maradék N-f az f-nél nem nagyobb tagokból áll. A csoportok mérete előre kiszámolható, és az I-edik felosztás megkeresése a nagy első tagtól lefelé haladva a csoportok méreteinek levonásával történik. ||
Hint 2: || Legyen p(n,k) azon felbontások száma, amelyekben minden tag legfeljebb k. Ekkor p(0,k)=1, p(n,0)=0, ha n>0, és p(n,k) = p(n,k-1) + p(n-k,k): vagy nincs k-s tag a felbontásban, vagy van legalább egy. A tábla N ≤ 150 esetén 64 bites egész számba elfér, memoizálással O(N²) lépésben kitölthető. ||
Hint 3: || Egy felosztás rangját 1-től számoljuk ([N] a 1.), és minden pozíción összeadjuk, hány olyan felosztás van előtte, amely ugyanazt a prefixet adja, de ezen a helyen nagyobb tagot tartalmaz. A megadott felosztás rangja +1 és -1 szerinti felosztását ugyanazzal az unrank eljárással állítsd elő. ||
*/
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

int N;
vector<vector<ull>> memo;
vector<vector<char>> vis;

ull countPart(int rem, int mx) {
    if (rem == 0) return 1;
    if (mx == 0 || rem < 0) return 0;
    if (vis[rem][mx]) return memo[rem][mx];
    vis[rem][mx] = 1;
    ull ans = countPart(rem, mx - 1);
    if (rem >= mx) ans += countPart(rem - mx, mx);
    return memo[rem][mx] = ans;
}

vector<int> unrankPart(int rem, int mx, ull rank) {
    if (rem == 0) return {};
    for (int first = min(rem, mx); first >= 1; --first) {
        ull cnt = countPart(rem - first, first);
        if (rank > cnt) rank -= cnt;
        else {
            vector<int> tail = unrankPart(rem - first, first, rank);
            tail.insert(tail.begin(), first);
            return tail;
        }
    }
    return {};
}

ull rankPart(const vector<int>& a) {
    ull rank = 1;
    int rem = N, mx = N;
    for (int x : a) {
        for (int first = min(rem, mx); first > x; --first) {
            rank += countPart(rem - first, first);
        }
        rem -= x;
        mx = x;
    }
    return rank;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int I;
    cin >> N >> I;
    vector<int> part;
    int m;
    cin >> m;
    part.resize(m);
    for (int i = 0; i < m; ++i) cin >> part[i];

    memo.assign(N + 1, vector<ull>(N + 1));
    vis.assign(N + 1, vector<char>(N + 1, 0));

    ull Ibig = I;
    vector<int> kth = unrankPart(N, N, Ibig);
    ull r = rankPart(part);
    vector<int> next = unrankPart(N, N, r + 1);
    vector<int> prev = unrankPart(N, N, r - 1);

    for (int i = 0; i < (int)kth.size(); ++i) {
        if (i) cout << ' ';
        cout << kth[i];
    }
    cout << '\n';
    for (int i = 0; i < (int)next.size(); ++i) {
        if (i) cout << ' ';
        cout << next[i];
    }
    cout << '\n';
    for (int i = 0; i < (int)prev.size(); ++i) {
        if (i) cout << ' ';
        cout << prev[i];
    }
    cout << '\n';
    return 0;
}