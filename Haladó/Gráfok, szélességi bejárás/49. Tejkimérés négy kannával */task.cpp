/*
Megoldás lényege:
A tej teljes mennyisége állandó (A liter), ezért a négy kanna közül elég három mennyiségét állapotként tárolni, a
negyedik ebből kijön. A D kanna űrtartalma ismeretlen, de ő a legnagyobb, így oda mindig befér az egész öntött
mennyiség. Két kanna között egy lépés egyértelmű: vagy a forrás teljes tartalma megy át, vagy annyi, amennyi a
cél megtöltéséhez kell. Szélességi bejárást futtatunk az állapottéren a kezdeti állapotból, így az első olyan
állapot, amelyben D-ben L liter van, legkevesebb lépésből érhető el. A lépéseket a szülő-állapotokból visszafelé
rakjuk össze. Az állapotok száma legfeljebb (A + 1)^3, így az időigény kicsi.
*/
/*
Hint 1: || A tej teljes mennyisége állandó, ezért a négy kanna közül elég három mennyiségét nyilvántartani, a negyediket az összegből kapod. Mivel minden lépés egyforma költségű, szélességi bejárás adja a legkevesebb lépést. ||
Hint 2: || Két kanna között egy lépésnél a forrás teljes tartalma megy át, vagy annyi, amennyi a cél megtöltéséhez kell. D-be mindig az egész forrás befér, mert D a legnagyobb. Az állapotot egy háromdimenziós tömbben tárold, és a célba érő lépéseket a szülő-tömbből fordítva olvasd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A, B, C, L;
    cin >> A >> B >> C >> L;

    // Kannák indexe: 0 = A, 1 = B, 2 = C, 3 = D. D űrtartalmát nem ismerjük, de a legnagyobb,
    // így a teljes tej (A liter) mindig befér D-be.
    int cap[3] = {A, B, C};
    const char name[4] = {'A', 'B', 'C', 'D'};
    // Lehetséges lépések
    const int order[12][2] = {{0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 2}, {1, 3},
                              {2, 0}, {2, 1}, {2, 3}, {3, 0}, {3, 1}, {3, 2}};

    // Állapot: (a, b, c), a D kanna tartalma A - a - b - c
    int W = A + 1;
    auto id = [&](int a, int b, int c) { return (a * W + b) * W + c; };
    int total = W * W * W;
    vector<int> dist(total, -1), par(total, -1);
    vector<pair<int, int>> how(total);  // az állapotba vezető lépés: honnan, hova

    int start = id(A, 0, 0);
    dist[start] = 0;
    queue<int> q;
    q.push(start);

    int found = -1;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        int c[4];
        c[2] = cur % W;
        int rest = cur / W;
        c[1] = rest % W;
        c[0] = rest / W;
        c[3] = A - c[0] - c[1] - c[2];
        if (c[3] == L) {
            found = cur;
            break;
        }
        for (auto &o : order) {
            int x = o[0], y = o[1];
            // Ha Y-ba befér az egész X-tartalom, mind átmegy; különben annyi, hogy Y tele legyen.
            // D-be (y == 3) mindig befér.
            int amount = (y == 3) ? c[x] : min(c[x], cap[y] - c[y]);
            if (amount == 0) continue;
            int nc[4] = {c[0], c[1], c[2], c[3]};
            nc[x] -= amount;
            nc[y] += amount;
            int nxt = id(nc[0], nc[1], nc[2]);
            if (dist[nxt] == -1) {
                dist[nxt] = dist[cur] + 1;
                par[nxt] = cur;
                how[nxt] = {x, y};
                q.push(nxt);
            }
        }
    }

    if (found == -1) {
        cout << -1 << '\n';
        return 0;
    }
    vector<pair<int, int>> steps;
    for (int cur = found; cur != start; cur = par[cur]) steps.push_back(how[cur]);
    reverse(steps.begin(), steps.end());

    cout << steps.size() << '\n';
    for (auto &s : steps) cout << name[s.first] << name[s.second] << '\n';
    return 0;
}
