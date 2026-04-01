/*
Megoldás lényege:
A sorozat következő eleme minden számból egyértelműen adódik, ezért az 1..K számokra egy funkcionális
gráfot kapunk. Azok a kezdőszámok jók, amelyekből indulva minden következő tag is legfeljebb K marad,
és végül eljutunk az 1-be.

Memoizált rekurzióval kiszámítjuk minden x-re a jó sorozat hosszát. Ha a következő elem kilóg K fölé,
akkor az adott kezdés érvénytelen. A legnagyobb érvényes hossz a válasz.
*/
/*
Hint 1: || Egy x számhoz pontosan egy következő tag tartozik. ||
Hint 2: || Ha valamelyik lépésnél K fölé ugrik a sorozat, az a kezdőszám már nem jó. ||
Hint 3: || A hosszakat érdemes memoizálni, hogy ugyanazt a láncot ne számold újra. ||
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

    int best = 1;
    for (int x = 1; x <= k; ++x) {
        best = max(best, solve(x));
    }

    cout << best << '\n';
    return 0;
}