/*
Megoldás lényege:
Minden településre kiszámoljuk a napi hőmérsékletek összegét. Egy nap akkor melegebb az átlagnál, ha h > S / M, ahol S az összeg és M a napok száma. Ezt törtek nélkül, az M·h > S egyenlőtlenséggel vizsgáljuk, így nincs lebegőpontos pontatlanság. Végül a településeket az átlagnál melegebb napok száma szerint csökkenő, egyenlőség esetén sorszám szerint növekvő sorrendbe rendezzük. Az idő O(N·M + N log N), a memória O(N·M).
*/
/*
Hint 1: || Egy település átlagnál melegebb napjainak megszámolásához előbb a saját átlagát kell ismerned, ezért a település összes napi értékét érdemes összegezni, mielőtt döntesz egy napról. ||
Hint 2: || Az átlag törtszám, de nem kell osztani: a h > S / M feltétel ekvivalens az M·h > S egyenlőtlenséggel, ami egész számokon pontos. A táblázatot érdemes tárolni, mert az összeg és a számlálás is bejárást igényel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> h(n, vector<int>(m));
    vector<int> osszeg(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> h[i][j];
            osszeg[i] += h[i][j];
        }
    }

    // darab[i]: hány napon melegebb az i. településnél az átlagánál
    vector<int> darab(n, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (m * h[i][j] > osszeg[i]) darab[i]++;

    vector<int> telepulesek(n);
    iota(telepulesek.begin(), telepulesek.end(), 0);
    sort(telepulesek.begin(), telepulesek.end(), [&](int a, int b) {
        if (darab[a] != darab[b]) return darab[a] > darab[b];
        return a < b;
    });

    for (int k = 0; k < n; k++) {
        if (k > 0) cout << ' ';
        cout << telepulesek[k] + 1;
    }
    cout << '\n';
    return 0;
}
