/*
Megoldási ötlet:
Szomszédos telkeket nem lehet egyszerre eladni, ezért ez a klasszikus „házrabló” feladat. Legyen dp[i]
az első i telekből elérhető maximális összterület. Ekkor vagy kihagyjuk az i-edik telket, vagy eladjuk,
és akkor az i-1-edik biztosan kimarad.

A döntések eltárolásával visszaépíthető egy optimális teleklista is.
*/
/*
Hint 1: || Az i-edik teleknél csak két lehetőség van: eladjuk vagy nem. ||
Hint 2: || Ha az i-edik telket eladod, az i-1-edik biztosan nem lehet benne a megoldásban. ||
Hint 3: || A visszafejtéshez tárold el, hogy az adott dp-állapotban melyik választás volt jobb. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> area(n + 1), dp(n + 1, 0);
    for (int i = 1; i <= n; ++i) cin >> area[i];

    vector<char> take(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        long long skip = dp[i - 1];
        long long use = area[i] + (i >= 2 ? dp[i - 2] : 0);
        if (use > skip) {
            dp[i] = use;
            take[i] = 1;
        } else {
            dp[i] = skip;
        }
    }

    vector<int> chosen;
    for (int i = n; i >= 1;) {
        long long use = area[i] + (i >= 2 ? dp[i - 2] : 0);
        if (take[i] && use == dp[i]) {
            chosen.push_back(i);
            i -= 2;
        } else {
            --i;
        }
    }
    sort(chosen.begin(), chosen.end());

    cout << dp[n] << '\n';
    for (size_t i = 0; i < chosen.size(); ++i) {
        if (i > 0) cout << ' ';
        cout << chosen[i];
    }
    cout << '\n';
    return 0;
}