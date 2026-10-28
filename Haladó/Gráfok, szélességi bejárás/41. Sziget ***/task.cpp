/*
Megoldás lényege:
Minden négyzethez kiszámítjuk az F értéket: ez a legalacsonyabb vízszint, amelynél a tenger a szélről eljut a négyzetig (a szélről odavezető utak közül azé, amelyiknek a legmagasabb pontja a legalacsonyabb). Ezt prioritásos sorral, Dijkstra-szerűen kapjuk meg. Minden négyzeten a víz felszínét (s) tároljuk; a négyzet vízzel borított, ha s nagyobb a magasságánál. Emelkedéskor a szélről vagy már vizes négyzetekből elérhető, a szintnél alacsonyabb négyzetek a szintre emelkednek, amit szélességi bejárással számolunk. Csökkenéskor a szélhez kapcsolódó (F < szint) négyzetek a szintre süllyednek, a többi víz viszont megmarad, legfeljebb az F értékig, mert ott folyik le. Minden állapot után megszámoljuk a szárazon maradt négyzeteket. Az időigény O(K * N * M), ami a korlátok mellett bőven belefér.
*/
/*
Hint 1: || Először határozd meg minden négyzetre, milyen magas vízszint kell ahhoz, hogy a tenger a szélről odaérjen. Ez a szélről induló minimax út, amit prioritásos sorral lehet kiszámítani. ||
Hint 2: || Ne csak azt tárold, hogy egy négyzet vizes-e, hanem a víz felszínének magasságát is. Emelkedésnél a szélről és a vizes négyzetekről szélességi bejárással árassz el minden, a szintnél alacsonyabb négyzetet. ||
Hint 3: || Csökkenésnél a szélhez kapcsolódó négyzetek a szintre kerülnek, a többi vizes négyzet felszíne legfeljebb az előbb kiszámolt F értékig csökkenhet. Minden állapot után a vízmentes négyzeteket kell megszámolni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<long long>> h(n, vector<long long>(m));
    for (auto& row : h)
        for (auto& x : row) cin >> x;
    vector<long long> delta(k);
    for (auto& d : delta) cin >> d;

    const int di[4] = {1, -1, 0, 0};
    const int dj[4] = {0, 0, 1, -1};
    auto onBorder = [&](int i, int j) { return i == 0 || j == 0 || i == n - 1 || j == m - 1; };

    // F[i][j]: a legalacsonyabb szint, amelynél a tenger a szélről a négyzetig eljut.
    const long long INF = LLONG_MAX / 4;
    vector<vector<long long>> F(n, vector<long long>(m, INF));
    using State = tuple<long long, int, int>;
    priority_queue<State, vector<State>, greater<State>> pq;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (onBorder(i, j)) {
                F[i][j] = h[i][j];
                pq.emplace(h[i][j], i, j);
            }
    while (!pq.empty()) {
        auto [f, i, j] = pq.top();
        pq.pop();
        if (f > F[i][j]) continue;
        for (int d = 0; d < 4; d++) {
            int x = i + di[d], y = j + dj[d];
            if (x < 0 || x >= n || y < 0 || y >= m) continue;
            long long nf = max(h[x][y], f);
            if (nf < F[x][y]) {
                F[x][y] = nf;
                pq.emplace(nf, x, y);
            }
        }
    }

    // s[i][j]: a víz felszíne a négyzeten. A négyzet vízzel borított, ha s > h.
    vector<vector<long long>> s(n, vector<long long>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) s[i][j] = (h[i][j] < 0) ? 0 : h[i][j];

    auto countDry = [&]() {
        int cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (!(s[i][j] > h[i][j])) cnt++;
        return cnt;
    };

    cout << countDry() << '\n';

    long long level = 0;
    for (long long d : delta) {
        long long prev = level;
        level += d;

        if (level > prev) {
            // Emelkedés: a szélről vagy vizes négyzetekről elérhető, a szintnél alacsonyabb négyzetek elöntődnek.
            vector<vector<char>> seen(n, vector<char>(m, 0));
            queue<pair<int, int>> q;
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    if (onBorder(i, j) || s[i][j] > h[i][j]) {
                        seen[i][j] = 1;
                        q.emplace(i, j);
                    }
            while (!q.empty()) {
                auto [i, j] = q.front();
                q.pop();
                for (int dir = 0; dir < 4; dir++) {
                    int x = i + di[dir], y = j + dj[dir];
                    if (x < 0 || x >= n || y < 0 || y >= m) continue;
                    if (seen[x][y] || h[x][y] >= level) continue;
                    seen[x][y] = 1;
                    q.emplace(x, y);
                }
            }
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    if (seen[i][j] && h[i][j] < level) s[i][j] = max(s[i][j], level);
        } else {
            // Csökkenés: a szélhez kapcsolódó négyzetek a szintre kerülnek, a többi víz legfeljebb F-ig marad.
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    s[i][j] = (F[i][j] < level) ? level : min(s[i][j], F[i][j]);
        }

        cout << countDry() << '\n';
    }
    return 0;
}
