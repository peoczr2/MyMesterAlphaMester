/*
Megoldás lényege:
Szempontonként megkeressük a legnagyobb pontot az alsó határt elérő kutyák között, és ezt a pontot elérő kutyák (holtverseny esetén mindegyik) a szempontban győztesek. Kutyánként számoljuk, hány szempontban lettek győztesek, és ha valakinek legalább két győzelme van, a válasz VAN, különben NINCS. Ha egy szempontban senki nem éri el az alsó határt, az a szempont nem ad győztest. Az időigény O(N·M), a memóriaigény O(N·M).
*/
/*
Hint 1: || Minden szempontot külön vizsgálhatsz: keresd meg a győztes pontot az alsó határt elérő kutyák között, és a holtversenyben álló kutyák mindegyikét írd jóvá győztesként. ||
Hint 2: || Tarts kutyánként egy számlálót arról, hány szempontban lett győztes, és a végén nézd meg, van-e legalább 2 értékű számláló. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> maxPont(m), minPont(m);
    for (int &x : maxPont) cin >> x;
    for (int &x : minPont) cin >> x;

    vector<vector<int>> p(n, vector<int>(m));
    for (auto &sor : p)
        for (int &x : sor) cin >> x;

    // gyozelmek[i]: hány szempontban lett az i. kutya győztes
    vector<int> gyozelmek(n, 0);
    for (int j = 0; j < m; j++) {
        int legjobb = -1;
        for (int i = 0; i < n; i++)
            if (p[i][j] >= minPont[j]) legjobb = max(legjobb, p[i][j]);
        if (legjobb < 0) continue;

        for (int i = 0; i < n; i++)
            if (p[i][j] == legjobb) gyozelmek[i]++;
    }

    bool van = *max_element(gyozelmek.begin(), gyozelmek.end()) >= 2;

    cout << (van ? "VAN" : "NINCS") << '\n';
    return 0;
}
