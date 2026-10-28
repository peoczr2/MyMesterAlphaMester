/*
Megoldás lényege:
A B kód i-edik eleme azt adja meg, hány korábbi elem nagyobb A[i]-nél; ez a korábbi elemek számának (i−1) és az A[i]-nél kisebb vagy egyenlő korábbi elemek számának különbsége.
A kisebb vagy egyenlő korábbi elemek számát egy Fenwick-fával (bináris indexelt fa) kérdezzük le: minden A[i] feldolgozása után az A[i] helyére 1-et írunk, és az A[i]-ig tartó prefixösszeget kérdezzük le.
Minden elemre egy lekérdezés és egy beszúrás történik, ezért az időigény O(N log N), a tárigény O(N).
*/
/*
Hint 1: || Az i-edik elem B-értéke a korábbi i−1 elem közül azoknak a száma, amelyek nagyobbak A[i]-nél; ezt megkapod, ha az i−1-ből kivonod a kisebb-egyenlő korábbiak számát. ||
Hint 2: || Egy 1..N méretű jelölőtömbben tárold, mely értékek szerepeltek már; a kérdés egy prefixösszeg, amelyet naivan O(N) időben kapnál meg, így összesen O(N²) lenne. ||
Hint 3: || Prefixösszeg lekérdezésére és egy pozíció növelésére használj Fenwick-fát (bináris indexelt fát): mindkettő O(log N), így az összes elem gyorsan feldolgozható. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> bit;
    Fenwick(int n) : n(n), bit(n + 1, 0) {}
    void add(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) bit[idx] += val;
    }
    int sum(int idx) const {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx) res += bit[idx];
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    Fenwick fw(n);
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        int smallerOrEqual = fw.sum(x);
        int code = (i - 1) - smallerOrEqual;
        if (i > 1) cout << ' ';
        cout << code;
        fw.add(x, 1);
    }
    cout << '\n';
    return 0;
}