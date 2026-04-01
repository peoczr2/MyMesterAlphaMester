#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
A fa gyökerét mindig megtartjuk, és legfeljebb K csomópontot hagyhatunk meg a gyökér
által meghatározott részfában. Egy csomópontnál meg kell mondanunk, hogy az adott
részfából pontosan hány csomópontot tartunk meg úgy, hogy a kiválasztott csomópontok
összefüggők maradjanak és tartalmazzák az aktuális gyökeret.

Legyen dp[u][s] az a maximális almaszám, amit az u gyökerű részfában pontosan s
megtartott csomóponttal érhetünk el. Az u csomópont mindig benne van a kiválasztott
részfában, ezért dp[u][1] = a[u]. A gyerekek részfáit ezután egymás után hozzáfűzzük:
egy gyerekből vagy 0 csomópontot tartunk meg (ekkor elvágjuk), vagy egy, a gyerekkel
együtt összefüggő részfát.

Mivel minden csomópontnak legfeljebb két gyereke van, a dinamikus programozás minden
csomópontnál két kis vektor összefésülésére korlátozódik. Ez elegendő az N <= 1000
korlát mellett.

Hint 1: || Gondold úgy, hogy a megtartott alakzat mindig egy gyökerezett részfa, ezért az aktuális csomópontot nem lehet kihagyni, ha a részfában bármit megtartunk alatta. ||
Hint 2: || Egy gyerekágat vagy teljesen elvágsz, vagy a gyerekkel együtt egy összefüggő részfát tartasz meg; ez adja a kétállású kombinációt a dinamikában. ||
Hint 3: || Az állapotod legyen a megtartott csomópontok száma, és a két gyereket külön-külön, kis vektorok összefésülésével vezesd be. ||
*/

static const long long NEG = -(1LL << 60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<long long> apples(N + 1);
    vector<int> leftChild(N + 1, -1), rightChild(N + 1, -1);
    vector<int> hasParent(N + 1, 0);

    for (int id = 1; id <= N; ++id) {
        int l, r;
        long long a;
        cin >> a >> l >> r;
        apples[id] = a;
        leftChild[id] = l;
        rightChild[id] = r;
        if (l != -1) hasParent[l] = 1;
        if (r != -1) hasParent[r] = 1;
    }

    int root = 1;
    for (int i = 1; i <= N; ++i) {
        if (!hasParent[i]) {
            root = i;
            break;
        }
    }

    function<vector<long long>(int)> dfs = [&](int u) -> vector<long long> {
        vector<long long> cur(2, NEG);
        cur[1] = apples[u];

        auto combine_child = [&](const vector<long long>& child) {
            vector<long long> next(min<int>(K, (int)cur.size() + (int)child.size() - 1) + 1, NEG);
            int curMax = (int)cur.size() - 1;
            int childMax = (int)child.size() - 1;
            for (int s = 1; s <= curMax; ++s) {
                if (cur[s] == NEG) continue;
                next[s] = max(next[s], cur[s]);
                for (int t = 1; t <= childMax && s + t <= K; ++t) {
                    if (child[t] == NEG) continue;
                    next[s + t] = max(next[s + t], cur[s] + child[t]);
                }
            }
            cur.swap(next);
        };

        if (leftChild[u] != -1) {
            combine_child(dfs(leftChild[u]));
        }
        if (rightChild[u] != -1) {
            combine_child(dfs(rightChild[u]));
        }

        return cur;
    };

    vector<long long> ans = dfs(root);
    long long best = 0;
    for (int s = 1; s < (int)ans.size() && s <= K; ++s) {
        best = max(best, ans[s]);
    }

    cout << best << '\n';
    return 0;
}