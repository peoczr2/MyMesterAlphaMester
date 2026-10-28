/*
Megoldás lényege:
A feltétel miatt a főtérből minden kereszteződésbe pontosan egy egyszerű út vezet, ezért a főtérből induló bejárás fája egyértelmű. Ebből következik, hogy minden fa-élen kívüli él egy felmenő kereszteződésbe mutat. A fa-éleken lefelé lehet menni, a többi élen csak felfelé. Ezért a fát bejárjuk, és amikor egy részfából vissza kell jutni, a részfából elérhető legfelsőbb ős felé megyünk, majd onnan lefelé a fán visszatérünk a szülőhöz. Minden részfához kiszámoljuk, melyik legfelső ősbe lehet kijutni belőle, így a kijáratot egyszer, előre meghatározhatjuk. A sorozat az összes csúcsot tartalmazza, és az utolsó kereszteződésből van út a főtérre.
*/
/*
Hint 1: || A főtérből minden kereszteződésbe egyetlen út vezet, ezért a főtérből induló bejárás fája egyértelmű. A fa-éleken kívül minden él egy felmenő csúcsba mutat. ||
Hint 2: || Egy részfából csak felfelé lehet kijutni. Minden csúcsra számold ki, melyik legfelsőbb ősbe jut vissza a részfájából, és a szülőhöz visszatérve a fa mentén lefelé haladj. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> startIdx, adjList;   // kimenő élek CSR-formában
vector<int> parentOf, depthOf, ownT, lowT, exitChild;
vector<vector<int>> children;
bool firstOut = true;

// A kimenet pufferelt: a számokat a pufferbe írjuk, és nagy darabokban adjuk át a cout-nak
const int OBUF = 1 << 16;
char obuf[OBUF];
int opos = 0;

void flushOut() {
    cout.write(obuf, opos);
    opos = 0;
}

void emit(int x) {
    if (opos > OBUF - 16) flushOut();
    if (!firstOut) obuf[opos++] = ' ';
    firstOut = false;
    char tmp[12];
    int len = 0;
    do {
        tmp[len++] = char('0' + x % 10);
        x /= 10;
    } while (x > 0);
    while (len > 0) obuf[opos++] = tmp[--len];
}

// A t ősből lefelé a u csúcsig írja az utat: t-t nem, u-t igen
void descendTo(int t, int u) {
    vector<int> path;
    for (int x = u; x != t && x != 0; x = parentOf[x]) path.push_back(x);
    for (int i = (int)path.size() - 1; i >= 0; --i) emit(path[i]);
}

// Az u csúcsba érkezve bejárja az u részfáját. A sorozat a részfa kijáratánál ér véget.
void visit(int u) {
    emit(u);
    int ex = exitChild[u];   // ha -1, a kijárat u saját felmenő élén van
    for (int c : children[u]) {
        if (c == ex) continue;
        visit(c);
        int t = lowT[c];     // a c részfából ide lehet felmenni
        emit(t);
        descendTo(t, u);     // a t-ből lefelé vissza u-ba
    }
    if (ex != -1) visit(ex);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    vector<int> eu(m), ev(m);
    startIdx.assign(n + 2, 0);
    for (int i = 0; i < m; ++i) {
        cin >> eu[i] >> ev[i];
        ++startIdx[eu[i] + 1];
    }
    for (int k = 1; k <= n + 1; ++k) startIdx[k] += startIdx[k - 1];
    adjList.assign(m, 0);
    {
        vector<int> pos(startIdx);
        for (int i = 0; i < m; ++i) adjList[pos[eu[i]]++] = ev[i];
    }
    vector<int>().swap(eu);
    vector<int>().swap(ev);

    // BFS a főtérből: a fa, a szülők és a mélységek
    parentOf.assign(n + 1, -1);
    depthOf.assign(n + 1, -1);
    vector<int> order = {1};
    depthOf[1] = 0;
    parentOf[1] = 0;
    for (size_t i = 0; i < order.size(); ++i) {
        int u = order[i];
        for (int k = startIdx[u]; k < startIdx[u + 1]; ++k) {
            int v = adjList[k];
            if (depthOf[v] == -1) {
                depthOf[v] = depthOf[u] + 1;
                parentOf[v] = u;
                order.push_back(v);
            }
        }
    }

    // Minden csúcsból közvetlenül elérhető legfelső ős (a fa-élen kívüli élek)
    ownT.assign(n + 1, -1);
    for (int u = 1; u <= n; ++u)
        for (int k = startIdx[u]; k < startIdx[u + 1]; ++k) {
            int t = adjList[k];
            if (parentOf[t] == u) continue;
            if (ownT[u] == -1 || depthOf[t] < depthOf[ownT[u]]) ownT[u] = t;
        }

    children.assign(n + 1, {});
    for (int v : order)
        if (v != 1) children[parentOf[v]].push_back(v);

    // Részfánként a legfelsőbb elérhető ős (lowT) és a kijáratot adó gyerek (exitChild)
    lowT.assign(n + 1, -1);
    exitChild.assign(n + 1, -1);
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int u = order[i];
        int best = ownT[u];
        int bestDepth = (best == -1) ? INT_MAX : depthOf[best];
        int ex = -1;
        for (int c : children[u])
            if (lowT[c] != -1 && depthOf[lowT[c]] < bestDepth) {
                bestDepth = depthOf[lowT[c]];
                best = lowT[c];
                ex = c;
            }
        lowT[u] = best;
        exitChild[u] = ex;
    }

    visit(1);
    if (opos > OBUF - 2) flushOut();
    obuf[opos++] = '\n';
    flushOut();
    return 0;
}
