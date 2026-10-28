/*
Megoldás lényege:
A maximális hőmérséklet az országos maximum, vagyis az összes N · M előrejelzett érték legnagyobbja.
Minden napra megszámoljuk, hány településen éri el a hőmérséklet ezt az értéket.
Mivel az országos maximumot csak a teljes beolvasás után lehet tudni, a táblázatot először teljesen be kell olvasni.
Ezután a legnagyobb darabszámot keressük meg, és kiírjuk azoknak a napoknak a sorszámát, ahol ez elérhető, növekvő sorrendben.
Az idő O(N · M).
*/
/*
Hint 1: || Először az összes érték közül keresd meg a legnagyobbat, az lesz az országos maximum. Utána már csak azt kell megnézni, hány településen szerepel ez az érték egy adott napon. ||
Hint 2: || Készíts egy számláló tömböt a napokra, és minden olyan elemnél, amely egyenlő az országos maximummal, növeld az adott nap számlálóját. A végén a legnagyobb számláló értékét keresd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> h(n, vector<int>(m));
    int globalMax = INT_MIN;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> h[i][j];
            globalMax = max(globalMax, h[i][j]);
        }

    vector<int> cnt(m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (h[i][j] == globalMax)
                cnt[j]++;

    int best = *max_element(cnt.begin(), cnt.end());
    vector<int> days;
    for (int j = 0; j < m; j++)
        if (cnt[j] == best)
            days.push_back(j + 1);

    cout << days.size();
    for (int d : days)
        cout << ' ' << d;
    cout << '\n';
    return 0;
}
