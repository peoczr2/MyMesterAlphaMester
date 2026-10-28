/*
Megoldás lényege:
A szülői kapcsolatokból E anyai és apai ágának csúcshalmazait kapjuk meg: az anyától és az apától indulva, DFS-sel bejárjuk az összes felmenőt (a szülő maga is benne van). A két halmaz metszete adja a közös őseket. E-ből egy szélességi bejárással (BFS) minden ős távolságát megkapjuk, ez a legrövidebb út hossza, vagyis a közelség. A közös ősök közül a legkisebb távolságú ősanya (a szülői él típusa 1) és ősapa (típusa 2) lesz a válasz; ha nincs ilyen, -1. Az egész O(N + M) időben fut.
*/
/*
Hint 1: || Két külön bejárás kell: egyet E anyjából, egyet E apjából indulva, a szülői élek mentén felfelé. A közös ősök a két bejárt halmaz metszetében vannak. ||
Hint 2: || Egy szülői élen a típus mutatja, ki a szülő: 1 esetén anya, 2 esetén apa. Ezt jegyezd fel minden csúcsra, így a közös ősök közül szét tudod válogatni az ősanyákat és az ősapákat. ||
Hint 3: || A közelséghez E-ből kell a legrövidebb távolság minden őshöz: szélességi bejárás (BFS) E-ből felfelé. Ezután egy ciklussal a közös ősök közül a két minimális távolságút válaszd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, e;
    cin >> n >> m >> e;

    vector<vector<pair<int, int>>> par(n + 1);  // gyerek -> (tipus, szulo)
    vector<int> sex(n + 1, 0);                  // 1: anya, 2: apa
    for (int i = 0; i < m; ++i) {
        int t, g, s;
        cin >> t >> g >> s;
        par[g].push_back({t, s});
        sex[s] = t;
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

    int anya = -1, apa = -1;
    for (int x = 1; x <= n; ++x) {
        if (!anyai[x] || !apai[x]) continue;
        if (sex[x] == 1 && (anya == -1 || dist[x] < dist[anya])) anya = x;
        if (sex[x] == 2 && (apa == -1 || dist[x] < dist[apa])) apa = x;
    }

    cout << anya << ' ' << apa << '\n';
    return 0;
}
