/*
Megoldás:
Három nyomtató közül mindig legfeljebb kettő lehet egyszerre a két portra kötve.
Ezért elegendő a jelenlegi bekötött halmazt állapotként kezelni. Az i-edik kérés
után csak az számít, hogy mely nyomtatók vannak éppen bekötve; ez legfeljebb 8 maszk.
Minden új kérésre végigpróbáljuk, hogy ha a kért nyomtató nincs bent, akkor egy új
kapcsolással berakjuk egy üres helyre vagy lecseréljük valamelyik jelenlegi nyomtatót.
Az összes lehetőség közül a minimális kapcsolásszámot tartjuk meg.

Az állapotok száma konstans, ezért az algoritmus O(N), a memóriaigénye O(1).
*/
/*
Hint 1: || Elég azt nyilvántartani, hogy az aktuális pillanatban melyik 0, 1 vagy 2 nyomtató van a két portra kötve. ||
Hint 2: || Egy kérés teljesítéséhez csak akkor kell új kapcsolás, ha a kért betű nincs a jelenlegi maszkban. ||
Hint 3: || Mivel csak háromféle nyomtató létezik, a lehetséges maszkok száma mindössze 8, így dinamikus programozás is belefér. ||
*/

#include <algorithm>
#include <array>
#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    const int INF = 1e9;
    array<int, 8> dp;
    array<int, 8> ndp;
    dp.fill(INF);
    dp[0] = 0;

    for (char ch : s) {
        int printer = ch - 'A';
        ndp.fill(INF);

        for (int mask = 0; mask < 8; ++mask) {
            if (dp[mask] == INF) {
                continue;
            }

            if (mask & (1 << printer)) {
                ndp[mask] = min(ndp[mask], dp[mask]);
                continue;
            }

            if (__builtin_popcount(mask) < 2) {
                ndp[mask | (1 << printer)] = min(ndp[mask | (1 << printer)], dp[mask] + 1);
                continue;
            }

            for (int other = 0; other < 3; ++other) {
                if (mask & (1 << other)) {
                    int nextMask = (mask ^ (1 << other)) | (1 << printer);
                    ndp[nextMask] = min(ndp[nextMask], dp[mask] + 1);
                }
            }
        }

        dp = ndp;
    }

    cout << *min_element(dp.begin(), dp.end()) << '\n';
    return 0;
}