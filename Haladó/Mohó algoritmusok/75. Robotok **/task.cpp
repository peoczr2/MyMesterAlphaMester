/*
Feladat: K darab ponton lévő tárgyat kell begyűjteni. Egy robot útja (1,1)-től (N,M)-ig csak jobbra/lefelé mehet, tehát az általa érintett pontok koordinátái részben rendezettek. Minimalizálni kell a robotok számát.
Ötlet: Egy robot által begyűjthető pontok láncot alkotnak a (sor, oszlop) rendezésben: ha sor szerint rendezzük a pontokat, akkor egy robot oszlopsorozata nemcsökkenő. Így a feladat minimális számú nemcsökkenő részsorozatra bontás az oszlopokból. Ennek mohó megoldása: minden oszlopot a legnagyobb <= tail értékű láncra teszünk, különben új lánc.
Hint 1: || Sor szerint rendezd a pontokat, azon belül oszlop szerint. ||
Hint 2: || Egy láncban az oszlopok nem csökkenhetnek. ||
Hint 3: || Minimális láncszámhoz a „largest tail <= c” illesztést használd. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;
    (void)N;
    (void)M;

    vector<pair<int,int>> p(K);
    for (int i = 0; i < K; ++i) cin >> p[i].first >> p[i].second;

    sort(p.begin(), p.end(), [](const auto& a, const auto& b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second < b.second;
    });

    multiset<int> tails;
    for (auto [r, c] : p) {
        (void)r;
        auto it = tails.upper_bound(c);
        if (it == tails.begin()) {
            tails.insert(c);
        } else {
            --it;
            tails.erase(it);
            tails.insert(c);
        }
    }

    cout << tails.size() << '\n';
    return 0;
}
