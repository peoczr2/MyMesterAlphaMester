/*
Megoldási ötlet:
A pihenőhelyek távolság szerint rendezettek, így ez súlyozott intervallumfüggetlen halmaz feladat. Ha az i. helyre
 építünk kutat, akkor az előző kiválasztott hely legfeljebb az utolsó olyan j lehet, amelyre T[i]-T[j] >= K.

Legyen dp[i] az első i pihenőhelyből elérhető maximális haszon. Ekkor vagy kihagyjuk az i-edik helyet, vagy építünk
oda kutat, és hozzáadjuk dp[prev(i)] értékét. A döntéseket eltárolva az optimális helylista is visszafejthető.
*/
/*
Hint 1: || Minden helyhez keresd meg az utolsó kompatibilis korábbi helyet. ||
Hint 2: || A DP átmenete ugyanaz, mint a súlyozott intervallum-kiválasztásnál: kihagyás vagy választás. ||
Hint 3: || Rekonstrukciókor visszafelé haladj az eltárolt döntések alapján. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, minDistance;
    cin >> n >> minDistance;
    vector<int> position(n + 1), profit(n + 1);
    for (int i = 1; i <= n; ++i) cin >> position[i] >> profit[i];

    vector<int> prev(n + 1, 0);
    int left = 0;
    for (int i = 1; i <= n; ++i) {
        while (left + 1 < i && position[i] - position[left + 1] >= minDistance) ++left;
        prev[i] = left;
    }

    vector<long long> dp(n + 1, 0);
    vector<char> take(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        long long skip = dp[i - 1];
        long long use = profit[i] + dp[prev[i]];
        if (use > skip) {
            dp[i] = use;
            take[i] = 1;
        } else {
            dp[i] = skip;
        }
    }

    vector<int> chosen;
    for (int i = n; i >= 1;) {
        if (take[i] && profit[i] + dp[prev[i]] == dp[i]) {
            chosen.push_back(i);
            i = prev[i];
        } else {
            --i;
        }
    }
    sort(chosen.begin(), chosen.end());

    cout << dp[n] << '\n';
    cout << chosen.size();
    for (int index : chosen) cout << ' ' << index;
    cout << '\n';
    return 0;
}