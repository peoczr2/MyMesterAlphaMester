/*
Feladat: A folyó menti településeken a lehető legkevesebb vízirendőrséget kell létrehozni úgy, hogy minden település elérhető legyen K órán belül.
Ötlet: Az első még lefedetlen településhez a lehető legjobbra tett állomást választjuk a még elérhető települések közül. Ez maximalizálja az új állomás által lefedett jobb oldali tartományt.
Hint 1: || Egy állomás a saját helyétől lefelé BK, felfelé AK kilométerig érhet el. ||
Hint 2: || Az első lefedetlen települést mindig a lehető legjobbra eső még választható állomással érdemes lefedni. ||
Hint 3: || Ezután az új állomás által elért legutolsó település után kell folytatni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, b, k;
    cin >> n >> a >> b >> k;
    vector<int> pos(n + 1);
    pos[1] = 0;
    for (int i = 2; i <= n; ++i) cin >> pos[i];

    vector<int> ans;
    int i = 1;
    while (i <= n) {
        int x = pos[i];
        int limit = x + b * k;
        int j = i;
        while (j + 1 <= n && pos[j + 1] <= limit) ++j;
        if (pos[j] + a * k < x) {
            cout << 0 << '\n';
            return 0;
        }
        ans.push_back(j);
        int reach = pos[j] + a * k;
        while (i <= n && pos[i] <= reach) ++i;
    }

    cout << ans.size() << '\n';
    for (int t = 0; t < (int)ans.size(); ++t) {
        if (t) cout << ' ';
        cout << ans[t];
    }
    cout << '\n';
    return 0;
}