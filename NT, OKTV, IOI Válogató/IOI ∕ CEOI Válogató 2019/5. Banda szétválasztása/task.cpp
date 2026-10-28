/*
Megoldás lényege:
Egy bandatag letartóztatása azt jelenti, hogy a gráfból egy csúcsot törlünk, és meg kell számolni a maradék összefüggő részeket. Ez az artikulációs pontok keresésével oldható meg egyetlen mélységi bejárással (DFS): a v csúcs DFS-fájában azok a gyerekek válnak külön részé, amelyek részfájából nem lehet v fölé ugrani (low[gyerek] >= disc[v]). Ezek részfáinak méretét összegezve a v-t tartalmazó maradék rész mérete is megkapható, így minden csúcs részszáma és legnagyobb bandája O(1) költséggel adódik. Ha a gráf nem összefüggő, a többi komponens változatlanul megmarad, ezért a v-n kívüli legnagyobb komponenst is figyelembe vesszük. A kiválasztás: előbb a legtöbb rész, azonos résznél a legkisebb legnagyobb banda, végül a legkisebb sorszám. Az időigény O(N + M).
*/
/*
Hint 1: || Keresd meg az artikulációs pontokat: ezek törlése szétesést okoz a gráfban. Egy csúcs törlése után a banda részeinek száma a DFS-fa szerkezetéből kiolvasható. ||
Hint 2: || Mélységi bejárásnál számold ki minden csúcsra a disc (felfedezési sorszám) és a low (a részfából visszafelé elérhető legkisebb disc) értékét. Ha a v egy gyerekére low[gyerek] >= disc[v], akkor a gyerek részfája külön bandává válik v törlése után. ||
Hint 3: || Minden csúcsnál a leválasztott gyerekek részfáinak méretéből és a maradék részből (N − 1 − a leválasztott részek mérete) kiszámolható a részek száma és a legnagyobb rész. Ezt minden csúcsra kiszámolva válassz a három szempont szerint. ||
*/
#include <bits/stdc++.h>
using namespace std;

static char ibuf[1 << 16];
static size_t ipos = 0, ilen = 0;

int gc() {
    if (ipos == ilen) {
        ilen = fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return ibuf[ipos++];
}

int readInt() {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9')) c = gc();
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return x;
}

int n, m;
vector<vector<int>> adj;
vector<int> disc, low_, sz, compOf, sepCnt, sepSum, sepMax;
int timer_ = 0, curComp = 0;

void dfs(int v, int p) {
    disc[v] = low_[v] = timer_++;
    compOf[v] = curComp;
    sz[v] = 1;
    for (int u : adj[v]) {
        if (u == p) continue;
        if (disc[u] != -1) {
            low_[v] = min(low_[v], disc[u]);
        } else {
            dfs(u, v);
            sz[v] += sz[u];
            low_[v] = min(low_[v], low_[u]);
            if (low_[u] >= disc[v]) {
                sepCnt[v]++;
                sepSum[v] += sz[u];
                sepMax[v] = max(sepMax[v], sz[u]);
            }
        }
    }
}

int main() {
    n = readInt();
    m = readInt();
    adj.assign(n + 1, {});
    for (int i = 0; i < m; i++) {
        int a = readInt(), b = readInt();
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    disc.assign(n + 1, -1);
    low_.assign(n + 1, 0);
    sz.assign(n + 1, 0);
    compOf.assign(n + 1, -1);
    sepCnt.assign(n + 1, 0);
    sepSum.assign(n + 1, 0);
    sepMax.assign(n + 1, 0);

    vector<int> compSize;
    for (int v = 1; v <= n; v++) {
        if (disc[v] != -1) continue;
        dfs(v, 0);
        compSize.push_back(sz[v]);
        curComp++;
    }

    int C = compSize.size();
    // a két legnagyobb komponens (a v-n kívüli legnagyobb mérethez)
    int big1 = 0, big1Id = -1, big2 = 0;
    for (int c = 0; c < C; c++) {
        if (compSize[c] > big1) {
            big2 = big1;
            big1 = compSize[c];
            big1Id = c;
        } else if (compSize[c] > big2) {
            big2 = compSize[c];
        }
    }

    int bestParts = -1, bestMax = INT_MAX, bestV = -1;
    for (int v = 1; v <= n; v++) {
        int K = compOf[v];
        int rest = compSize[K] - 1 - sepSum[v];  // a v-t tartalmazó maradék rész
        int parts = (C - 1) + sepCnt[v] + (rest > 0 ? 1 : 0);
        int largest = max(sepMax[v], rest);
        largest = max(largest, K == big1Id ? big2 : big1);
        if (parts > bestParts || (parts == bestParts && largest < bestMax)) {
            bestParts = parts;
            bestMax = largest;
            bestV = v;
        }
    }

    cout << bestV << "\n";
    return 0;
}
