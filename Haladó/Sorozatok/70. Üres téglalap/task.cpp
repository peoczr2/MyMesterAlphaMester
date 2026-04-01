/*
Megoldás lényege:
A legnagyobb üres téglalap felső és alsó határa mindig felvehető úgy, hogy vagy a tábla szélén,
vagy közvetlenül egy fa felett/alatt legyen. Ezért elegendő a fák sorai közötti vízszintes sávokat
vizsgálni.

Rögzítünk egy felső sort, és lefelé söprünk a következő fa-sorokig. Közben karbantartjuk, hogy az
aktuális függőleges sávban mely oszlopok tiltottak már (van bennük fa). A tiltott oszlopok között a
legnagyobb rés adja a maximális szélességet, ezt egy rendezett halmazzal és rés-hossz multihalmazzal
tartjuk fenn.
*/
/*
Hint 1: || Az optimális téglalap szélei fa-sorok és fa-oszlopok közé tolhatók. ||
Hint 2: || Fix felső határ mellett lefelé haladva csak új tiltott oszlopok jelennek meg. ||
Hint 3: || A tiltott oszlopok közti legnagyobb résből közvetlenül kijön a legjobb szélesség. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n, k;
    cin >> m >> n >> k;

    map<int, vector<int>> byRow;
    vector<int> rows;
    rows.reserve(k);
    for (int i = 0; i < k; ++i) {
        int r, c;
        cin >> r >> c;
        byRow[r].push_back(c);
    }
    for (auto &entry : byRow) {
        rows.push_back(entry.first);
        auto &cols = entry.second;
        sort(cols.begin(), cols.end());
        cols.erase(unique(cols.begin(), cols.end()), cols.end());
    }

    long long answer = 0;
    int uniqueRows = (int)rows.size();

    for (int topIndex = -1; topIndex < uniqueRows; ++topIndex) {
        int top = (topIndex == -1 ? 1 : rows[topIndex] + 1);
        if (top > m) continue;

        unordered_set<int> activeColumns;
        activeColumns.reserve(2 * k + 1);
        set<int> blocked;
        multiset<int> gaps;
        blocked.insert(0);
        blocked.insert(n + 1);
        gaps.insert(n);

        auto addColumn = [&](int col) {
            if (activeColumns.find(col) != activeColumns.end()) return;
            activeColumns.insert(col);
            auto rightIt = blocked.lower_bound(col);
            auto leftIt = prev(rightIt);
            gaps.erase(gaps.find(*rightIt - *leftIt - 1));
            gaps.insert(col - *leftIt - 1);
            gaps.insert(*rightIt - col - 1);
            blocked.insert(col);
        };

        for (int rowIndex = topIndex + 1; rowIndex < uniqueRows; ++rowIndex) {
            int row = rows[rowIndex];
            if (row > top) {
                long long height = row - top;
                long long width = *gaps.rbegin();
                answer = max(answer, height * width);
            }
            for (int col : byRow[row]) {
                addColumn(col);
            }
        }

        long long height = (long long)m - top + 1;
        long long width = *gaps.rbegin();
        answer = max(answer, height * width);
    }

    cout << answer << '\n';
    return 0;
}