/*
 * Egy szám prímtényezős felbontását írjuk ki növekvő sorrendben.
 
Hint 1: || Haladj a lehető legkisebb prímosztóktól felfelé, és mindig számold meg, hányszor osztják a számot. ||
Hint 2: || Amint egy prímet teljesen kiosztottál, már a következő osztót keresd; ha a végén marad 1-nél nagyobb szám, az maga is prímosztó. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64 n;
    cin >> n;
    auto factors = factorize_int(n);
    for (auto [p, e] : factors) cout << p << ' ' << e << '\n';
    return 0;
}
