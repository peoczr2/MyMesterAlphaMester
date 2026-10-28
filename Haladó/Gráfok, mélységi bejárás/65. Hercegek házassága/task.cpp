/*
Megoldás lényege:
Adott egy jó párosítás, és azt kell eldönteni, mely (herceg, lány) párok szerepelhetnek valamely másik jó párosításban is. Egy herceg akkor kaphat másik lányt, ha a cserék alternáló körként zárulnak, vagyis egy körben mindenki a következő herceg feleségét kapja. Ezért építsünk irányított gráfot a hercegekre: i-ből k-ba mutat él, ha az i herceg kedveli a k herceg feleségét. Az i herceg pontosan akkor kaphatja meg a k herceg feleségét, ha i és k ugyanabban az erősen összefüggő komponensben van. Az erősen összefüggő komponenseket Tarjan-algoritmussal keressük meg, az időigény O(N + ΣK_i).
*/
/*
Hint 1: || A jó párosítás cseréi körökké állnak össze: ha egy herceg másik lányt kap, valakinek ki kell cserélnie a jelenlegi feleségét, és ez addig folytatódik, míg vissza nem érünk az elsőhöz. ||
Hint 2: || Építs irányított gráfot a hercegekre: i-ből k-ba mutasson él, ha az i herceg kedveli a k herceg Merlin-féle feleségét. Ebben a gráfban a cserekörök irányított körök. ||
Hint 3: || Az i herceg pontosan akkor kaphatja meg a k herceg feleségét, ha i és k ugyanabban az erősen összefüggő komponensben van; ezt Tarjan-algoritmussal határozd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;  // g[i]: az i herceg által kedvelt lányok párjai (hercegek)
vector<int> idxT, low, compOf, st;
vector<char> onStack;
int tick = 0, compCnt = 0;

// Tarjan-algoritmus az erősen összefüggő komponensekre.
void tarjan(int v) {
    idxT[v] = low[v] = ++tick;
    st.push_back(v);
    onStack[v] = 1;
    for (int w : g[v]) {
        if (!idxT[w]) {
            tarjan(w);
            low[v] = min(low[v], low[w]);
        } else if (onStack[w]) {
            low[v] = min(low[v], idxT[w]);
        }
    }
    if (low[v] == idxT[v]) {
        while (true) {
            int w = st.back();
            st.pop_back();
            onStack[w] = 0;
            compOf[w] = compCnt;
            if (w == v) break;
        }
        ++compCnt;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> likes(n + 1);
    for (int i = 1; i <= n; ++i) {
        int k;
        cin >> k;
        likes[i].resize(k);
        for (int &x : likes[i]) cin >> x;
    }
    vector<int> owner(n + 1, 0);  // owner[lány] = a lány jelenlegi párja (herceg)
    for (int i = 1; i <= n; ++i) {
        int h;
        cin >> h;
        owner[h] = i;
    }

    g.assign(n + 1, {});
    for (int i = 1; i <= n; ++i)
        for (int j : likes[i]) g[i].push_back(owner[j]);

    idxT.assign(n + 1, 0);
    low.assign(n + 1, 0);
    compOf.assign(n + 1, -1);
    onStack.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i)
        if (!idxT[i]) tarjan(i);

    for (int i = 1; i <= n; ++i) {
        vector<int> ok;
        for (int j : likes[i])
            if (compOf[owner[j]] == compOf[i]) ok.push_back(j);
        sort(ok.begin(), ok.end());
        cout << ok.size();
        for (int j : ok) cout << ' ' << j;
        cout << '\n';
    }
    return 0;
}
