/*
Minden 1..K díjhoz megkeressük a legkevesebb szükséges bélyegek számát korlátlan darabszám mellett.
Ez pontosan az unbounded coin change minimumos változata: dp[x] a legkisebb bélyegszám az x összeghez,
és minden címletre balról jobbra frissítünk. Mivel az 1 címlet biztosan szerepel, minden összeg előállítható.
A keresett M az 1..K tartományon vett legnagyobb minimális bélyegszám.
*/
/*
Hint 1: || Ne azt vizsgáld külön-külön, hogy egy adott M elég-e, hanem számold ki minden összeg minimális bélyegszámát. ||
Hint 2: || Ez a klasszikus korlátlan pénzváltásos DP minimumkereséssel. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> stamp(n);
    for (int i = 0; i < n; ++i) {
        cin >> stamp[i];
    }

    const int INF = 1e9;
    vector<int> dp(k + 1, INF);
    dp[0] = 0;
    for (int c : stamp) {
        for (int sum = c; sum <= k; ++sum) {
            dp[sum] = min(dp[sum], dp[sum - c] + 1);
        }
    }

    int answer = 0;
    for (int sum = 1; sum <= k; ++sum) {
        answer = max(answer, dp[sum]);
    }
    cout << answer << '\n';
    return 0;
}