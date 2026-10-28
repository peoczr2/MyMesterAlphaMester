/*
Megoldás lényege:
Minden tanulóból pontosan két irányított él indul a két osztálytársához, így a tanulók irányított gráfot alkotnak. Tarjan-algoritmussal megkeressük az erősen összefüggő komponenseket: egy komponens tagjai egymásnak továbbadják a hírt, ezért elég egy tagjukat megkapnia. Azokat a komponenseket kell közvetlenül értesíteni, amelyekbe nem fut be él másik komponensből, mert ezekbe kívülről csak új hírrel lehet eljutni. Minden ilyen forrás-komponenshez pontosan egy kezdő tanuló kell, és ez elég is, mert minden tanuló valamelyik forrásból elérhető. A válasz tehát a forrás-komponensek száma, az időigény O(N).
*/
/*
Hint 1: || A tanulók irányított gráfot alkotnak, és a hír azokhoz jut el, akik a kiindulóból elérhetők. Az erősen összefüggő komponensek egy csomópontként kezelhetők, mert ott a hír végigmegy. ||
Hint 2: || Egy komponensbe a hír kívülről csak akkor juthat be, ha van hozzá befutó él másik komponensből. Azokat a komponenseket, amelyekbe nincs ilyen él, külön kell értesíteni. ||
Hint 3: || Minden ilyen forrás-komponensből pontosan egy tanulónak kell új hírt adni, és ez elég is, mert minden tanuló valamelyik forrásból elérhető. A kimenetben az ilyen komponensek egy-egy tanulóját írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

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
    int n;
    cin >> n;
    g.assign(n + 1, {});
    for (int i = 1; i <= n; ++i) {
        int a, b;
        cin >> a >> b;
        g[i].push_back(a);
        g[i].push_back(b);
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
    sort(src.rbegin(), src.rend());

    cout << src.size() << "\n";
    for (size_t i = 0; i < src.size(); ++i)
        cout << src[i] << (i + 1 < src.size() ? ' ' : '\n');
    return 0;
}
