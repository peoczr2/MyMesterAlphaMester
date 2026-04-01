/*
Megoldás lényege:
Az adott csapat lexikografikus következőjét és előzőjét kell megadni a
választott M elemű kombinációk között.

Az előbbihez a jobb szélső növelhető elemet, az utóbbihoz a jobb szélső
csökkenthető elemet keressük meg. A sorrend ciklikus, ezért ha nincs ilyen
elem, akkor az első vagy az utolsó kombinációra ugrunk.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<int> a(m);
    for (int i = 0; i < m; ++i) cin >> a[i];

    vector<int> nxt = a;
    bool ok = false;
    for (int i = m - 1; i >= 0; --i) {
        int limit = n - m + i + 1;
        if (nxt[i] < limit) {
            ++nxt[i];
            for (int j = i + 1; j < m; ++j) nxt[j] = nxt[j - 1] + 1;
            ok = true;
            break;
        }
    }
    if (!ok) {
        for (int i = 0; i < m; ++i) nxt[i] = i + 1;
    }

    vector<int> prv = a;
    ok = false;
    for (int i = m - 1; i >= 0; --i) {
        int minVal = (i == 0 ? 1 : prv[i - 1] + 1);
        if (prv[i] > minVal) {
            --prv[i];
            for (int j = i + 1; j < m; ++j) prv[j] = n - (m - 1 - j);
            ok = true;
            break;
        }
    }
    if (!ok) {
        for (int i = 0; i < m; ++i) prv[i] = n - m + 1 + i;
    }

    for (int i = 0; i < m; ++i) {
        if (i) cout << ' ';
        cout << nxt[i];
    }
    cout << '\n';
    for (int i = 0; i < m; ++i) {
        if (i) cout << ' ';
        cout << prv[i];
    }
    cout << '\n';
    return 0;
}