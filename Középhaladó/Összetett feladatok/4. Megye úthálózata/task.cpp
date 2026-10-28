/*
Megoldás lényege:
A távolságmátrix i. sorának nem nulla elemei adják az i. település közvetlen szomszédait. Zsákfalu az, amelynek pontosan egy szomszédja van, a T-nél közelebbi szomszédok számát pedig egyszerű megszámlálással kapjuk. A legelszigeteltebb települést a szomszédok átlagos távolsága alapján keressük: az átlagot törtként kezeljük és szorzással hasonlítjuk össze, így nincs lebegőpontos hiba, döntetlennél a kisebb sorszám marad. A legközelebbi szomszéd minimumkeresés (döntetlennél a kisebb j), a (i,j) párt pedig akkor írjuk ki, ha nem az a fordított (j,i) pár, amely már kiíródott. A zsákfalvakból indulva követjük az utat: amíg a település pontosan két úttal kapcsolódik, a másik szomszédjára lépünk, és az első elágazó vagy újabb zsákfalu is beleszámít. Az összidő O(N^2), ami N <= 1000 mellett bőven belefér.
*/
/*
Hint 1: || A zsákfalvak és a közelebbi szomszédok száma a távolságmátrix soraiból közvetlenül adódik: egy sorban a nem nulla elemek a közvetlen utak. ||
Hint 2: || A 4. részfeladatnál minden településhez keress legkisebb távolságú szomszédot, és a párt akkor hagyd ki, ha a fordított pár már szerepelt (a kisebb sorszámú elem a kezdőpont). Az 5. részfeladatban zsákfaluból indulva lépkedj, és minden megállt települést is számold bele. ||
Hint 3: || Az átlag összehasonlítása egész számokkal: a/b > c/d helyett a·d > c·b, így nincs lebegőpontos pontatlanság. Az összegek 64 bites egészben férnek el. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t;
    cin >> n >> t;

    vector<vector<int>> d(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            cin >> d[i][j];
            if (d[i][j] > 0) adj[i].push_back(j);
        }

    // 1. részfeladat: a zsákfalvak száma
    int deadEnds = 0;
    for (int i = 1; i <= n; ++i)
        if (adj[i].size() == 1) ++deadEnds;
    cout << "#\n" << deadEnds << "\n";

    // 2. részfeladat: T-nél közelebbi közvetlen szomszédok száma
    cout << "#\n";
    for (int i = 1; i <= n; ++i) {
        int c = 0;
        for (int j : adj[i])
            if (d[i][j] < t) ++c;
        cout << c << (i < n ? " " : "\n");
    }

    // 3. részfeladat: a legelszigeteltebb település (átlagos szomszédtávolság maximuma)
    int isolated = 0;
    long long bestSum = 0, bestCnt = 1;
    for (int i = 1; i <= n; ++i) {
        if (adj[i].empty()) continue;
        long long sum = 0;
        for (int j : adj[i]) sum += d[i][j];
        long long cnt = (long long)adj[i].size();
        if (isolated == 0 || sum * bestCnt > bestSum * cnt) {
            isolated = i;
            bestSum = sum;
            bestCnt = cnt;
        }
    }
    cout << "#\n" << isolated << "\n";

    // 4. részfeladat: minden településhez a legközelebbi szomszéd
    vector<int> nearest(n + 1, 0);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (d[i][j] > 0 && (nearest[i] == 0 || d[i][j] < d[i][nearest[i]]))
                nearest[i] = j;

    cout << "#\n";
    for (int i = 1; i <= n; ++i) {
        int j = nearest[i];
        if (j == 0) continue;
        if (j < i && nearest[j] == i) continue;  // a (j,i) pár már kiíródott
        cout << i << " " << j << "\n";
    }

    // 5. részfeladat: zsákfalunként az elágazás nélkül elérhető települések száma
    cout << "#\n";
    bool firstOut = true;
    for (int s = 1; s <= n; ++s) {
        if (adj[s].size() != 1) continue;
        int prev = s, cur = adj[s][0], steps = 0;
        while (true) {
            ++steps;
            if (adj[cur].size() != 2 || steps > n) break;
            int nxt = (adj[cur][0] == prev) ? adj[cur][1] : adj[cur][0];
            prev = cur;
            cur = nxt;
        }
        cout << (firstOut ? "" : " ") << steps;
        firstOut = false;
    }
    cout << "\n";

    return 0;
}
