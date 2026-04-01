/*
Megoldás lényege:
A 90. feladathoz hasonlóan minden 1..K számra kiszámítjuk, hogy a belőle induló Collatz-sorozat
végig K alatt maradva eljut-e az 1-be, és ha igen, milyen hosszú. A leghosszabb jó sorozat kezdőeleme
adja a keresett megoldást, holtversenyben a legkisebb kezdőszámot kell választani.

Miután ismert a legjobb kezdőszám, a teljes sorozat egyszerűen visszagenerálható.
*/
/*
Hint 1: || Ugyanaz a memoizált hosszszámítás kell, mint a hosszas változatban. ||
Hint 2: || Csak azokat a kezdőszámokat szabad figyelembe venni, amelyek lánca nem lép ki K fölé. ||
Hint 3: || A végén a kiválasztott kezdőszámból a következő értékeket már csak sorban ki kell írni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;

    vector<int> dp(k + 1, -2);
    vector<char> state(k + 1, 0);

    auto nextValue = [](int x) -> long long {
        return (x % 2 == 0) ? x / 2 : 3LL * x + 1;
    };

    function<int(int)> solve = [&](int x) -> int {
        if (x < 1 || x > k) return -1;
        if (x == 1) return 1;
        if (state[x] == 2) return dp[x];
        if (state[x] == 1) return -1;
        state[x] = 1;
        long long nxt = nextValue(x);
        int child = (nxt <= k ? solve((int)nxt) : -1);
        dp[x] = (child < 0 ? -1 : child + 1);
        state[x] = 2;
        return dp[x];
    };

    int bestLen = 1;
    int bestStart = 1;
    for (int x = 1; x <= k; ++x) {
        int cur = solve(x);
        if (cur > bestLen) {
            bestLen = cur;
            bestStart = x;
        }
    }

    cout << bestLen << '\n';
    int current = bestStart;
    for (int i = 0; i < bestLen; ++i) {
        if (i) cout << ' ';
        cout << current;
        if (current != 1) current = (int)nextValue(current);
    }
    cout << '\n';
    return 0;
}