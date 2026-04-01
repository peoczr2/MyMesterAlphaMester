/*
Feladat: A legszűkebb időintervallumot kell megtalálni, amelyben legalább K sejt teljes életciklusa benne van.
Ötlet: Rendezzük a sejteket elpusztulási idő szerint, és egy mozgó ablakban tartsuk nyilván a lehetséges kezdőpontokat. Minden U végpontra a K. legnagyobb keletkezési idő adja az optimális E-t.
Hint 1: || Ha U rögzített, akkor csak azokat a sejteket számítjuk, amelyek p<=U. ||
Hint 2: || Ezek közül az E legyen a K. legnagyobb keletkezési idő, hogy legalább K sejt maradjon. ||
Hint 3: || U-t végig lehet próbálni a távozási időpontok szerint növekvően. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K, M, N;
    cin >> K >> M >> N;
    vector<pair<int,int>> cells(N);
    for (int i = 0; i < N; ++i) cin >> cells[i].first >> cells[i].second;
    sort(cells.begin(), cells.end(), [](auto &x, auto &y) {
        if (x.second != y.second) return x.second < y.second;
        return x.first < y.first;
    });

    multiset<int> births;
    int bestLen = INT_MAX, bestE = 1, bestU = M;
    for (auto [e, p] : cells) {
        births.insert(e);
        if ((int)births.size() < K) continue;
        auto it = births.end();
        advance(it, -K);
        int candE = *it;
        int candU = p;
        int len = candU - candE;
        if (len < bestLen || (len == bestLen && candE < bestE)) {
            bestLen = len;
            bestE = candE;
            bestU = candU;
        }
    }

    cout << bestE << ' ' << bestU << '\n';
    return 0;
}