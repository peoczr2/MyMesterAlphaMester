/*
Feladat: M segélyadó ország van, az i-edik C_i csomagot küld, de csak az 1..E_i országokba. Osszuk el a csomagokat úgy, hogy a kapott csomagok maximuma és minimuma közti különbség minimális legyen.
Ötlet: Bináris keresés a D különbségre. Egy fix D-re azt vizsgáljuk, létezik-e olyan L minimum, hogy minden ország [L, L+D] intervallumban kapjon.
Prefix-korlát: jelölje P(t) az összes olyan donor csomagját, amelynek E_i <= t. Ezek a csomagok kötelezően az első t országba mennek, tehát S_t >= P(t), ahol S_t az első t ország összes kapott csomagja.
Ha minden ország [L, L+D]-ben kap, akkor:
  - S_t <= t*(L+D)
  - S_t >= t*L
  - S_t >= P(t)
  - a suffix legalább L-et kapjon: C-P(t) >= (N-t)*L (t < N)
Ezekből L-re alsó/felső korlátok adódnak; ha metszetük nem üres, D megvalósítható.
Hint 1: || A donorok prefix-korlátot adnak: az E_i-ig elérő csomagokat nem lehet későbbi országokba küldeni. ||
Hint 2: || Fix D mellett az ismeretlen L-re írj fel minden szükséges korlátot. ||
Hint 3: || A minimális D bináris kereséssel található meg. ||
*/

#include <bits/stdc++.h>
using namespace std;

static long long floor_div(long long a, long long b) {
    // b > 0
    if (a >= 0) return a / b;
    return - ((-a + b - 1) / b);
}

static long long ceil_div(long long a, long long b) {
    // b > 0
    if (a >= 0) return (a + b - 1) / b;
    return - ((-a) / b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long N;
    int M;
    cin >> N >> M;

    vector<pair<int,long long>> v;
    v.reserve(M);
    long long C = 0;
    for (int i = 0; i < M; ++i) {
        long long c;
        int e;
        cin >> c >> e;
        v.push_back({e, c});
        C += c;
    }

    sort(v.begin(), v.end());

    // Kandidát t pontok P(t) értékkel: szegmenskezdők + eseménypontok.
    vector<pair<long long,long long>> cand; // (t, P_t)
    long long prev = 0;
    long long pref = 0;
    for (int i = 0; i < M;) {
        int e = v[i].first;

        if (prev + 1 <= e - 1) {
            cand.push_back({prev + 1, pref});
        }

        while (i < M && v[i].first == e) {
            pref += v[i].second;
            ++i;
        }

        cand.push_back({e, pref});
        prev = e;
    }
    if (prev < N) {
        cand.push_back({prev + 1, pref});
    }

    auto feasible = [&](long long D) -> bool {
        long long lo = ceil_div(C - N * D, N);
        long long hi = floor_div(C, N);

        for (auto [t, Pt] : cand) {
            lo = max(lo, ceil_div(Pt - t * D, t));
            if (t < N) {
                hi = min(hi, floor_div(C - Pt, N - t));
            }
            if (lo > hi) return false;
        }

        return lo <= hi;
    };

    long long lo = 0, hi = C;
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        if (feasible(mid)) hi = mid;
        else lo = mid + 1;
    }

    cout << lo << '\n';
    return 0;
}
