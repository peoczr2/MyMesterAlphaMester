/*
Ha az intervallumokat növekvő jobb végpont szerint nézzük, akkor egy optimális lefedés is láncként épül fel: az
utolsó kiválasztott intervallum csak olyan korábbi lefedéshez csatlakozhat, amely legalább a kezdete előtti utolsó
pontig már eljutott. Így dp[i] legyen a minimális költség, amellyel az [A,vi] szakasz lefedhető úgy, hogy az i-edik
intervallum biztosan szerepel. A szülőmutatóval a minimális lánc visszafejthető.
*/
/*
Hint 1: || Ha az utolsó kiválasztott intervallum [k,v], akkor a korábbi lefedésnek legalább a k-1 pontig el kell jutnia. ||
Hint 2: || Érdemes az intervallumokat a jobb végpontjuk szerint feldolgozni, mert így a részfeladatok természetesen rendezettek. ||
Hint 3: || Az első felhasznált intervallumnak tartalmaznia kell az A pontot, tehát itt a kezdőfeltétel nagyon szigorú. ||
*/

#include <bits/stdc++.h>

using namespace std;

struct Interval {
    int l;
    int r;
    int idx;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A, B;
    cin >> A >> B;
    int n;
    cin >> n;
    vector<Interval> seg(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> seg[i].l >> seg[i].r;
        seg[i].idx = i;
    }

    const int INF = 1e9;
    vector<int> dp(n + 1, INF), parent(n + 1, -1);

    for (int i = 1; i <= n; ++i) {
        int len = seg[i].r - seg[i].l;
        if (seg[i].l == A) {
            dp[i] = len;
        }
        for (int j = 1; j < i; ++j) {
            if (dp[j] == INF || seg[j].r < seg[i].l - 1) {
                continue;
            }
            int cand = dp[j] + len;
            if (cand < dp[i]) {
                dp[i] = cand;
                parent[i] = j;
            }
        }
    }

    int answer = INF;
    int last = -1;
    for (int i = 1; i <= n; ++i) {
        if (seg[i].r == B && dp[i] < answer) {
            answer = dp[i];
            last = i;
        }
    }

    if (last == -1) {
        cout << -1 << '\n';
        return 0;
    }

    vector<int> chosen;
    while (last != -1) {
        chosen.push_back(seg[last].idx);
        last = parent[last];
    }
    reverse(chosen.begin(), chosen.end());

    cout << answer << '\n';
    for (int i = 0; i < (int)chosen.size(); ++i) {
        if (i) {
            cout << ' ';
        }
        cout << chosen[i];
    }
    cout << '\n';
    return 0;
}
