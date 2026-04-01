/*
Megoldási ötlet:
Ez ugyanaz a szerkezet, mint a határidős üléskiosztás: egy megrendelés d hosszú blokkot foglal, és legkésőbb a h-adik helyig be kell
fejeződnie. A kiválasztott megrendelések tehát egy súlyozott határidős ütemezési feladatot alkotnak.

Rendezzük a megrendeléseket h szerint. Legyen dp[i][t] a legnagyobb bevétel az első i megrendelésből, ha összesen t ülőhelyet foglaltunk
le. A kiválasztott részhalmaz visszafejthető, majd határ szerint sorban balról jobbra kiosztható.
*/
/*
Hint 1: || A „d egymás melletti ülés az első h hely között” megint csak egy hossz és egy határidő. ||
Hint 2: || A profit miatt ez nem sima eldöntés, hanem súlyozott knapsack-szerű DP. ||
Hint 3: || A kiválasztott megrendeléseket utólag már elég egymás után lerakni balról jobbra. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Order {
    int d;
    int h;
    int f;
    int id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int seats, n;
    cin >> seats >> n;
    vector<Order> orders(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> orders[i].d >> orders[i].h >> orders[i].f;
        orders[i].id = i;
    }
    sort(orders.begin() + 1, orders.end(), [](const Order& a, const Order& b) {
        if (a.h != b.h) return a.h < b.h;
        return a.id < b.id;
    });

    vector<vector<int>> dp(n + 1, vector<int>(seats + 1, -1));
    vector<vector<char>> take(n + 1, vector<char>(seats + 1, 0));
    dp[0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int t = 0; t <= seats; ++t) dp[i][t] = dp[i - 1][t];
        for (int t = orders[i].d; t <= orders[i].h; ++t) {
            if (dp[i - 1][t - orders[i].d] == -1) continue;
            int cand = dp[i - 1][t - orders[i].d] + orders[i].f;
            if (cand > dp[i][t]) {
                dp[i][t] = cand;
                take[i][t] = 1;
            }
        }
    }

    int bestT = 0;
    for (int t = 1; t <= seats; ++t) {
        if (dp[n][t] > dp[n][bestT]) bestT = t;
    }

    vector<Order> chosen;
    int curT = bestT;
    for (int i = n; i >= 1; --i) {
        if (take[i][curT]) {
            chosen.push_back(orders[i]);
            curT -= orders[i].d;
        }
    }
    reverse(chosen.begin(), chosen.end());

    cout << dp[n][bestT] << '\n';
    cout << chosen.size() << '\n';
    int start = 1;
    for (const Order& order : chosen) {
        cout << order.id << ' ' << start << '\n';
        start += order.d;
    }
    return 0;
}