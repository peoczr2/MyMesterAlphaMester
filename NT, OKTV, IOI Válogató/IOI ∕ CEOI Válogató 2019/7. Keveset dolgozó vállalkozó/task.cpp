/*
Megoldás lényege:
Az összidő minimalizálása úgy, hogy a bevétel legalább F legyen, hátizsák-jellegű kiválasztás: minden munka időt és bevételt hoz. Legyen dp[i][r] a legkisebb összidő, amellyel az első i munkából legalább r forint kereshető (r > F esetén F-nek számít). Minden munkánál vagy kihagyjuk, vagy elvállaljuk: utóbbi esetén az előző munkákból még max(0, r − Bev_i) forintot kell elérni, és az Idő_i időt hozzáadjuk. A választ dp[N][F] adja. A kiválasztott munkákat a táblázat visszafelé bejárásával kapjuk meg: ha dp[i][r] különbözik dp[i−1][r]-től, akkor az i. munka benne van. Az időigény O(N·F) ≤ 10^6.
*/
/*
Hint 1: || Két értékkel kell dolgozni: az időt kell minimalizálni, a bevételnek pedig legalább F-nek kell lennie. Érdemes a DP állapotot a bevételre építeni, az értéke pedig a legkisebb idő legyen. ||
Hint 2: || Legyen dp[i][r] a legkisebb összidő, amellyel az első i munkából legalább r bevétel érhető el. Átmenet: dp[i][r] = min(dp[i−1][r], Idő_i + dp[i−1][max(0, r − Bev_i)]), a kezdőérték dp[0][0] = 0, a többi végtelen. ||
Hint 3: || A kiválasztott munkákat dp[N][F]-ből kiindulva, visszafelé haladva kapod meg: ha dp[i][r] = dp[i−1][r], a munka kimarad; különben benne van, és r-et csökkented Bev_i-vel (0-nál nem lehet kisebb). ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, f;
    cin >> n >> f;
    vector<int> t(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) cin >> t[i] >> b[i];

    const int INF = 1000000000;
    vector<vector<int>> dp(n + 1, vector<int>(f + 1, INF));
    for (int i = 0; i <= n; i++) dp[i][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int r = 1; r <= f; r++) {
            dp[i][r] = dp[i - 1][r];
            int prev = max(0, r - b[i]);
            if (dp[i - 1][prev] < INF)
                dp[i][r] = min(dp[i][r], dp[i - 1][prev] + t[i]);
        }

    cout << dp[n][f] << "\n";

    vector<int> chosen;
    int r = f;
    for (int i = n; i >= 1; i--) {
        if (dp[i][r] == dp[i - 1][r]) continue;
        chosen.push_back(i);
        r = max(0, r - b[i]);
    }
    reverse(chosen.begin(), chosen.end());

    cout << chosen.size();
    for (int x : chosen) cout << " " << x;
    cout << "\n";
    return 0;
}
