/*
Megoldas lenyege:
Mindket allatkert nev-peldany parokat ad meg, ezert egy gyors nev->peldanyszam kereses
eseten el tudjuk donteni, hogy az adott faj csere vagy ajandekozas szempontjabol jo-e.
A sorrendhez nem kell rendezni: eleg az eredeti bemeneti sorrendben vegigmenni a fajokon,
es csak a feltetelnek megfelelo neveket kiirni.
*/
/*
Hint 1: || A fajok neve egyedi az adott allatkertben, ezert egy taroloban egyszeruen megkeresheto, hogy a masik allatkertben szerepel-e. ||
Hint 2: || A kimeneti sorrend a bemeneti sorrendet koveti, tehat kulon rendezest nem kell vegezni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<string, int>> kukutyin;
    kukutyin.reserve(n);
    unordered_map<string, int> kukMap;
    kukMap.reserve(n * 2 + 1);

    for (int i = 0; i < n; ++i) {
        string name;
        int count;
        cin >> name >> count;
        kukutyin.push_back({name, count});
        kukMap[name] = count;
    }

    int m;
    cin >> m;

    vector<pair<string, int>> ratot;
    ratot.reserve(m);
    unordered_map<string, int> ratMap;
    ratMap.reserve(m * 2 + 1);

    for (int i = 0; i < m; ++i) {
        string name;
        int count;
        cin >> name >> count;
        ratot.push_back({name, count});
        ratMap[name] = count;
    }

    int k, l;
    cin >> k >> l;

    vector<string> csere;
    vector<string> ajandekKukutyin;
    vector<string> ajandekRatot;

    for (const auto &entry : kukutyin) {
        const string &name = entry.first;
        int count = entry.second;
        auto it = ratMap.find(name);
        if (it != ratMap.end() && count >= k && it->second >= k) {
            csere.push_back(name);
        }
        if (it == ratMap.end() && count >= l) {
            ajandekKukutyin.push_back(name);
        }
    }

    for (const auto &entry : ratot) {
        const string &name = entry.first;
        int count = entry.second;
        if (kukMap.find(name) == kukMap.end() && count >= l) {
            ajandekRatot.push_back(name);
        }
    }

    auto printLine = [](const vector<string> &names) {
        for (size_t i = 0; i < names.size(); ++i) {
            if (i) cout << ' ';
            cout << names[i];
        }
        cout << '\n';
    };

    printLine(csere);
    printLine(ajandekKukutyin);
    printLine(ajandekRatot);

    return 0;
}
