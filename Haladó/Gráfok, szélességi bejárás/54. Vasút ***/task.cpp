/*
Megoldás lényege:
Nem az állomásokat, hanem a vasútvonalakat tekintjük csúcsnak: két vonal között akkor van él, ha van közös állomásuk.
Az A állomást tartalmazó vonalak a kiindulási csúcsok (ezeken már egy vonal is elég), így a szélességi bejárás a legkevesebb
felhasznált vonalat adja. Az átszállások száma ilyenkor a felhasznált vonalak számánál eggyel kisebb.
Minden vonalhoz eltároljuk, melyik vonalról és melyik közös állomáson keresztül értük el, így a B-t tartalmazó
vonaltól visszafelé követve az átszállási állomások sorrendje is kiadódik.
Az időigény a vonalak és állomások teljes adatának arányos, ami a korlátok mellett gyors.
*/
/*
Hint 1: || Gondolj a vasútvonalakra csúcsként: két vonal akkor köthető össze, ha van közös állomásuk. ||
Hint 2: || A kiindulási csúcsok az A állomást tartalmazó vonalak; szélességi bejárással a legkevesebb felhasznált vonalat kapod meg. ||
Hint 3: || Minden vonalhoz jegyezd meg, melyik vonalról és melyik közös állomáson át érted el; a visszakövetéssel az átszállások sorrendje adódik. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k, n, a, b;
    cin >> k >> n >> a >> b;
    vector<vector<int>> line(n);
    vector<vector<int>> at(k + 1);
    for (int i = 0; i < n; i++) {
        int mi;
        cin >> mi;
        line[i].resize(mi);
        for (int &s : line[i]) {
            cin >> s;
            at[s].push_back(i);
        }
    }

    vector<int> dist(n, -1), par(n, -1), via(n, -1);
    queue<int> q;
    for (int l : at[a]) {
        dist[l] = 1;
        q.push(l);
    }
    while (!q.empty()) {
        int l = q.front();
        q.pop();
        for (int s : line[l]) {
            for (int l2 : at[s]) {
                if (dist[l2] != -1) continue;
                dist[l2] = dist[l] + 1;
                par[l2] = l;
                via[l2] = s;
                q.push(l2);
            }
        }
    }

    int best = -1;
    for (int l : at[b])
        if (dist[l] != -1 && (best == -1 || dist[l] < dist[best])) best = l;

    vector<int> trans;
    for (int l = best; par[l] != -1; l = par[l]) trans.push_back(via[l]);
    reverse(trans.begin(), trans.end());

    cout << trans.size() << '\n';
    for (size_t i = 0; i < trans.size(); i++) {
        if (i) cout << ' ';
        cout << trans[i];
    }
    cout << '\n';
    return 0;
}
