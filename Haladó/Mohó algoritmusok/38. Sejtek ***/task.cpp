/*
Megoldás lényege:
Az optimális U mindig valamelyik sejt elpusztulási ideje, ezért a sejteket elpusztulási idő szerint dolgozzuk fel. Egy adott U-hoz a legnagyobb E az, amelynél még legalább K sejt van: ez a már feldolgozott sejtek keletkezési idejei közül a K. legnagyobb. Ezeket egy multisetben tartjuk: minden sejt után, ha legalább K elem van, a K. legnagyobbat E-jelöltként összevetjük az eddigi legjobb U-E hosszal, egyenlőség esetén a kisebb E marad. Így minden lehetséges optimális pár szerepel a jelöltek között, az időigény O(N log N).
*/
/*
Hint 1: || Ha U rögzített, akkor csak azokat a sejteket számoljuk, amelyek p <= U. ||
Hint 2: || Ezek közül az E legyen a K. legnagyobb keletkezési idő, hogy legalább K sejt maradjon. ||
Hint 3: || U-t végig lehet próbálni az elpusztulási időpontok szerint növekvően. ||
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
    multiset<int>::iterator kth;  // a K. legnagyobb keletkezési idő
    int bestLen = INT_MAX, bestE = 1, bestU = M;
    for (auto [e, p] : cells) {
        births.insert(e);
        int sz = births.size();
        if (sz < K) continue;
        if (sz == K) kth = births.begin();
        else if (e >= *kth) ++kth;
        int candE = *kth;
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