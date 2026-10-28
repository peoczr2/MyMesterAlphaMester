/*
Megoldás lényege:
Minden városból egyetlen út vezet a raktárba, így a szállítható városok a kamionok útjainak uniójából állnak; a raktár maga nem számít.
Egy levélből induló út a levél összes ősét tartalmazza, ezért érdemes leveleket választani kezdőpontnak, így K kamion K levélből indul.
A fát leghosszabb lefelé vezető utas láncokra bontjuk: minden csúcsnál a legmélyebb gyermeket visszük tovább, a többi gyermek új láncot indít, és egy lánc annyi új várost ad, amennyi a hossza.
A maximum a K leghosszabb lánc hosszának összege, a kezdőpontok pedig ezek alsó végpontjai; az időigény O(N log N).
*/
/*
Hint 1: || Egy város akkor szállítható el, ha rajta van valamelyik kamion útján. Melyik városokat érdemes kezdőpontnak választani, ha a lehető legtöbb várost akarod lefedni? ||
Hint 2: || Minden csúcsra számold ki a részfája legmélyebb levelének távolságát, és minden csúcsnál vidd tovább a leghosszabb gyermek irányát. Így a fa láncokra bomlik. ||
Hint 3: || Egy lánc annyi új várost fed le, ahány csúcsot tartalmaz a raktár nélkül. Válaszd ki a K leghosszabb láncot, és mindegyikből a lánc alsó végpontját add meg kezdőpontként. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> par(n + 1, 0);
    vector<vector<int>> ch(n + 1);
    for (int i = 1; i <= n; ++i) cin >> par[i];      // par[1] = 0
    for (int i = 2; i <= n; ++i) ch[par[i]].push_back(i);

    // BFS-sorrend a raktárból (1)
    vector<int> order{1};
    for (size_t h = 0; h < order.size(); ++h)
        for (int c : ch[order[h]]) order.push_back(c);

    // hgt: a részfa legmélyebb levelének távolsága; heavy: a leghosszabb gyermek (döntetlennél a kisebb sorszám)
    vector<int> hgt(n + 1, 0), heavy(n + 1, 0);
    for (int idx = n - 1; idx >= 0; --idx) {
        int v = order[idx];
        for (int c : ch[v])
            if (heavy[v] == 0 || hgt[c] > hgt[heavy[v]]) heavy[v] = c;
        if (heavy[v]) hgt[v] = hgt[heavy[v]] + 1;
    }

    auto bottom = [&](int v) {
        while (heavy[v]) v = heavy[v];
        return v;
    };

    // láncok: (új városok száma, a lánc alsó végpontja)
    vector<pair<int, int>> chains;
    chains.push_back({hgt[1], bottom(1)});
    for (int v = 2; v <= n; ++v)
        if (heavy[par[v]] != v) chains.push_back({hgt[v] + 1, bottom(v)});
    sort(chains.begin(), chains.end(), greater<pair<int, int>>());

    long long answer = 0;
    vector<int> chosen;
    for (size_t i = 0; i < chains.size() && (int)chosen.size() < k; ++i) {
        answer += chains[i].first;
        chosen.push_back(chains[i].second);
    }

    // ha K nagyobb a láncok számánál, a többi kamion tetszőleges, még nem választott városból indul
    vector<char> used(n + 1, 0);
    for (int c : chosen) used[c] = 1;
    for (int v = 2; v <= n && (int)chosen.size() < k; ++v)
        if (!used[v]) { used[v] = 1; chosen.push_back(v); }
    for (int v = 1; v <= n && (int)chosen.size() < k; ++v)
        if (!used[v]) { used[v] = 1; chosen.push_back(v); }

    cout << answer << "\n";
    for (size_t i = 0; i < chosen.size(); ++i)
        cout << chosen[i] << (i + 1 < chosen.size() ? ' ' : '\n');
    return 0;
}
