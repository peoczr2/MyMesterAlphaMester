/*
Megoldás lényege:
Az állapot a székek sorrendje (egy permutáció), egy lépés pedig két szomszédos szék emberének cseréje, így minden lépés egységnyi költségű. Mivel N legfeljebb 8, az elérhető elrendezések száma legfeljebb 8! = 40320, ezért szélességi bejárással (BFS) mind végigjárható. A BFS a kezdő elrendezésből indul, és az első olyan elrendezésnél áll meg, ahol minden kívánt pár egymás mellett ül; mivel a BFS a lépésszám szerint halad, ez adja a minimális lépésszámot. Ha az állapottér bejárása után sincs ilyen elrendezés, a válasz -1.
*/
/*
Hint 1: || Egy elrendezést leírhatsz úgy, hogy minden székhez odaírod, melyik ember ül rajta; egy lépés ebben a sorozatban két szomszédos elem felcserélését jelenti. ||
Hint 2: || Mivel N kicsi, az összes elrendezés szélességi bejárással végigjárható; az első olyan elrendezés, ahol minden igény teljesül, adja a legkevesebb cserét. ||
Hint 3: || Egy elrendezés ellenőrzéséhez készíts pozíció-tömböt (melyik ember melyik széken ül), és minden igénypárnál nézd meg, hogy a két ember székei közötti távolság pontosan 1-e. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    vector<pair<int, int>> wish(M);
    for (auto& p : wish) cin >> p.first >> p.second;

    vector<int> start(N);
    for (int i = 0; i < N; ++i) cin >> start[i];

    auto satisfied = [&](const vector<int>& row) {
        vector<int> pos(N + 1);
        for (int i = 0; i < N; ++i) pos[row[i]] = i;
        for (auto [a, b] : wish) {
            if (abs(pos[a] - pos[b]) != 1) return false;
        }
        return true;
    };

    map<vector<int>, int> dist;
    queue<vector<int>> q;
    dist[start] = 0;
    q.push(start);

    int answer = -1;
    while (!q.empty()) {
        vector<int> cur = q.front();
        q.pop();
        int d = dist[cur];
        if (satisfied(cur)) {
            answer = d;
            break;
        }
        for (int i = 0; i + 1 < N; ++i) {
            vector<int> nxt = cur;
            swap(nxt[i], nxt[i + 1]);
            if (!dist.count(nxt)) {
                dist[nxt] = d + 1;
                q.push(nxt);
            }
        }
    }

    cout << answer << "\n";
    return 0;
}
