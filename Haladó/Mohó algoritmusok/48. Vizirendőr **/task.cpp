/*
Megoldás lényege: Az első még lefedetlen településhez azt az állomást választjuk, amely a még elérhető települések közül folyásirányban a legtávolabb esik, mert ez a legtovább lát előre.
Egy állomás a folyásirányban A*K, a folyásiránnyal szemben B*K kilométerig éri el a településeket, így a lefedett szakasz az állomás helyéhez képest nem szimmetrikus.
Az állomás által elért utolsó településnél folytatjuk a keresést, így az algoritmus egyetlen bejárással, O(N) időben fut.
*/
/*
Hint 1: || Egy állomás a folyásirányban A*K, a folyásiránnyal szemben B*K kilométerig éri el a településeket. ||
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