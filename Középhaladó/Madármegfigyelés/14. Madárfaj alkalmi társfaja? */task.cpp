/*
Megoldás lényege:
Két faj akkor alkalmi társfaja egymásnak, ha van olyan helység, ahol mindkettőt megfigyeltük. Ezt helységenként ellenőrizzük: az adott helyen előforduló fajok minden párját bejelöljük egy N×N-es logikai táblázatban. Egy faj önmagának nem társfaja, ezért a főátlót kihagyjuk. A végén minden sorból N darab 0/1 karaktert írunk ki. Mivel helységenként legfeljebb N² párt nézünk, az összidő O(M·N²), vagyis legfeljebb 2·10^6 művelet.
*/
/*
Hint 1: || Egy helységben csak a ténylegesen előforduló fajok számítanak: a 0 darabszámú faj nem vesz részt a párosításban. A helységeket egyenként, külön kell feldolgoznod. ||
Hint 2: || Készíts egy N×N-es logikai táblázatot, amely kezdetben minden elemében hamis. Minden helységben a pozitív darabszámú fajok minden (j, k) párjára, ahol j ≠ k, állítsd igazra a táblázat j-edik sorának k-adik elemét. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    vector<vector<bool>> egyutt(N + 1, vector<bool>(N + 1, false));
    vector<int> sor(N + 1);
    for (int i = 0; i < M; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> sor[j];
        }
        for (int j = 1; j <= N; ++j) {
            if (sor[j] == 0) continue;
            for (int k = 1; k <= N; ++k) {
                if (k != j && sor[k] > 0) egyutt[j][k] = true;
            }
        }
    }

    for (int j = 1; j <= N; ++j) {
        for (int k = 1; k <= N; ++k) {
            cout << (egyutt[j][k] ? '1' : '0');
        }
        cout << '\n';
    }
    return 0;
}
