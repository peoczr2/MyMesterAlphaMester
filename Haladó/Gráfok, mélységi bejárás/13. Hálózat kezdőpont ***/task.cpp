/*
Megoldás lényege:
Az élek irányított gráfot alkotnak. Először az erősen összefüggő komponenseket keressük meg Tarjan-algoritmussal (mélységi bejárással), majd a komponensekből álló kondenzált gráfot vizsgáljuk. Forrásnak nevezünk egy komponenst, ha nem fut bele él a többi komponensből, vagyis csak új élen át lehet elérni. Minden csomópont elérhető valamelyik forrásból, ezért elég a forrásokat egymással összekötni. Ha R egy forráskomponensben van, akkor a k forrás közül a többi k-1 forrásba új élen át lehet eljutni, és egy új él egyetlen komponensbe érkezik, így k-1 új él szükséges és elegendő. A forrásokat láncba fűzve R-ből minden csomópont elérhető. Az időigény O(N+M).
*/
/*
Hint 1: || Nézd meg, mely csomópontokba nem fut be egyetlen másik csomópontból sem él. Az erősen összefüggő komponenseket érdemes egy csomópontnak tekinteni, mert köztük bármerre el lehet jutni. ||
Hint 2: || Ha k ilyen „bemenet nélküli” komponens van, a többi ilyen komponenst egy-egy új éllel kell elérni, és egy új él csak egy komponensbe mutat. Így a válasz k-1, és R bármelyik ilyen komponens egy csomópontja lehet. ||
Hint 3: || Az új éleket láncba fűzheted: R-ből az első másik forráshoz, onnan a következőhöz, és így tovább. A forrásokat bármilyen sorrendben végigveheted. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> g;
vector<int> idx_, low_, comp, stk;
vector<char> onStk;
int timer_ = 0, compCnt = 0;

void tarjan(int v) {
    idx_[v] = low_[v] = ++timer_;
    stk.push_back(v);
    onStk[v] = 1;
    for (int u : g[v]) {
        if (!idx_[u]) {
            tarjan(u);
            low_[v] = min(low_[v], low_[u]);
        } else if (onStk[u]) {
            low_[v] = min(low_[v], idx_[u]);
        }
    }
    if (low_[v] == idx_[v]) {
        while (true) {
            int w = stk.back();
            stk.pop_back();
            onStk[w] = 0;
            comp[w] = compCnt;
            if (w == v) break;
        }
        ++compCnt;
    }
}

int main() {
    cin >> n >> m;
    g.assign(n + 1, {});
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    idx_.assign(n + 1, 0);
    low_.assign(n + 1, 0);
    comp.assign(n + 1, -1);
    onStk.assign(n + 1, 0);
    for (int v = 1; v <= n; ++v)
        if (!idx_[v]) tarjan(v);

    vector<int> rep(compCnt, INT_MAX);
    for (int v = 1; v <= n; ++v) rep[comp[v]] = min(rep[comp[v]], v);

    vector<char> hasIn(compCnt, 0);
    for (int v = 1; v <= n; ++v)
        for (int u : g[v])
            if (comp[u] != comp[v]) hasIn[comp[u]] = 1;

    vector<int> src;
    for (int c = 0; c < compCnt; ++c)
        if (!hasIn[c]) src.push_back(rep[c]);
    sort(src.begin(), src.end());

    int R = src.back();
    cout << R << "\n";
    cout << (int)src.size() - 1 << "\n";
    int prev = R;
    for (size_t i = 0; i + 1 < src.size(); ++i) {
        cout << prev << ' ' << src[i] << "\n";
        prev = src[i];
    }
    return 0;
}
