/*
Megoldás lényege:
Az F függvény gráfjában minden csúcsból pontosan egy él indul, ezért minden kezdőszámhoz egyértelmű sorozat tartozik, és a gráf körökből és a körökbe befutó fákból áll.
Az x kezdőszámú sorozat első ismétlődő szakasza az a kör, amelybe a sorozat először belép; a periódushossz ennek a körnek a hossza, a sorszám pedig a körbe vezető lépések száma plusz egy.
A körön lévő csúcsokat a bemenő élek szerinti levágással találjuk meg: amelyik csúcsba már nem vezet él, azt eltávolítjuk, és a sorozat többi csúcsának bemenő számlálóját csökkentjük. A maradék csúcsok pontosan a körökön vannak.
A körön kívüli csúcsokhoz a levágás fordított sorrendjében a rájuk következő csúcs adatait használva egy lépésben kiszámolható a körbe vezető út hossza. Az idő O(N).
*/
/*
Hint 1: || Minden csúcsból pontosan egy él indul, így a sorozat egyértelmű; minden kezdőszám vagy egy körön van, vagy egy körbe befutó úton. ||
Hint 2: || A körön kívüli csúcsok levághatók: keresd azokat a csúcsokat, amelyekbe már nem vezet él, távolítsd el őket, és közben csökkentsd a rájuk mutató élek számát. ||
Hint 3: || A levágás sorrendjének fordítottját bejárva minden csúcsnál már ismert a rákövetkező csúcs adata: a körbe jutáshoz szükséges lépések száma eggyel több a rákövetkező csúcsénál, a kör hossza pedig ugyanaz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> f(n + 1);
    for (int i = 1; i <= n; i++) cin >> f[i];

    // 1. Levágás: a bemenő él nélküli csúcsok nem körön vannak.
    vector<int> indeg(n + 1, 0);
    for (int i = 1; i <= n; i++) indeg[f[i]]++;
    vector<int> order;
    for (int i = 1; i <= n; i++)
        if (indeg[i] == 0) order.push_back(i);
    for (size_t k = 0; k < order.size(); k++) {
        int v = order[k];
        if (--indeg[f[v]] == 0) order.push_back(f[v]);
    }
    vector<char> removed(n + 1, 0);
    for (int v : order) removed[v] = 1;

    // 2. A maradék csúcsok körön vannak: a kör hossza és a kör csúcsai.
    vector<int> cycLen(n + 1, 0), root(n + 1, 0), tail(n + 1, 0);
    for (int v = 1; v <= n; v++) {
        if (removed[v] || cycLen[v]) continue;
        int len = 1;
        for (int u = f[v]; u != v; u = f[u]) len++;
        int u = v;
        do {
            cycLen[u] = len;
            root[u] = u;
            u = f[u];
        } while (u != v);
    }

    // 3. A körön kívüli csúcsok: a rákövetkező csúcs már ki van számolva.
    for (int k = (int)order.size() - 1; k >= 0; k--) {
        int v = order[k];
        tail[v] = tail[f[v]] + 1;
        root[v] = root[f[v]];
    }

    for (int i = 1; i <= n; i++)
        cout << cycLen[root[i]] << ' ' << tail[i] + 1 << '\n';
    return 0;
}
