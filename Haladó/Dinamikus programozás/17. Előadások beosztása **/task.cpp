/*
Mivel a kiválasztott előadások zárt intervallumai nem metszehetik egymást, a terem lefedett időpontjainak
száma egyszerűen a kiválasztott intervallumhosszak összege. Így ez súlyozott intervallumütemezés: minden
esemény súlya bi-ki+1, és az utolsó kompatibilis előd bináris kereséssel megkereshető. A maximális lefedésből
egyetlen kivonással megkapjuk a fedetlen időpontok számát, a döntéseket pedig visszafejtjük.
*/
/*
Hint 1: || A célfüggvényt érdemes átírni maximalizált lefedett időpontra, nem minimalizált üresre. ||
Hint 2: || Két esemény akkor kompatibilis, ha az első vége szigorúan kisebb a második kezdeténél. ||
*/

#include <bits/stdc++.h>

using namespace std;

struct Event {
    int l;
    int r;
    int idx;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, b;
    cin >> n >> k >> b;
    vector<Event> e(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> e[i].l >> e[i].r;
        e[i].idx = i;
    }

    vector<int> ends(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        ends[i] = e[i].r;
    }

    vector<long long> dp(n + 1, 0);
    vector<int> prev_ok(n + 1, 0);
    vector<char> take(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        int p = int(lower_bound(ends.begin() + 1, ends.begin() + i, e[i].l) - ends.begin()) - 1;
        prev_ok[i] = p;
        long long gain = e[i].r - e[i].l + 1;
        if (dp[p] + gain > dp[i - 1]) {
            dp[i] = dp[p] + gain;
            take[i] = 1;
        } else {
            dp[i] = dp[i - 1];
        }
    }

    vector<int> chosen;
    for (int i = n; i >= 1;) {
        long long gain = e[i].r - e[i].l + 1;
        if (take[i] && dp[i] == dp[prev_ok[i]] + gain) {
            chosen.push_back(e[i].idx);
            i = prev_ok[i];
        } else {
            --i;
        }
    }
    reverse(chosen.begin(), chosen.end());

    cout << (b - k + 1 - dp[n]) << '\n';
    cout << chosen.size() << '\n';
    for (int i = 0; i < (int)chosen.size(); ++i) {
        if (i) {
            cout << ' ';
        }
        cout << chosen[i];
    }
    cout << '\n';
    return 0;
}