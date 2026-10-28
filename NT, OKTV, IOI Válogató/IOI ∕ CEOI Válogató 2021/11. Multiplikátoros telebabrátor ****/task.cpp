/*
Megoldás lényege:
A gyökértől (1-es csúcs) vett xor-távolságokat (D[x]) egyetlen bejárással kiszámoljuk. Mivel
két csúcs útvonalának xor-ja a két gyökértől vett érték xor-ja, d(u,v) = D[u] xor D[v]. Ezért
minden u csúcsra azt a v csúcsot keressük, amelyre D[u] xor D[v] maximális. Ezt egy bináris
trie-ben oldjuk meg: a D értékek bitjeit a legfelső bittől kezdve építjük be, a lekérdezésnél
mindig a bitenként ellentétes ágat követjük, ha az létezik. A trie levelében tároljuk a csúcs
sorszámát. Az időigény O(N * 30), a memóriaigény szintén O(N * 30).
*/
/*
Hint 1: || Érdemes a gyökértől vett xor-távolságokat előre kiszámolni: egy út xor-ja két ilyen érték xor-ja, így bármely két csúcs távolsága egyetlen xor-művelettel megkapható. ||
Hint 2: || Adott x-hez keress olyan y értéket a halmazból, amelyre x xor y a lehető legnagyobb: bináris trie-ben a legfelső bittől kezdve mindig a másik bitű ágat válaszd, ha az létezik. A levélben tárold a csúcs sorszámát. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int BITS = 30;  // a súlyok legfeljebb 10^9 < 2^30, így az xor-értékek is 30 biten férnek el

vector<array<int, 2>> ch;  // trie-élek
vector<int> who;           // a levélhez tartozó csúcs sorszáma

int newNode() {
    ch.push_back({-1, -1});
    who.push_back(-1);
    return (int)ch.size() - 1;
}

void insertValue(long long x, int id) {
    int cur = 0;
    for (int b = BITS - 1; b >= 0; b--) {
        int bit = (x >> b) & 1;
        if (ch[cur][bit] == -1) {
            int nn = newNode();
            ch[cur][bit] = nn;
        }
        cur = ch[cur][bit];
    }
    who[cur] = id;
}

int bestPartner(long long x) {
    int cur = 0;
    for (int b = BITS - 1; b >= 0; b--) {
        int bit = (x >> b) & 1;
        int want = 1 - bit;  // az xor akkor nagy, ha a bit eltér
        if (ch[cur][want] != -1) {
            cur = ch[cur][want];
        } else {
            cur = ch[cur][bit];
        }
    }
    return who[cur];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // D[x]: az 1-es csúcsból x-be vezető út xor-távolsága (bejárás verembe rakással)
    vector<long long> D(n + 1, 0);
    vector<char> seen(n + 1, 0);
    vector<int> st;
    st.push_back(1);
    seen[1] = 1;
    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        for (auto [v, w] : adj[u]) {
            if (!seen[v]) {
                seen[v] = 1;
                D[v] = D[u] ^ w;
                st.push_back(v);
            }
        }
    }

    ch.reserve((size_t)n * BITS + 1);
    who.reserve((size_t)n * BITS + 1);
    newNode();  // gyökér
    for (int v = 1; v <= n; v++) {
        insertValue(D[v], v);
    }

    for (int u = 1; u <= n; u++) {
        cout << bestPartner(D[u]) << (u == n ? '\n' : ' ');
    }
    return 0;
}
