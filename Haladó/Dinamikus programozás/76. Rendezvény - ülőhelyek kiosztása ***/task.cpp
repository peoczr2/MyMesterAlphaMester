/*
Megoldási ötlet:
Ha a megrendeléseket a határuk (H) szerint rendezzük, akkor pontosan egy súlyozott határidős ütemezési feladatot kapunk. Egy
megrendelés d darab egymás melletti széket foglal, vagyis d hosszú blokkot vesz el, és legkésőbb a H. székig kell befejeződnie.

Legyen dp[i][t] a legnagyobb bevétel az első i megrendelésből, ha összesen t széket foglaltunk le. Az i. megrendelést akkor vehetjük
fel, ha t >= d_i és t <= h_i. A kiválasztott rendeléseket visszafejtjük, majd határ szerint sorban, balról jobbra kiosztjuk nekik a
helyeket; ez a klasszikus balra tolt optimális ütemezés.
*/
/*
Hint 1: || A „d darab egymás melletti szék az első h hely között” ugyanaz, mint egy d hosszú feladat, amelynek határideje h. ||
Hint 2: || Ha határ szerint rendezed a megrendeléseket, akkor egy knapsack-szerű DP eldönti, melyik részhalmaz fér bele optimálisan. ||
Hint 3: || A kiválasztott megrendeléseket a határok szerinti sorrendben egyszerűen egymás után lehet leültetni balról jobbra. ||
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

    int seats, m;
    cin >> seats >> m;
    vector<Order> orders(m + 1);
    for (int i = 1; i <= m; ++i) {
        cin >> orders[i].d >> orders[i].h >> orders[i].f;
        orders[i].id = i;
    }

    vector<vector<int>> dp(m + 1, vector<int>(seats + 1, -1));
    vector<vector<char>> take(m + 1, vector<char>(seats + 1, 0));
    dp[0][0] = 0;

    for (int i = 1; i <= m; ++i) {
        for (int t = 0; t <= seats; ++t) {
            dp[i][t] = dp[i - 1][t];
        }
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
        if (dp[m][t] > dp[m][bestT]) bestT = t;
    }

    vector<Order> chosen;
    int curT = bestT;
    for (int i = m; i >= 1; --i) {
        if (take[i][curT]) {
            chosen.push_back(orders[i]);
            curT -= orders[i].d;
        }
    }
    reverse(chosen.begin(), chosen.end());

    cout << dp[m][bestT] << '\n';
    cout << chosen.size() << '\n';
    int start = 1;
    for (const Order& order : chosen) {
        cout << order.id << ' ' << start << '\n';
        start += order.d;
    }
    return 0;
}