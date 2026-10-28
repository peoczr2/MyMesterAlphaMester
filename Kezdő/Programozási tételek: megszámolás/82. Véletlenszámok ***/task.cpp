/*
Megoldás lényege:
Az első i elem után minden 0..M-1 értékről nyilvántartjuk, hányszor szerepelt eddig (prefixösszeg).
Az [A,B] intervallumban egy érték pontosan akkor nem fordul elő, ha az első B elemben és az első A-1 elemben ugyanannyiszor szerepel.
Így minden kérdésre végigmegyünk az M értéken, és megszámoljuk azokat, amelyekre ez teljesül. Az előkészítés O(N*M), egy kérdés O(M), az összes idő O(N*M + Db*M), ami N≤20000, M≤100 és Db≤10000 mellett bőven belefér az időlimitbe.
*/
/*
Hint 1: || Egy érték akkor nem fordul elő az [A,B] intervallumban, ha az A-1. elemig és a B. elemig ugyanannyiszor szerepel. Ezt érdemes a két határ különbségével vizsgálni. ||
Hint 2: || Számold ki minden i-re, hogy az első i elemben melyik értékből hány van, és tárold tömbben. Egy kérdésnél így minden értékre konstans idő alatt eldöntheted, hogy van-e előfordulás, nem kell újra végigmenned az intervallumon. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }

    // pref[i][x]: az x érték hányszor szerepel az első i elemben
    vector<vector<int>> pref(n + 1, vector<int>(m, 0));
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1];
        pref[i][v[i]]++;
    }

    int db;
    cin >> db;
    while (db--) {
        int a, b;
        cin >> a >> b;
        int nincs = 0;
        for (int x = 0; x < m; x++) {
            if (pref[b][x] == pref[a - 1][x]) {
                nincs++;
            }
        }
        cout << nincs << "\n";
    }
    return 0;
}
