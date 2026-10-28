/*
Megoldás lényege:
Minden doboznak legfeljebb egy közvetlen szülője van (0, ha a doboz szabad), és egy lépés
pontosan egy szülő-kapcsolatot ad hozzá vagy old fel. Csak szabad doboz kerülhet más
doboz belsejébe, és csak szabad doboz nyitható fel. Ezért ha egy doboz szülője a két
helyzetben különbözik, az 1 lépés (ha az egyik szülő 0), illetve 2 lépés (ha mindkettő
nem 0): ez az alapköltség.

Ettől eltér a helyes válasz, ha egy doboz szülő-kapcsolata a két helyzetben ugyanaz,
de a gyermeke változik: ehhez a dobozt szabaddá kell tenni, vagyis a közös kapcsolatot
egyszer fel kell bontani és vissza kell állítani (+2). Ez a kényszer a láncban alulról
felfelé terjed, ezért a láncokat egyszer végigjárva minden közös kapcsolatra eldönthető,
hogy kell-e bontani. Az időigény O(N).
*/
/*
Hint 1: || Nézd meg minden doboznál, hogy a szülője változik-e, és ez 1 vagy 2 lépést jelent-e: ez adja az alapköltséget. Egy szülő-kapcsolatot csak akkor lehet módosítani, ha a gyermek és a szülő is szabad. ||
Hint 2: || Ha egy doboz szülője a két helyzetben megegyezik, de a gyermeke változik vagy a gyermeke közös kapcsolata is bomlik, a dobozt szabaddá kell tenni. Ehhez a közös szülő-kapcsolatot egyszer fel kell bontani és vissza kell állítani. ||
Hint 3: || A közös kapcsolatok láncait a gyermek felől haladva járd be: a „kell szabadnak lennie” jelölést a lánc alsó végéről felfelé terjeszd, és minden közös kapcsolatra csak egyszer számolj. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> s(n + 1), t(n + 1);
    for (int i = 1; i <= n; ++i) cin >> s[i];
    for (int i = 1; i <= n; ++i) cin >> t[i];

    vector<int> sc(n + 1, 0), tc(n + 1, 0);
    for (int k = 1; k <= n; ++k) {
        if (s[k]) sc[s[k]] = k;
        if (t[k]) tc[t[k]] = k;
    }

    long long answer = 0;
    for (int i = 1; i <= n; ++i) {
        if (s[i] == t[i]) continue;
        if (s[i]) ++answer;
        if (t[i]) ++answer;
    }

    vector<char> needFree(n + 1, -1);
    for (int y = 1; y <= n; ++y) {
        if (needFree[y] != -1) continue;
        vector<int> path;
        int cur = y;
        char val;
        while (true) {
            if (needFree[cur] != -1) { val = needFree[cur]; break; }
            if (sc[cur] != tc[cur]) { needFree[cur] = 1; val = 1; break; }
            if (sc[cur] == 0) { needFree[cur] = 0; val = 0; break; }
            path.push_back(cur);
            cur = sc[cur];
        }
        for (int v : path) needFree[v] = val;
    }

    for (int y = 1; y <= n; ++y) {
        if (s[y] != 0 && s[y] == t[y] && needFree[y]) answer += 2;
    }

    cout << answer << '\n';
    return 0;
}
