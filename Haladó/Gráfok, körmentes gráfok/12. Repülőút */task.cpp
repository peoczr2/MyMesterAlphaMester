/*
Megoldás lényege:
A járatok csak a nagyobb sorszámú város felé mennek, ezért egy 1 és N közötti útvonal sorszámai szigorúan nőnek. Egy v város
akkor kerülhetetlen, ha nincs olyan használható járat (u, w), amelyre u < v < w: az ilyen járat átugorja v-t, és ezzel
kerülhető. Egy p-q járat akkor kerülhetetlen, ha a p-től q-ig terjedő vágásokat (p ≤ t < q) átvágó használható járatok közül
ez az egyetlen, mert minden 1 és N közötti útvonal pontosan egy járattal keresztezi a t és t+1 közötti vágást.
A „használható” járat itt olyan, amely 1-ből elérhető kezdőpontról N-be vezet. A számlálást különbségi tömbbel (prefixösszeggel)
végezzük, így az időigény O(N + M).
*/
/*
Hint 1: || Mivel minden járat nagyobb sorszámú városba megy, egy város akkor kerülhetetlen, ha semelyik járat nem ugorja át: nincs u < v < w járat. ||
Hint 2: || Egy járat átugorja a t és t+1 közötti vágást is: számold meg különbségi tömbbel, hány használható járat fedi le az egyes vágásokat; ha pontosan 1, az a járat kerülhetetlen. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> edges(m);
    vector<vector<int>> out(n + 1);
    for (auto& [p, q] : edges) {
        cin >> p >> q;
        out[p].push_back(q);
    }

    // Elérhető-e az 1. városból (előre), illetve el lehet-e jutni onnan az N. városba (hátra).
    vector<bool> fromStart(n + 1, false), toEnd(n + 1, false);
    fromStart[1] = true;
    for (int v = 1; v <= n; ++v) {
        if (fromStart[v]) {
            for (int q : out[v]) {
                fromStart[q] = true;
            }
        }
    }
    toEnd[n] = true;
    for (int v = n; v >= 1; --v) {
        for (int q : out[v]) {
            if (toEnd[q]) {
                toEnd[v] = true;
                break;
            }
        }
    }

    // Használható járatok: 1-ből elérhető p-ből és N-be vezető q-ba megy.
    vector<int> bypass(n + 2, 0), crossing(n + 2, 0);
    for (const auto& [p, q] : edges) {
        if (!fromStart[p] || !toEnd[q]) {
            continue;
        }
        // Az (p, q) járat a p+1 .. q-1 városokat átugorhatja.
        bypass[p + 1]++;
        bypass[q]--;
        // A p ≤ t < q vágásokat keresztezi.
        crossing[p]++;
        crossing[q]--;
    }
    for (int i = 1; i <= n + 1; ++i) {
        bypass[i] += bypass[i - 1];
        crossing[i] += crossing[i - 1];
    }

    vector<int> cities;
    for (int v = 2; v < n; ++v) {
        if (fromStart[v] && toEnd[v] && bypass[v] == 0) {
            cities.push_back(v);
        }
    }

    vector<pair<int, int>> roads;
    for (const auto& [p, q] : edges) {
        if (fromStart[p] && toEnd[q] && crossing[p] == 1) {
            roads.push_back({p, q});
        }
    }
    sort(roads.begin(), roads.end());

    cout << cities.size();
    for (int v : cities) {
        cout << ' ' << v;
    }
    cout << "\n" << roads.size() << "\n";
    for (const auto& [p, q] : roads) {
        cout << p << ' ' << q << "\n";
    }
    return 0;
}
