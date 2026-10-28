/*
Megoldás lényege:
Egész koordinátáknál két pont pontosan akkor van 1 egység távolságra, ha rácsszomszédok, ezért a gráf páros (az x+y paritása szerint). Béla a v kezdőpontból lép, és pontosan akkor veszít, ha v minden maximális párosításban benne van. Így Alíz pontosan azokon a pontokon nyer, amelyek legalább egy maximális párosításban nincsenek lefedve. Egy maximális párosítást Kuhn-algoritmussal keresünk. Ezután mindkét színosztályban egy-egy BFS-sel megkeressük azokat a csúcsokat, amelyek egy nem fedett csúcsból páros hosszú váltakozó úton elérhetők: ezek pontosan a keresett pontok. Az időigény O(N·E), ahol N ≤ 5000, és a rácsgráfban E ≤ 2N.
*/
/*
Hint 1: || Egész koordinátáknál két pont akkor van egység távolságra, ha rácsszomszédok. Így a gráf páros, és a párosítások módszere alkalmazható. ||
Hint 2: || Béla a v pontból lép. Ő veszít pontosan akkor, ha v minden maximális párosításban benne van. Alíz tehát azokat a pontokat keresi, amelyek valamelyik maximális párosításban nincsenek lefedve. ||
Hint 3: || Keress egy maximális párosítást Kuhn-algoritmussal. Ezután mindkét színosztályban indíts BFS-t a nem fedett csúcsokból, és csak nem fedett élen lépj, fedett élen vissza. Az így elért csúcsok a válaszban vannak. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> adj;
vector<int> matchTo;     // matchTo[v] = párja a párosításban, vagy -1
vector<int> stampArr;    // a Kuhn-keresés látogatási jelölője
int stampCur = 0;

bool kuhn(int u) {
    for (int v : adj[u]) {
        if (stampArr[v] == stampCur) continue;
        stampArr[v] = stampCur;
        if (matchTo[v] == -1 || kuhn(matchTo[v])) {
            matchTo[v] = u;
            matchTo[u] = v;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    vector<long long> X(n), Y(n);
    map<pair<long long, long long>, int> id;
    for (int i = 0; i < n; i++) {
        cin >> X[i] >> Y[i];
        id[{X[i], Y[i]}] = i;
    }

    adj.assign(n, {});
    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < 4; k++) {
            auto it = id.find({X[i] + dx[k], Y[i] + dy[k]});
            if (it != id.end()) adj[i].push_back(it->second);
        }
    }

    // A gráf páros: a színosztály az x+y paritása.
    vector<int> side(n);
    for (int i = 0; i < n; i++) side[i] = (int)(((X[i] + Y[i]) % 2 + 2) % 2);

    // Maximális párosítás: Kuhn-algoritmus a 0. színosztályból.
    matchTo.assign(n, -1);
    stampArr.assign(n, 0);
    for (int u = 0; u < n; u++) {
        if (side[u] != 0) continue;
        stampCur++;
        kuhn(u);
    }

    // Olyan csúcsok, amelyek valamelyik maximális párosításban nincsenek lefedve:
    // a nem fedett csúcsokból páros hosszú váltakozó úton elérhetők.
    vector<char> good(n, 0);
    for (int s = 0; s < 2; s++) {
        vector<char> vis(n, 0);
        queue<int> q;
        for (int v = 0; v < n; v++) {
            if (side[v] == s && matchTo[v] == -1) {
                vis[v] = 1;
                q.push(v);
            }
        }
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int y : adj[x]) {
                int z = matchTo[y];   // y párja: ugyanabban a színosztályban, mint x
                if (z == -1 || vis[z]) continue;
                vis[z] = 1;
                q.push(z);
            }
        }
        for (int v = 0; v < n; v++) {
            if (side[v] == s && vis[v]) good[v] = 1;
        }
    }

    int cnt = 0;
    for (int v = 0; v < n; v++) cnt += good[v];
    cout << cnt << '\n';
    for (int v = 0; v < n; v++) {
        if (good[v]) cout << X[v] << ' ' << Y[v] << '\n';
    }
    return 0;
}
