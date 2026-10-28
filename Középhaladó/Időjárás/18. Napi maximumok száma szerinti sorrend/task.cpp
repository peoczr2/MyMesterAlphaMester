/*
Megoldás lényege:
Először minden napra megkeressük az aznapi legnagyobb hőmérsékletet. Ezután minden településnél megszámoljuk, hányszor éri el ezt a maximumot; döntetlen esetén minden, a maximumot elérő település pontot kap. Végül a településeket a darabszám szerint csökkenő, egyenlőség esetén a sorszám szerint növekvő sorrendbe rendezzük. Az idő O(N·M + N log N), a memória O(N·M).
*/
/*
Hint 1: || Két lépésben gondolkodj: előbb minden napra keresd meg az aznapi legnagyobb hőmérsékletet, utána nézd meg minden településre, hogy ezt hányszor érte el. ||
Hint 2: || A teljes táblázatot érdemes tárolni (1000×1000 egész elfér a memóriában), így két bejárással dolgozhatsz: az első a napi maximumokat adja, a második a településenkénti darabszámokat. A rendezésnél a darabszám legyen az elsődleges, a sorszám a másodlagos kulcs. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> h(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> h[i][j];

    // darab[i]: hány napon éri el az i. település a napi maximumot
    vector<int> darab(n, 0);
    for (int j = 0; j < m; j++) {
        int mx = INT_MIN;
        for (int i = 0; i < n; i++) mx = max(mx, h[i][j]);
        for (int i = 0; i < n; i++)
            if (h[i][j] == mx) darab[i]++;
    }

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
