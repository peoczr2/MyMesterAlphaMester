/*
Megoldás lényege:
Egy mezőben akkor van arany, ha a mérési eredmény pozitív, ezért ezt 0/1 értékekként kezeljük.
A 2D prefixösszeggel bármely téglalapban az aranyas mezők száma O(1) idő alatt megkapható: a négy sarokból a szokásos inklúzió-exklúzió adja az értéket.
Mivel N, M ≤ 100, a téglalapok száma csak néhány tízmillió, ezért mind a négy határt végigpróbáljuk.
Egy téglalap akkor megfelelő, ha az aranyas mezők számának kétszerese legalább a terület, ezt egész számokkal ellenőrizzük, így nincs kerekítési hiba.
A megfelelő téglalapok közül a legnagyobb területet tartjuk meg, az időigény kb. (N·M)² / 4, ami az 0,2 mp-es limitbe belefér.
*/
/*
Hint 1: || Egy mezőt pozitív mérési eredmény esetén tekints aranyasnak, így a feladat egy 0/1 rács. Egy téglalapban lévő aranyas mezők száma gyorsan kiszámolható előre összegzett tömbből (2D prefixösszeg). ||
Hint 2: || Mivel N, M legfeljebb 100, a téglalapok két sor- és két oszlophatárral mind végigpróbálhatók. A feltétel egész számokkal is ellenőrizhető: 2 * (aranyas mezők) >= terület. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> p(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int a;
            cin >> a;
            int gold = (a > 0) ? 1 : 0;
            p[i][j] = p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1] + gold;
        }
    }

    int best = 0;
    for (int r1 = 1; r1 <= n; ++r1) {
        for (int r2 = r1; r2 <= n; ++r2) {
            for (int c1 = 1; c1 <= m; ++c1) {
                for (int c2 = c1; c2 <= m; ++c2) {
                    int area = (r2 - r1 + 1) * (c2 - c1 + 1);
                    if (area <= best) continue;
                    int gold = p[r2][c2] - p[r1 - 1][c2] - p[r2][c1 - 1] + p[r1 - 1][c1 - 1];
                    if (2 * gold >= area) best = area;
                }
            }
        }
    }

    cout << best << '\n';
    return 0;
}
