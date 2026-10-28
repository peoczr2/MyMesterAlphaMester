/*
Megoldás lényege:
Az embereket csúcsoknak, a továbbadásokat irányított éleknek tekintjük: egy "A B" sor A -> B élt jelent, mert B az A-tól hallotta a rémhírt. Az A csoportba azok tartoznak, akiknek nincs bejövő élük, de van kimenő élük: ők indították el a hírt és adják tovább. A B csoportba azok kerülnek, akik kaptak hírt (van bejövő élük), de nem adják tovább (nincs kimenő élük). A C csoport a legtöbb kimenő éllel rendelkező csúcsok halmaza. Mivel ugyanaz a továbbadás többször is szerepelhet a bemenetben, az éleket rendezés és duplikátumszűrés után számoljuk, így a kimenő élek száma valóban a különböző embereket adja. Az időigény O(M log M + N).
*/
/*
Hint 1: || A kérdésekre a csúcsok be- és kimenő éleinek száma ad választ: gondolj az emberekre csúcsokként, a továbbadásokra irányított élekként. ||
Hint 2: || Minden csúcsra számold meg a bejövő és a kimenő éleket (a duplikált párokat előbb szűrd ki). A kezdők: bejövő 0 és kimenő több mint 0; a nem továbbadók: kimenő 0 és bejövő több mint 0; a C-hez a kimenő élek maximumát keresd. ||
*/
#include <bits/stdc++.h>
using namespace std;

static void printList(const vector<int>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        if (i) cout << ' ';
        cout << v[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Az A -> B élt egyetlen számba kódoljuk, így könnyű rendezni és szűrni.
    vector<long long> edges(m);
    for (int i = 0; i < m; i++) {
        long long a, b;
        cin >> a >> b;
        edges[i] = a * (n + 1) + b;
    }
    sort(edges.begin(), edges.end());
    edges.erase(unique(edges.begin(), edges.end()), edges.end());

    vector<int> indeg(n + 1, 0), outdeg(n + 1, 0);
    for (long long code : edges) {
        int a = code / (n + 1);
        int b = code % (n + 1);
        outdeg[a]++;
        indeg[b]++;
    }

    vector<int> starters, silent, best;
    int maxOut = 0;
    for (int v = 1; v <= n; v++) {
        if (indeg[v] == 0 && outdeg[v] > 0) starters.push_back(v);
        if (outdeg[v] == 0 && indeg[v] > 0) silent.push_back(v);
        maxOut = max(maxOut, outdeg[v]);
    }
    for (int v = 1; v <= n; v++) {
        if (outdeg[v] == maxOut) best.push_back(v);
    }

    printList(starters);
    printList(silent);
    printList(best);
    return 0;
}
