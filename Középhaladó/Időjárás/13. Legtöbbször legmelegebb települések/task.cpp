/*
Megoldás lényege:
Először minden napra megkeressük az aznapi legmagasabb előrejelzést, ami a táblázat megfelelő oszlopának legnagyobb eleme.
Ezután minden településre számoljuk, hányszor fordul elő, hogy az előrejelzése eléri az adott nap maximumát. Ha egy napon több település is eléri a maximumot, mindegyiknél növeljük a számlálót.
Végül megkeressük a legnagyobb számlálót, és kiírjuk azoknak a településeknek a sorszámát, akiknél ez elérhető, növekvő sorrendben.
Mivel a napi maximum az egész oszlop ismeretét igényli, a táblázatot először teljesen be kell olvasni, majd két bejárással feldolgozni.
Az idő O(N · M).
*/
/*
Hint 1: || Gondolj a táblázatra úgy, hogy minden oszlop egy nap, és az aznapi maximum az oszlop legnagyobb eleme. ||
Hint 2: || Minden településhez tarts egy számlálót, és minden napon, ahol a település értéke egyenlő a napi maximummal, növeld meg. A végén a legnagyobb számlálójú települések sorszámát kell kiírni. ||
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

    vector<int> cnt(n, 0);
    for (int j = 0; j < m; j++) {
        int dayMax = INT_MIN;
        for (int i = 0; i < n; i++)
            dayMax = max(dayMax, h[i][j]);
        for (int i = 0; i < n; i++)
            if (h[i][j] == dayMax)
                cnt[i]++;
    }

    int best = *max_element(cnt.begin(), cnt.end());
    vector<int> chosen;
    for (int i = 0; i < n; i++)
        if (cnt[i] == best)
            chosen.push_back(i + 1);

    cout << chosen.size();
    for (int x : chosen)
        cout << ' ' << x;
    cout << '\n';
    return 0;
}
