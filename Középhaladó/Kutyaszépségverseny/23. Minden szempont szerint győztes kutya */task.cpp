/*
Megoldás lényege:
Szempontonként meghatározzuk a legnagyobb pontszámot, de csak az alsó határt elérő (értékelhető) kutyák között. Van minden szempont szerint győztes kutya, ha van olyan kutya, amelynek minden szempontban ez a maximum a pontszáma; holtverseny a győzelemben is számít. Az idő O(N·M), a memóriaigény O(N·M).
*/
/*
Hint 1: || Szempontonként keresd meg a legnagyobb pontszámot, de csak azok közül a kutyák közül, akik eléri az adott szempont alsó határát. ||
Hint 2: || Ellenőrizd, hogy van-e olyan kutya, amely minden szempontban pontosan ezt a maximumot éri el. Ha igen, a válasz VAN, különben NINCS. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> maxPont(m), minPont(m);
    for (int &x : maxPont) cin >> x;
    for (int &x : minPont) cin >> x;

    vector<vector<int>> p(n, vector<int>(m));
    for (auto &sor : p)
        for (int &x : sor) cin >> x;

    vector<int> maxErtek(m, -1);
    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++)
            if (p[i][j] >= minPont[j]) maxErtek[j] = max(maxErtek[j], p[i][j]);

    bool van = false;
    for (int i = 0; i < n && !van; i++) {
        bool mindenSzempont = true;
        for (int j = 0; j < m; j++) {
            if (maxErtek[j] < 0 || p[i][j] != maxErtek[j]) {
                mindenSzempont = false;
                break;
            }
        }
        if (mindenSzempont) van = true;
    }

    cout << (van ? "VAN" : "NINCS") << '\n';
    return 0;
}
