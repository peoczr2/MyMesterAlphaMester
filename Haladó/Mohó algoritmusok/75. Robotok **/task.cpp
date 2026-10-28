/*
Megoldás lényege:
Egy robot útja olyan pontsorozat, amelyben a sor-oszlop rendezés szerint haladva az oszlopok nem csökkenhetnek, tehát egy láncot gyűjt be a részbenrendezésben.
A legkevesebb robot száma ezért a legkisebb láncfedés, ami Dilworth-tétel szerint a legnagyobb antilánc méretével egyezik.
A pontokat sor, azon belül oszlop szerint rendezve mohón haladunk: minden pontot arra a láncra fűzünk, amelynek utolsó oszlopa a legnagyobb, de még nem nagyobb a pont oszlopánál.
Ha ilyen lánc nincs, új robotot indítunk. Az utolsó oszlopokat multiset tárolja. Időigény: O(K log K).
*/
/*
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
