/*
Megoldás lényege:
A teljes tejmennyiség áttöltéskor nem változik, ezért egy állapotot elég az első két kanna mennyiségével leírni, a
harmadik kanna mennyisége ebből már kiszámolható. Szélességi bejárást futtatunk a kezdeti állapotból: minden
állapotból minden (forrás, cél) kannapárra és mindkét mérőpohár-mennyiségre (A vagy B) megnézzük, hogy a forrásban
van-e elég tej, és ha igen, az új állapotba lépünk. Mivel minden lépés egyforma költségű, az első olyan állapot,
ahol mindhárom kannában az összeg harmada van, a legkevesebb áttöltéssel érhető el. A lépéseket a szülő-állapotokból
visszafelé rakjuk össze. Az állapotok száma legfeljebb (S + 1)^2, ahol S az összes tej, így az időigény ehhez képest
kicsi.
*/
/*
Hint 1: || Az áttöltések nem változtatják a tej teljes mennyiségét, ezért elég az első két kanna mennyiségét állapotként tárolni: a harmadik kanna az összegből kiszámolható. Mivel minden lépés egyforma költségű, a legkevesebb áttöltés szélességi bejárással adódik. ||
Hint 2: || Egy állapotból minden olyan (forrás, cél, mennyiség) hármast ki kell próbálni, ahol a mennyiség A vagy B, és a forrásban legalább ennyi tej van. Az állapotok mellé jegyezd meg az előző állapotot és a lépést, hogy a célba érő sorozatot a végétől visszafelé ki tudd olvasni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t[3];
    cin >> t[0] >> t[1] >> t[2];
    int A, B;
    cin >> A >> B;
    int amounts[2] = {A, B};

    int S = t[0] + t[1] + t[2];
    int goal = S / 3;
    int W = S + 1;

    // Állapot: (x, y) az 1. és 2. kanna tartalma, a 3. kanna z = S - x - y
    auto id = [&](int x, int y) { return x * W + y; };
    vector<int> dist(W * W, -1), par(W * W, -1);
    vector<array<int, 3>> how(W * W);  // az állapotba vezető lépés: honnan, hova, mennyi (0-tól számozva)

    int start = id(t[0], t[1]);
    dist[start] = 0;
    queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        int x = cur / W, y = cur % W;
        int c[3] = {x, y, S - x - y};
        for (int from = 0; from < 3; from++) {
            for (int to = 0; to < 3; to++) {
                if (from == to) continue;
                for (int k = 0; k < 2; k++) {
                    int z = amounts[k];
                    if (c[from] < z) continue;
                    int nc[3] = {c[0], c[1], c[2]};
                    nc[from] -= z;
                    nc[to] += z;
                    int nxt = id(nc[0], nc[1]);
                    if (dist[nxt] == -1) {
                        dist[nxt] = dist[cur] + 1;
                        par[nxt] = cur;
                        how[nxt] = {from, to, z};
                        q.push(nxt);
                    }
                }
            }
        }
    }

    int target = id(goal, goal);
    if (dist[target] == -1) {
        cout << -1 << '\n';
        return 0;
    }
    vector<array<int, 3>> moves;
    for (int cur = target; cur != start; cur = par[cur]) moves.push_back(how[cur]);
    reverse(moves.begin(), moves.end());

    cout << moves.size() << '\n';
    for (auto &mv : moves) {
        cout << mv[0] + 1 << ' ' << mv[1] + 1 << ' ' << mv[2] << '\n';
    }
    return 0;
}
