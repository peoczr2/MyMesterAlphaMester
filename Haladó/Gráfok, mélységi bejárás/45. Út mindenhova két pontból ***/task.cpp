/*
Megoldás lényege:
Egy erősen összefüggő komponens forrás, ha nem kap élt más komponensből. Egy forrás-komponens pontjait csak onnan kezdett bejárás érheti el, ezért minden forrás-komponensből kell legalább egy kezdőpont. A feladat garantálja a megoldást, így legfeljebb két forrás van: az egyikből lesz A, a másikból B. Ha csak egy forrás van, abból bármely pont jó A-nak, mert minden más komponens elérhető belőle, B pedig legyen egy másik tetszőleges pont. Az erősen összefüggő komponenseket Tarjan-algoritmussal kapjuk meg, az időigény O(N+M).
*/
/*
Hint 1: || Vedd az erősen összefüggő komponenseket, és nézd meg, melyikbe nem vezet él másik komponensből. Ezek a komponensek kívülről nem érhetők el. ||
Hint 2: || Minden ilyen komponensből kell legalább egy kezdőpont, különben a pontjait senki nem érné el. A feladat szerint van megoldás, ezért ilyen komponens legfeljebb kettő lehet. ||
Hint 3: || Tarjan-algoritmussal (egy mélységi bejárással) kapod az erősen összefüggő komponenseket. Ha két ilyen komponens van, az egyik pontja legyen A, a másiké B; ha egy van, B legyen egy másik pont. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<int> idxOf, lowOf, compOf, stk;
vector<char> onStk;
int timerCnt = 0, compCnt = 0;

void tarjan(int v) {
    idxOf[v] = lowOf[v] = ++timerCnt;
    stk.push_back(v);
    onStk[v] = 1;
    for (int to : g[v]) {
        if (!idxOf[to]) {
            tarjan(to);
            lowOf[v] = min(lowOf[v], lowOf[to]);
        } else if (onStk[to]) {
            lowOf[v] = min(lowOf[v], idxOf[to]);
        }
    }
    if (lowOf[v] == idxOf[v]) {
        ++compCnt;
        int w;
        do {
            w = stk.back();
            stk.pop_back();
            onStk[w] = 0;
            compOf[w] = compCnt;
        } while (w != v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    g.assign(n + 1, {});
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    idxOf.assign(n + 1, 0);
    lowOf.assign(n + 1, 0);
    compOf.assign(n + 1, 0);
    onStk.assign(n + 1, 0);
    for (int v = 1; v <= n; ++v)
        if (!idxOf[v]) tarjan(v);

    vector<int> indeg(compCnt + 1, 0), rep(compCnt + 1, 0);
    for (int v = 1; v <= n; ++v) rep[compOf[v]] = v;
    for (int u = 1; u <= n; ++u)
        for (int v : g[u])
            if (compOf[u] != compOf[v]) indeg[compOf[v]]++;

    vector<int> sources;
    for (int c = 1; c <= compCnt; ++c)
        if (indeg[c] == 0) sources.push_back(rep[c]);

    int a = sources[0];
    int b = (a == 1 && n >= 2) ? 2 : 1;  // egy forrás esetén B egy másik pont
    if (sources.size() >= 2) b = sources[1];
    cout << a << ' ' << b << '\n';
    return 0;
}
