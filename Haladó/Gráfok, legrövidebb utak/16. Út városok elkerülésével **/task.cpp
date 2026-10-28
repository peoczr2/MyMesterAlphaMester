/*
Megoldás lényege:
Az útvonal költsége a bejárt városok közül az elkerülendőek száma, ezért minden csúcs súlya 1, ha elkerülendő, különben 0; az élek súlya nincs. Dijkstra-algoritmussal keressük A-ból B felé a legkevesebb elkerülendő várost tartalmazó utat, és másodlagosan a legkevesebb várost, így a kiírt R is a lehető legkisebb az optimális utak közül. A két mennyiséget egy 64 bites kulcsba csomagoljuk (elkerülendő · 2^20 + városok), a szülő tömbből B-től visszafelé rakjuk ki az útvonalat. Az időigény O((N + M) log N), ami a 10 000 csúcsú, 200 000 élű gráfon a 0,1 mp-es időlimit alatt van.
*/
/*
Hint 1: || Az út költsége nem az élekből, hanem a bejárt városokból adódik: egy elkerülendő város 1-et ér, a többi 0-t. Így a feladat legkisebb költségű A-B út keresése súlyozott gráfon, ahol a csúcsok súlyai nemnegatívak. ||
Hint 2: || Dijkstra-algoritmussal számolj, de a távolságot két szempont szerint rendezd: először az elkerülendő városok száma, másodszor az útba eső városok száma. Ezt egyetlen számba csomagolhatod, például elkerülendő · 2^20 + városok. ||
Hint 3: || A szülő tömbbel B-ből visszafelé haladva kapod meg az útvonalat, majd megfordítod. A második sorba pontosan annyi szám kerül, amennyi a városok száma az első sorban. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Beolvasás pufferelt módon; a nem számjegy karaktereket (pl. CRLF, nem törő szóköz) kihagyja.
static char ibuf[1 << 16];
static int ilen = 0, ipos = 0;

int gc() {
    if (ipos == ilen) {
        ilen = (int)fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen <= 0) return -1;
    }
    return ibuf[ipos++];
}

long long readInt() {
    int c = gc();
    while (c != -1 && c != '-' && (c < '0' || c > '9')) c = gc();
    bool neg = false;
    if (c == '-') {
        neg = true;
        c = gc();
    }
    long long x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return neg ? -x : x;
}

int main() {
    int N = (int)readInt(), M = (int)readInt(), K = (int)readInt();
    int A = (int)readInt() - 1, B = (int)readInt() - 1;

    vector<char> avoid(N, 0);
    for (int i = 0; i < K; i++) avoid[(int)readInt() - 1] = 1;

    vector<vector<int>> adj(N);
    for (int i = 0; i < M; i++) {
        int u = (int)readInt() - 1, v = (int)readInt() - 1;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Kulcs: elkerülendő városok száma * SH + városok száma (a városok száma kisebb, mint SH).
    const long long SH = 1LL << 20;
    const long long INF = LLONG_MAX;
    vector<long long> dist(N, INF);
    vector<int> parent(N, -1);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    dist[A] = (long long)avoid[A] * SH + 1;
    pq.push({dist[A], A});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        if (u == B) break;
        for (int v : adj[u]) {
            long long nd = d + (long long)avoid[v] * SH + 1;
            if (nd < dist[v]) {
                dist[v] = nd;
                parent[v] = u;
                pq.push({nd, v});
            }
        }
    }

    long long R = dist[B] % SH;
    long long S = dist[B] / SH;
    cout << R << ' ' << S << '\n';

    vector<int> path;
    for (int cur = B; cur != -1; cur = parent[cur]) {
        path.push_back(cur);
        if (cur == A) break;
    }
    reverse(path.begin(), path.end());
    for (size_t i = 0; i < path.size(); i++) {
        if (i) cout << ' ';
        cout << path[i] + 1;
    }
    cout << '\n';
    return 0;
}
