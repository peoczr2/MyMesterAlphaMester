/*
Megoldás lényege:
Két pont pontosan 1 egység távolságra akkor van, ha koordinátáik közül az egyik azonos, a másik 1-gyel tér el, így a pontok gráfja páros: a koordináták összegének paritása szerint két csoportra osztható.
A játék irányítatlan csúcs-geográfia, ahol Béla lép először a kiválasztott pontból. Az első lépő pontosan akkor veszít, ha a kezdőpont minden maximális párosításban benne van, ezért Alíz akkor nyer a pontból, ha van olyan maximális párosítás, amely kihagyja.
Egy maximális párosítást Kuhn-algoritmussal keresünk. Ezután a párosítatlan csúcsokból indított, párosított és nem párosított élekből váltakozó bejárás megadja azokat a csúcsokat, amelyeket valamelyik maximális párosítás kihagy.
Az időigény O(N * E), ami N <= 5000 és legfeljebb 4 él csúcsonként bőven elfér.
*/
/*
Hint 1: || Két pont pontosan 1 távolságra van, ha a koordinátáik különbsége (1,0) vagy (0,1) alakú. Ebből következik, hogy a pontok gráfja páros, és a koordináták összegének paritása adja a két csoportot. ||
Hint 2: || Béla lép először a kiválasztott pontból. Az első lépő pontosan akkor nyer egy irányítatlan gráfban, ha a kezdőpont minden maximális párosításban benne van; így Alíz akkor nyer, ha a pontot kihagyja legalább egy maximális párosítás. ||
Hint 3: || Keress egy maximális párosítást (például Kuhn-algoritmussal), majd a párosítatlan csúcsokból indított, párosított és nem párosított élekből váltakozó bejárással jelöld meg azokat a csúcsokat, amelyeket valamelyik maximális párosítás kihagyhat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int N;
vector<vector<int>> adj;
vector<int> mate;
vector<char> vis;

// Kuhn-algoritmus: a bal oldali u csúcsból növelő utat keres.
bool augment(int u) {
    for (int w : adj[u]) {
        if (vis[w]) continue;
        vis[w] = 1;
        if (mate[w] == -1 || augment(mate[w])) {
            mate[w] = u;
            mate[u] = w;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    vector<long long> X(N), Y(N);
    map<pair<long long, long long>, int> id;
    for (int i = 0; i < N; i++) {
        cin >> X[i] >> Y[i];
        id[{X[i], Y[i]}] = i;
    }

    // Két pont élben van, ha egy egységvektorral különböznek.
    const int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
    adj.assign(N, {});
    for (int i = 0; i < N; i++)
        for (int d = 0; d < 4; d++) {
            auto it = id.find({X[i] + dx[d], Y[i] + dy[d]});
            if (it != id.end()) adj[i].push_back(it->second);
        }

    // Bal oldal: a koordináták összegének páros paritása. A gráf páros.
    vector<char> isLeft(N);
    for (int i = 0; i < N; i++) isLeft[i] = ((X[i] + Y[i]) % 2 == 0);

    mate.assign(N, -1);
    vis.assign(N, 0);
    for (int u = 0; u < N; u++) {
        if (!isLeft[u] || mate[u] != -1) continue;
        fill(vis.begin(), vis.end(), 0);
        augment(u);
    }

    // Alternáló bejárás a párosítatlan csúcsokból: ezek és az elérhetők
    // pontosan azok, amelyeket valamelyik maximális párosítás kihagy.
    vector<char> inD(N, 0);
    queue<int> q;
    for (int v = 0; v < N; v++)
        if (mate[v] == -1) {
            inD[v] = 1;
            q.push(v);
        }
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int y : adj[x]) {
            if (y == mate[x]) continue;
            int z = mate[y];
            if (z == -1 || inD[z]) continue;
            inD[z] = 1;
            q.push(z);
        }
    }

    vector<int> res;
    for (int v = 0; v < N; v++)
        if (inD[v]) res.push_back(v);
    sort(res.begin(), res.end(), [&](int a, int b) {
        return make_pair(Y[a], X[a]) < make_pair(Y[b], X[b]);
    });

    cout << res.size() << '\n';
    for (int v : res) cout << X[v] << ' ' << Y[v] << '\n';
    return 0;
}
