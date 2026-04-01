/*
Megoldás lényege:
Rendezzük a megrendeléseket határidő szerint. Ha kiválasztunk közülük egy
részhalmazt, akkor az ütemezhető pontosan akkor, ha ebben a sorrendben haladva
minden prefix teljes hossza legfeljebb az aktuális határidő. Mivel M <= 1000,
dinamikus programmal tárolhatjuk, hogy az eddig vizsgált megrendelésekből mely
összes bérleti napok érhetők el.

Legyen dp[t] igaz, ha az első i megrendelésből kiválasztható olyan részhalmaz,
amely összesen t napot foglal, és a határidőfeltételek teljesülnek. Az i-edik
megrendelés (D, H) akkor vehető fel, ha a korábbi t állapotból t + D <= H.
Így a legnagyobb elérhető t a maximális összes bérbeadott nap. A visszafejtéshez
eltároljuk, melyik állapot melyik megrendeléssel jött létre.

Miután megvan a kiválasztott részhalmaz, a határidő szerinti sorrendben egymás
után ütemezzük őket a lehető legkorábbi kezdőnapokra; ez biztosan jó, mert a DP
pontosan ezt a prefixfeltételt garantálta.

Idő: O(N * M)
*/
/*
Hint 1: || Határidő szerinti rendezés után elég azt figyelni, hogy az eddigi összhossz belefér-e minden aktuális határidőbe. ||
Hint 2: || A DP állapota lehet egyszerűen az összes már lefoglalt napok száma. ||
Hint 3: || Ha kiválasztottad a megrendeléseket, a legkorábbi kezdés szerinti sorbarakás automatikusan jó lesz. ||
*/

#include <bits/stdc++.h>

using namespace std;

struct Order {
    int days;
    int deadline;
    int index;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;

    vector<Order> orders(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> orders[i].days >> orders[i].deadline;
        orders[i].index = i;
    }

    stable_sort(orders.begin() + 1, orders.end(), [](const Order& a, const Order& b) {
        if (a.deadline != b.deadline) {
            return a.deadline < b.deadline;
        }
        return a.index < b.index;
    });

    vector<vector<char>> reach(n + 1, vector<char>(m + 1, 0));
    vector<vector<int>> parent_sum(n + 1, vector<int>(m + 1, -1));
    vector<vector<char>> took(n + 1, vector<char>(m + 1, 0));
    reach[0][0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int t = 0; t <= m; ++t) {
            if (reach[i - 1][t] && !reach[i][t]) {
                reach[i][t] = 1;
                parent_sum[i][t] = t;
            }
        }
        for (int t = 0; t + orders[i].days <= m; ++t) {
            if (!reach[i - 1][t]) {
                continue;
            }
            int next_sum = t + orders[i].days;
            if (next_sum > orders[i].deadline) {
                continue;
            }
            if (!reach[i][next_sum]) {
                reach[i][next_sum] = 1;
                parent_sum[i][next_sum] = t;
                took[i][next_sum] = 1;
            }
        }
    }

    int best = m;
    while (best >= 0 && !reach[n][best]) {
        --best;
    }

    vector<Order> chosen;
    int current = best;
    for (int i = n; i >= 1; --i) {
        if (!reach[i][current]) {
            continue;
        }
        if (took[i][current]) {
            chosen.push_back(orders[i]);
        }
        current = parent_sum[i][current];
    }
    reverse(chosen.begin(), chosen.end());

    cout << best << '\n';
    cout << chosen.size() << '\n';

    int start_day = 1;
    for (const Order& order : chosen) {
        cout << order.index << ' ' << start_day << '\n';
        start_day += order.days;
    }

    return 0;
}