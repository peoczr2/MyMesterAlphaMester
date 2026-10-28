/*
Megoldás lényege:
Gyökerezzük a fát az 1. csúcsban, és legyen x[v] az 1-ből v-be vezető út XOR-ja. A közös szakasz XOR-ja kiesik, ezért d(u,v) = x[u] XOR x[v]. Így minden u-hoz azt a v csúcsot kell megtalálni, amelyre x[u] XOR x[v] maximális. Ezt bináris trie-vel oldjuk meg: az összes x[v] értékét 30 bittel (felülről lefelé) beszúrjuk, a lekérdezésnél minden bitnél az ellentétes bitű ágat követjük, és a trie csúcsain tárolt csúcs lesz a válasz. Több jó válasz esetén bármelyik megfelel. Az időigény O(N · 30), a memóriaigény szintén O(N · 30).
*/
/*
Hint 1: || Rögzíts gyökeret (az 1. csúcs), és számold ki minden csúcsra a gyökértől vett út XOR-ját. Két csúcs közötti út XOR-ja ebből a két érték XOR-ja. ||
Hint 2: || A legnagyobb XOR-ú párra a klasszikus eszköz a bináris trie: a számokat 30 bitjükkel szúrd be felülről lefelé, és lekérdezésnél minden bitnél az ellentétes bitű ágat válaszd, ha van. ||
Hint 3: || A trie minden csúcsánál tárold, melyik csúcs értéke halad át rajta. A lekérdezés végén ez a csúcs adja a legtávolabbi csúcsot. Ha több jó válasz van, bármelyik elfogadható. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<pair<int, int>>> g(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    // x[v] = az 1-ből v-be vezető út XOR-ja, így d(u,v) = x[u] XOR x[v].
    vector<int> x(n + 1, 0);
    vector<char> seen(n + 1, 0);
    queue<int> q;
    q.push(1);
    seen[1] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, w] : g[u]) {
            if (!seen[v]) {
                seen[v] = 1;
                x[v] = x[u] ^ w;
                q.push(v);
            }
        }
    }

    // Bináris trie: w <= 10^9 < 2^30, így 30 bit elég.
    const int BITS = 30;
    vector<array<int, 2>> ch;
    vector<int> who;          // who[csúcs] = egy olyan csúcs, amelynek értéke átmegy rajta
    ch.reserve((size_t)n * BITS + 2);
    who.reserve((size_t)n * BITS + 2);
    ch.push_back({0, 0});
    who.push_back(0);
    for (int v = 1; v <= n; v++) {
        int node = 0;
        who[node] = v;
        for (int b = BITS - 1; b >= 0; b--) {
            int bit = (x[v] >> b) & 1;
            if (ch[node][bit] == 0) {
                ch.push_back({0, 0});
                who.push_back(0);
                ch[node][bit] = (int)ch.size() - 1;
            }
            node = ch[node][bit];
            who[node] = v;
        }
    }

    for (int i = 1; i <= n; i++) {
        int node = 0;
        for (int b = BITS - 1; b >= 0; b--) {
            int want = ((x[i] >> b) & 1) ^ 1;
            if (ch[node][want] != 0) node = ch[node][want];
            else node = ch[node][want ^ 1];
        }
        cout << who[node] << (i < n ? ' ' : '\n');
    }
    return 0;
}
