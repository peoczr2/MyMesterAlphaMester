/*
Megoldás lényege:
A dobozok állapota láncok összessége: minden doboz legfeljebb egy másik dobozban
lehet közvetlenül, és minden doboz legfeljebb egy dobozt tartalmazhat közvetlenül.
Egy lépés mindig pontosan egy doboz szülőviszonyát változtatja meg: vagy egy
szabad dobozt teszünk egy üres szabad dobozba (0 -> nem 0), vagy egy nem üres
szabad dobozból kivesszük a benne lévő dobozt (nem 0 -> 0).

Ezért minden doboz hozzájárulása független:
- ha a kezdeti és a cél szülő ugyanaz, akkor 0,
- ha az egyik 0, a másik nem, akkor 1,
- ha mindkettő nem 0, de különböző, akkor 2.

Az összegük adja a minimális lépésszámot.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> start(n + 1), target(n + 1);
    for (int i = 1; i <= n; ++i) cin >> start[i];
    for (int i = 1; i <= n; ++i) cin >> target[i];

    long long answer = 0;
    for (int i = 1; i <= n; ++i) {
        if (start[i] == target[i]) continue;
        if (start[i] == 0 || target[i] == 0) answer += 1;
        else answer += 2;
    }

    cout << answer << '\n';
    return 0;
}