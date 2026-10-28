/*
Megoldás lényege:
Az anyai ág (E anyja és annak összes felmenője) és az apai ág (E apja és annak összes felmenője) csúcshalmazainak metszete adja a közös őseket. E-ből egy szélességi bejárással (BFS) a szülői éleken felfelé minden ős távolságát megkapjuk, ez a legrövidebb út hossza, vagyis a közelség. A metszet elemei közül a legkisebb távolságút kell kiírni; ha a metszet üres, -1 a válasz. Az egész O(N + M) időben fut.
*/
/*
Hint 1: || Két halmazt kell készítened: E anyjából és apjából indulva a szülői élek mentén felfelé bejárod az összes felmenőt. A közös ős ezeknek a halmazoknak a metszetében van. ||
Hint 2: || A közelséghez E-ből kell a legrövidebb távolság minden őshöz: szélességi bejárás (BFS) E-ből felfelé a szülői éleken. A metszet elemei közül a legkisebb távolságút írd ki, ha a metszet üres, akkor -1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, e;
    cin >> n >> m >> e;

    vector<vector<pair<int, int>>> par(n + 1);  // gyerek -> (tipus, szulo)
    for (int i = 0; i < m; ++i) {
        int t, g, s;
        cin >> t >> g >> s;
        par[g].push_back({t, s});
    }

    // Tavolsag E-tol felfele (BFS a szuloi eleken)
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[e] = 0;
    q.push(e);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (const auto& pr : par[x]) {
            int p = pr.second;
            if (dist[p] == -1) {
                dist[p] = dist[x] + 1;
                q.push(p);
            }
        }
    }

    // Egy szulo es az osszes felmenoje egy halmazba
    auto collect = [&](int start, vector<char>& seen) {
        if (seen[start]) return;
        vector<int> st = {start};
        seen[start] = 1;
        while (!st.empty()) {
            int x = st.back();
            st.pop_back();
            for (const auto& pr : par[x]) {
                int p = pr.second;
                if (!seen[p]) {
                    seen[p] = 1;
                    st.push_back(p);
                }
            }
        }
    };

    vector<char> anyai(n + 1, 0), apai(n + 1, 0);
    for (const auto& pr : par[e]) {
        if (pr.first == 1) collect(pr.second, anyai);
        else collect(pr.second, apai);
    }

    int best = -1;
    for (int x = 1; x <= n; ++x) {
        if (!anyai[x] || !apai[x]) continue;
        if (best == -1 || dist[x] < dist[best]) best = x;
    }

    cout << best << '\n';
    return 0;
}
