/*
Megoldás lényege:
Egy v csúcs (A-n és B-n kívül) pontosan akkor kritikus, ha minden A-ból B-be vezető úton rajta van, vagyis a v dominálja B-t az A gyökerű irányított gráfban. A dominátorok a dominátorfában B szülői láncán vannak A-ig, ezért elég ezt a fát kiszámolni. A dominátorfát Lengauer–Tarjan-algoritmussal építjük fel: egy mélységi bejárás sorszámaiból indulunk, majd fordított sorrendben a semi-értékeket, a bucket-eket és az eval/link (útkompressziós) műveleteket használjuk. Az időigény O(M log N), ami a korlátok mellett bőven belefér az időlimitbe. Ha B nem érhető el A-ból, a definíció szerint minden más csúcs kritikus.
*/
/*
Hint 1: || Keresd azokat a csúcsokat, amelyek minden A-ból B-be vezető úton rajta vannak. Ezek a B csúcs dominátorai az A gyökerű irányított gráfban. ||
Hint 2: || A dominátorfában (közvetlen dominátor, idom) B szülő-láncolata A-ig pontosan a kritikus csúcsok listája. A fát Lengauer–Tarjan-algoritmussal építsd: a semi-értékek a DFS-sorszámok, az eval/link pedig láncokon út-kompressziót végez. ||
Hint 3: || Lépések: 1) mélységi bejárás A-ból, sorszámok és szülők; 2) a sorszám szerint fordított sorrendben semi-minimumok és bucket-ek; 3) közvetlen dominátorok javítása sorrendben; 4) B-ből az idom-láncon A-ig gyűjtsd a csúcsokat, A és B kivételével. ||
*/
#include <bits/stdc++.h>
using namespace std;

int N;
vector<vector<int>> succ, pred;
vector<int> semi, vert, par, anc, lab, idom;
vector<vector<int>> bucket;
int cnt = 0;

void dfs(int v) {
    semi[v] = ++cnt;
    vert[cnt] = v;
    lab[v] = v;
    for (int w : succ[v])
        if (semi[w] == 0) {
            par[w] = v;
            dfs(w);
        }
}

void compress(int v) {
    if (anc[anc[v]] != 0) {
        compress(anc[v]);
        if (semi[lab[anc[v]]] < semi[lab[v]]) lab[v] = lab[anc[v]];
        anc[v] = anc[anc[v]];
    }
}

int eval(int v) {
    if (anc[v] == 0) return v;
    compress(v);
    return lab[v];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, a, b;
    cin >> N >> m >> a >> b;
    succ.assign(N + 1, {});
    pred.assign(N + 1, {});
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        succ[u].push_back(v);
        pred[v].push_back(u);
    }

    semi.assign(N + 1, 0);
    vert.assign(N + 1, 0);
    par.assign(N + 1, 0);
    anc.assign(N + 1, 0);
    lab.assign(N + 1, 0);
    idom.assign(N + 1, 0);
    bucket.assign(N + 1, {});

    dfs(a);

    vector<int> ans;
    if (semi[b] == 0) {
        // B nem érhető el A-ból: minden más csúcs kritikus
        for (int v = 1; v <= N; ++v)
            if (v != a && v != b) ans.push_back(v);
    } else {
        for (int i = cnt; i >= 2; --i) {
            int w = vert[i];
            for (int v : pred[w]) {
                if (semi[v] == 0) continue;
                int u = eval(v);
                if (semi[u] < semi[w]) semi[w] = semi[u];
            }
            bucket[vert[semi[w]]].push_back(w);
            anc[w] = par[w];  // link(par[w], w)
            for (int y : bucket[par[w]]) {
                int u = eval(y);
                idom[y] = (semi[u] < semi[y]) ? u : par[w];
            }
            bucket[par[w]].clear();
        }
        for (int i = 2; i <= cnt; ++i) {
            int w = vert[i];
            if (idom[w] != vert[semi[w]]) idom[w] = idom[idom[w]];
        }
        for (int v = idom[b]; v != a && v != 0; v = idom[v]) ans.push_back(v);
    }

    cout << ans.size() << "\n";
    for (size_t i = 0; i < ans.size(); ++i) cout << ans[i] << (i + 1 < ans.size() ? ' ' : '\n');
    if (ans.empty()) cout << "\n";
    return 0;
}
