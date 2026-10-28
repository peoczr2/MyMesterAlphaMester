/*
Megoldás lényege: a T kezdetű, H hosszú intervallumban pontosan azok a vírusok figyelhetők meg, amelyek [K, P) élettartama átfedi a [T, T+H) intervallumot, azaz K < T+H és P > T. Egy vírus így a kezdőidők egy összefüggő [K-H+1, P-1] szakaszán számít bele a számlálóba, a 1 <= T <= 7000-H korlátba vágva. Ezeket a szakaszokat különbségi tömbbel gyűjtjük össze, majd a prefixösszegekkel végigjárjuk T-t, és a legkorábbi maximumot írjuk ki; az időigény O(N + 7000).
*/
/*
Hint 1: || Egy vírus pontosan akkor figyelhető meg, ha élettartama átfedi a vizsgált intervallumot: K < T+H és P > T. ||
Hint 2: || Ez a T-kezdőpontok egy összefüggő szakasza: T a [K-H+1, P-1] tartományba esik, a [1, 7000-H] korlátba vágva. ||
Hint 3: || Minden vírus szakaszát egy különbségi tömbben rögzítheted, így egy prefixösszeg-bejárással minden T számlálója megkapható. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, h;
    cin >> n >> h;
    const int LIM = 7000;
    vector<int> diff(LIM + 3, 0);

    for (int i = 0; i < n; ++i) {
        int k, p;
        cin >> k >> p;
        int l = max(1, k - h + 1);
        int r = min(p - 1, LIM - h);
        if (l <= r) {
            ++diff[l];
            --diff[r + 1];
        }
    }

    int best = -1, bestT = 1, cur = 0;
    for (int t = 1; t <= LIM - h; ++t) {
        cur += diff[t];
        if (cur > best) {
            best = cur;
            bestT = t;
        }
    }

    cout << best << '\n' << bestT << '\n';
    return 0;
}