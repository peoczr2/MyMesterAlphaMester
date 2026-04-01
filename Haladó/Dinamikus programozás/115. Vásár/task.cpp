/*
Megoldási ötlet:
Először minden termékből levonjuk a kötelezően elviendő darabszámot. Ha ezek össztömege már önmagában nagyobb,
mint a teherautó kapacitása, akkor nincs megoldás. Egyébként a maradék kapacitásra már csak arról kell dönteni,
hogy az egyes termékekből a még szabadon választható példányok közül mennyit tegyünk fel.

Ez klasszikus korlátos hátizsák: minden plusz példány egy külön választható tárgy, a tömege az adott termék tömege,
az értéke az egységár. A DP a maradék kapacitás minden értékére eltárolja az elérhető legnagyobb többletbevételt.
*/
/*
Hint 1: || A kötelező darabszámokat érdemes előre „betenni” a kamionba. ||
Hint 2: || A maradék példányokból már korlátos hátizsák-feladat lesz. ||
Hint 3: || Ha a kötelező mennyiség össztömege meghaladja K-t, akkor azonnal -1 a válasz. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, capacity;
    cin >> n >> capacity;

    long long baseValue = 0;
    int baseWeight = 0;
    vector<pair<int, int>> extras;

    for (int i = 0; i < n; ++i) {
        int weight, price, amount, mandatory;
        cin >> weight >> price >> amount >> mandatory;
        baseWeight += weight * mandatory;
        baseValue += 1LL * price * mandatory;
        for (int cnt = mandatory; cnt < amount; ++cnt) extras.push_back({weight, price});
    }

    if (baseWeight > capacity) {
        cout << -1 << '\n';
        return 0;
    }

    int remaining = capacity - baseWeight;
    vector<long long> dp(remaining + 1, 0);
    for (const auto& [weight, price] : extras) {
        for (int w = remaining; w >= weight; --w) {
            dp[w] = max(dp[w], dp[w - weight] + price);
        }
    }

    long long bestExtra = 0;
    for (long long value : dp) bestExtra = max(bestExtra, value);
    cout << baseValue + bestExtra << '\n';
    return 0;
}