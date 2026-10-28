/*
Megoldás lényege: a feladat azt kérdezi, melyik tantárgyat tanítja a legtöbb különböző tanár. Ezért nem az órák
számát kell összeszámolni, hanem minden tantárgyhoz azt, hogy hány különböző tanár tart rá órát. Egy mátrixban
(tantárgy × tanár) jelöljük, ha egy tanár tanít egy tantárgyat, így egy tanár többszöri órája sem számít kétszer.
A mátrix kitöltése O(O) időt igényel, a tantárgyankénti összegzés O(M * N). Döntetlennél a kisebb sorszámú
tantárgyat választjuk. A nap és az órák sorszáma az eredményt nem befolyásolja.
*/
/*
Hint 1: || A kérdés nem az órák száma, hanem az, hogy hány különböző tanár tanítja a tantárgyat. Egy tanár több órája ugyanazt a tanárt jelenti. ||
Hint 2: || Tárold egy tábla celláiban, hogy a j-edik tantárgyat tanítja-e az i-edik tanár. A beolvasás után tantárgyanként számold meg az igaz cellákat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int o, n, m, t, h;
    cin >> o >> n >> m >> t >> h; // a t és a h az eredményt nem befolyásolja

    // taught[s][tanar] = igaz, ha a tanár tanítja az s. tantárgyat
    vector<vector<bool>> taught(m + 1, vector<bool>(n + 1, false));
    for (int i = 0; i < o; i++) {
        int ts, tts, nap, ora;
        cin >> ts >> tts >> nap >> ora;
        taught[tts][ts] = true;
    }

    int bestSubject = 1, bestCount = -1;
    for (int s = 1; s <= m; s++) {
        int cnt = 0;
        for (int tanar = 1; tanar <= n; tanar++) cnt += taught[s][tanar];
        if (cnt > bestCount) { // szigorú >, így döntetlennél a kisebb sorszám marad
            bestCount = cnt;
            bestSubject = s;
        }
    }
    cout << bestSubject << '\n';
    return 0;
}
