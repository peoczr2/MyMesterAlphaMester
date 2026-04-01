/*
Megoldási ötlet:
Egy állomásról csak olyan másikba mehetünk, amelynek mindkét koordinátája nem kisebb. Ez egy súlyozott kétdimenziós részben rendezett
láncmaximalizálás: a pontokat x, majd y szerint rendezzük, és minden állomáshoz megkeressük a legjobb korábbi állomást, amelynek y-ja
nem nagyobb.

Ezt Fenwick-fával lehet gyorsítani. A BIT minden y-prefixre a legnagyobb elérhető pontszámot és annak utolsó állomását tárolja. A
szülőmutatókból a végén visszaállítható az optimális útvonal.
*/
/*
Hint 1: || A feltétel pontosan azt mondja, hogy egy nemcsökkenő koordinátájú láncot keresel. ||
Hint 2: || Ha x szerint rendezel, akkor már csak azt kell tudni gyorsan, melyik korábbi állomás a legjobb y szerint. ||
Hint 3: || Erre egy prefixmaximumot tároló Fenwick-fa jó. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Station {
    int x;
    int y;
    int p;
    int id;
};

struct Best {
    long long score;
    int idx;
};

struct Fenwick {
    int n;
    vector<Best> bit;
    Fenwick(int n) : n(n), bit(n + 1, {0, 0}) {}

    void update(int idx, Best val) {
        for (; idx <= n; idx += idx & -idx) {
            if (val.score > bit[idx].score) bit[idx] = val;
        }
    }

    Best query(int idx) const {
        Best res{0, 0};
        for (; idx > 0; idx -= idx & -idx) {
            if (bit[idx].score > res.score) res = bit[idx];
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Station> a(n + 1);
    int maxY = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].x >> a[i].y >> a[i].p;
        a[i].id = i;
        maxY = max(maxY, a[i].y);
    }

    sort(a.begin() + 1, a.end(), [](const Station& lhs, const Station& rhs) {
        if (lhs.x != rhs.x) return lhs.x < rhs.x;
        if (lhs.y != rhs.y) return lhs.y < rhs.y;
        return lhs.id < rhs.id;
    });

    Fenwick fw(maxY + 2);
    vector<long long> dp(n + 1, 0);
    vector<int> parent(n + 1, 0);

    long long bestScore = 0;
    int bestIdx = 0;
    for (int i = 1; i <= n; ++i) {
        Best prev = fw.query(a[i].y + 1);
        dp[i] = prev.score + a[i].p;
        parent[i] = prev.idx;
        fw.update(a[i].y + 1, {dp[i], i});
        if (dp[i] > bestScore) {
            bestScore = dp[i];
            bestIdx = i;
        }
    }

    vector<int> path;
    for (int cur = bestIdx; cur != 0; cur = parent[cur]) path.push_back(a[cur].id);
    reverse(path.begin(), path.end());

    cout << bestScore << '\n';
    for (int i = 0; i < (int)path.size(); ++i) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << '\n';
    return 0;
}