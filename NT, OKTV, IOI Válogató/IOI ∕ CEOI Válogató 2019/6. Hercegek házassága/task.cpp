/*
Megoldás lényege:
Egy herceg–lány pár akkor szerepelhet megoldásban, ha van olyan teljes párosítás, amelyben a herceg éppen azt a lányt kapja. Merlin párosításából kiindulva ez úgy érhető el, hogy a herceg átveszi a lányt, a lány korábbi párja másik lányt kap, és így tovább, amíg a lánc vissza nem ér az eredeti herceghez; ez egy váltakozó kör. Ezt irányított gráfként modellezzük: i → k akkor, ha az i herceg kedveli azt a lányt, aki Merlin szerint k felesége. Egy i → k él pontosan akkor esik körbe, ha k és i ugyanabban az erősen összefüggő komponensben van. A komponenseket Tarjan-algoritmussal határozzuk meg. Végül minden hercegre azok a lányok kerülnek a listába, akiket kedvel, és akiknek Merlin szerinti párja ugyanabban a komponensben van, mint ő. Az időigény O(N + ΣKi).
*/
/*
Hint 1: || Egy (herceg i, lány g) pár akkor jó, ha van olyan teljes párosítás, amelyben i pont g-vel párosodik. Merlin párosításából indulva körkeresés adja ezt: i átveszi g-t, g korábbi párja másik lányt kap, és így tovább, amíg vissza nem érsz i-hez. ||
Hint 2: || Készíts irányított gráfot a hercegekből: i → k, ha i kedveli azt a lányt, aki Merlin szerint k felesége. Az i → k él akkor van körben, ha van út k-ból i-be, vagyis ha i és k ugyanabban az erősen összefüggő komponensben van. ||
Hint 3: || Tarjan-algoritmussal határozd meg az erősen összefüggő komponenseket. Egy i herceghez azt a g lányt írd ki, amelyet kedvel, és amelynek Merlin-párja (inverz tömb) ugyanabban a komponensben van, mint i. A listát rendezd növekvő sorrendbe. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> g;  // irányított gráf a hercegeken
vector<int> idx, low_, comp, stk;
vector<bool> onStk;
int timer_ = 0, compCnt = 0;

void tarjan(int v) {
    idx[v] = low_[v] = timer_++;
    stk.push_back(v);
    onStk[v] = true;
    for (int u : g[v]) {
        if (idx[u] == -1) {
            tarjan(u);
            low_[v] = min(low_[v], low_[u]);
        } else if (onStk[u]) {
            low_[v] = min(low_[v], idx[u]);
        }
    }
    if (low_[v] == idx[v]) {
        while (true) {
            int w = stk.back();
            stk.pop_back();
            onStk[w] = false;
            comp[w] = compCnt;
            if (w == v) break;
        }
        compCnt++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    vector<vector<int>> likes(n + 1);
    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;
        likes[i].resize(k);
        for (auto &x : likes[i]) cin >> x;
    }
    vector<int> h(n + 1), inv(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        inv[h[i]] = i;
    }

    g.assign(n + 1, {});
    for (int i = 1; i <= n; i++)
        for (int girl : likes[i]) g[i].push_back(inv[girl]);

    idx.assign(n + 1, -1);
    low_.assign(n + 1, 0);
    comp.assign(n + 1, -1);
    onStk.assign(n + 1, false);
    for (int v = 1; v <= n; v++)
        if (idx[v] == -1) tarjan(v);

    for (int i = 1; i <= n; i++) {
        vector<int> ans;
        for (int girl : likes[i])
            if (comp[inv[girl]] == comp[i]) ans.push_back(girl);
        sort(ans.begin(), ans.end());
        cout << ans.size();
        for (int x : ans) cout << " " << x;
        cout << "\n";
    }
    return 0;
}
