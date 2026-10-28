/*
 * A számot próbaosztással bontjuk fel: p = 2-től kezdve, növekvő sorrendben addig osztjuk N-et p-vel,
 * amíg osztható, és közben megszámoljuk, hányszor sikerült. Amint p * p nagyobb a maradéknál,
 * a maradék (ha nagyobb 1-nél) prím, és ez lesz az utolsó tényező. Mivel a p-ket növekvő sorrendben
 * próbáljuk, a prímtényezők is növekvő sorrendben jönnek ki. Az időigény O(sqrt(N)), ami N <= 10^8 esetén
 * legfeljebb kb. 10^4 lépés.
 */
/*
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
