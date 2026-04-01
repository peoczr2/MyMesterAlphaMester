/*
Feladat: N gyereket K szerepre kell kiosztani. Az i. szerepet legfeljebb Mi gyerek kaphatja, és minden szerepet legalább egy gyereknek játszania kell. Egy gyerek akkor sír Ti percet, ha nem a választott Si szerepet kapja. A cél az összsírás minimalizálása.
Ötlet: A „boldog” gyerekek kiválasztása szerepenként független: egy szerepre érdemes annyi saját jelentkezőt bent hagyni, amennyit a kapacitás enged (top Mi darab Ti szerint), mert ez közvetlenül csökkenti a sírást. Azután a maradék gyerekeket (akik biztosan sírnak) a még szabad férőhelyekre osztjuk, előbb feltöltve az esetleg üres szerepeket (minden szerep legalább 1).
Hint 1: || Alapállapot: mindenki sír, ezt csökkented a „saját szerepen maradókkal”. ||
Hint 2: || Egy szerepnél a legnagyobb Ti értékű saját jelentkezőket érdemes megtartani. ||
Hint 3: || A maradék gyerekek kiosztása már csak kapacitás- és „minden szerep legyen nem üres” feltétel. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<int> cap(K + 1);
    for (int r = 1; r <= K; ++r) cin >> cap[r];

    vector<int> pref(N + 1), cry(N + 1);
    for (int i = 1; i <= N; ++i) cin >> pref[i];
    for (int i = 1; i <= N; ++i) cin >> cry[i];

    vector<vector<pair<int,int>>> byRole(K + 1); // (cry, id)
    long long baseline = 0;
    for (int i = 1; i <= N; ++i) {
        byRole[pref[i]].push_back({cry[i], i});
        baseline += cry[i];
    }

    vector<int> assigned(N + 1, -1);
    vector<int> cntRole(K + 1, 0);
    vector<char> happy(N + 1, 0);

    long long saved = 0;

    for (int r = 1; r <= K; ++r) {
        auto& vec = byRole[r];
        sort(vec.begin(), vec.end(), [](auto a, auto b) {
            if (a.first != b.first) return a.first > b.first;
            return a.second < b.second;
        });
        int keep = min((int)vec.size(), cap[r]);
        for (int i = 0; i < keep; ++i) {
            int id = vec[i].second;
            happy[id] = 1;
            assigned[id] = r;
            cntRole[r]++;
            saved += vec[i].first;
        }
    }

    vector<int> unhappy;
    unhappy.reserve(N);
    for (int i = 1; i <= N; ++i) if (!happy[i]) unhappy.push_back(i);

    int ptr = 0;
    // Először minden szerep kapjon legalább 1 gyereket.
    for (int r = 1; r <= K; ++r) {
        if (cntRole[r] == 0) {
            if (ptr >= (int)unhappy.size()) {
                cout << -1 << '\n';
                return 0;
            }
            int id = unhappy[ptr++];
            assigned[id] = r;
            cntRole[r]++;
        }
    }

    // A maradék gyerekeket tetszőlegesen a szabad kapacitásokra osztjuk.
    int role = 1;
    while (ptr < (int)unhappy.size()) {
        while (role <= K && cntRole[role] >= cap[role]) ++role;
        if (role > K) {
            cout << -1 << '\n';
            return 0;
        }
        int id = unhappy[ptr++];
        assigned[id] = role;
        cntRole[role]++;
    }

    long long totalCry = 0;
    for (int i = 1; i <= N; ++i) {
        if (assigned[i] != pref[i]) totalCry += cry[i];
    }

    cout << totalCry << '\n';
    for (int i = 1; i <= N; ++i) {
        if (i > 1) cout << ' ';
        cout << assigned[i];
    }
    cout << '\n';
    return 0;
}
