/*
Minden ajándék háromféleképpen végződhet: az első testvéré lesz, a másodiké lesz, vagy közösben marad. Emiatt az
állapotot jól leírja a két testvér összértékének különbsége, és ehhez tároljuk, hogy ebből a különbségből eddig mekkora
összértéket sikerült kiosztani. A végén a 0 különbségű állapotban a legnagyobb kiosztott összérték adja a minimális
maradékot, az egész kiosztás pedig visszafejthető a DP-táblából.
*/
/*
Hint 1: || Nem kell külön-külön mindkét részösszeget tárolni, elég a különbség és az összes kiosztott érték. ||
Hint 2: || Egy ajándék három opciója: bal oldal, jobb oldal vagy kimarad. ||
Hint 3: || A végső cél a 0 különbség, azon belül pedig a lehető legnagyobb kiosztott összérték. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n + 1);
    int total = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        total += a[i];
    }

    int width = 2 * total + 1;
    int offset = total;
    vector<short> best((n + 1) * width, -1);

    auto cell = [&](int i, int d) -> short& {
        return best[i * width + d];
    };

    cell(0, offset) = 0;
    for (int i = 1; i <= n; ++i) {
        for (int d = 0; d < width; ++d) {
            cell(i, d) = cell(i - 1, d);
        }
        for (int d = 0; d < width; ++d) {
            short prev = cell(i - 1, d);
            if (prev < 0) {
                continue;
            }
            if (d + a[i] < width) {
                cell(i, d + a[i]) = max<short>(cell(i, d + a[i]), prev + a[i]);
            }
            if (d - a[i] >= 0) {
                cell(i, d - a[i]) = max<short>(cell(i, d - a[i]), prev + a[i]);
            }
        }
    }

    int used = cell(n, offset);
    cout << total - used << '\n';

    vector<int> first, second;
    int d = offset;
    for (int i = n; i >= 1; --i) {
        if (cell(i, d) == cell(i - 1, d)) {
            continue;
        }
        if (d - a[i] >= 0 && cell(i - 1, d - a[i]) >= 0 && cell(i, d) == cell(i - 1, d - a[i]) + a[i]) {
            first.push_back(i);
            d -= a[i];
        } else {
            second.push_back(i);
            d += a[i];
        }
    }

    reverse(first.begin(), first.end());
    reverse(second.begin(), second.end());

    for (int i = 0; i < (int)first.size(); ++i) {
        if (i) {
            cout << ' ';
        }
        cout << first[i];
    }
    cout << '\n';
    for (int i = 0; i < (int)second.size(); ++i) {
        if (i) {
            cout << ' ';
        }
        cout << second[i];
    }
    cout << '\n';
    return 0;
}
