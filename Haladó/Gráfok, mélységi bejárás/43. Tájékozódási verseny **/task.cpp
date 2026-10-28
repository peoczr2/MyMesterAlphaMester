/*
Megoldás lényege:
Egy ellenőrzőpont pontosan akkor kikerülhetetlen, ha a Start-ból a Cél a pont nélkül már nem érhető el. A Start és a Cél mindig benne van minden úton, ezért ezeket külön vesszük, a többi pontot pedig egyesével ellenőrizzük. Ha a Start-ból a Cél eleve nem érhető el, a válasz -1. Mivel N legfeljebb 200, minden pontra elfér egy teljes bejárás a Start-ból, amelyben a vizsgált pontot kihagyjuk. Az időigény O(N*(N+K)), ami a korlátok mellett bőven belefér.
*/
/*
Hint 1: || Egy pont akkor nem kerülhető ki, ha nélküle a Start-ból már nem lehet eljutni a Cél-ba. Ezt kell minden pontra megnézni. ||
Hint 2: || N legfeljebb 200, ezért minden pontra lefuttathatsz egy bejárást a Start-ból: a vizsgált pontot tiltottnak jelölöd, és megnézed, eléri-e a Cél. Ha nem, a pont kikerülhetetlen. Ha eleve nincs út, a válasz -1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s, t, k;
    cin >> n >> s >> t >> k;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < k; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
    }

    // Bejárás s-ből a banned csúcs kihagyásával (banned = 0: nincs tiltott csúcs).
    // Visszaadja, hogy t elérhető-e.
    auto reachable = [&](int banned) {
        vector<char> seen(n + 1, 0);
        seen[banned] = 1;
        seen[s] = 1;
        vector<int> st = {s};
        while (!st.empty()) {
            int x = st.back();
            st.pop_back();
            for (int y : g[x])
                if (!seen[y]) {
                    seen[y] = 1;
                    st.push_back(y);
                }
        }
        return seen[t] != 0;
    };

    if (!reachable(0)) {
        cout << "-1\n";
        return 0;
    }

    vector<int> ans;
    for (int v = 1; v <= n; ++v)
        if (v == s || v == t || !reachable(v)) ans.push_back(v);

    cout << ans.size() << "\n";
    for (size_t i = 0; i < ans.size(); ++i) cout << ans[i] << (i + 1 < ans.size() ? ' ' : '\n');
    return 0;
}
