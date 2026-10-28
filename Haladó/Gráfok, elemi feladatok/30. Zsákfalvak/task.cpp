/*
Megoldás lényege:
Egy zsákfaluból az út addig nem ágazik el, amíg olyan faluba nem érünk, ahonnan nem csak egy másik úton lehet továbbmenni, vagyis amíg fokszám 2 csúcsokon haladunk.
Ezért minden zsákfaluból egyszer végigkövetjük az utat: a fokszám 2 falvakon az érkezésen kívüli másik utat választjuk, és megállunk, amikor a fokszám nem 2.
A megtett útszakaszok száma adja az út hosszát; a leghosszabbakhoz tartozó zsákfalvakat növekvő sorrendben írjuk ki.
Mivel a fokszám 2 csúcsok láncai diszjunktak, az összes bejárás együtt O(N + M) időben lefut.
*/
/*
Hint 1: || Egy zsákfaluból indulva csak akkor van döntési helyzet, ha az aktuális faluban háromnál több (vagy egynél több) út találkozik; fokszám 2 falvon a továbbhaladás egyértelmű. ||
Hint 2: || Számold a megtett útszakaszokat, és állj meg, amint olyan faluhoz érsz, ahol a fokszám nem 2 (elágazás vagy zsákfalu); a megtett szakaszok száma adja az út hosszát. ||
Hint 3: || Fokszám 2 falun az érkező úttól különböző másik utat kell választanod; a kettő közül azt, amelyiken nem jöttél. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n + 1); // (szomszéd, útazonosító)
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }

    int best = 0;
    vector<int> ans;
    for (int s = 1; s <= n; s++) {
        if (g[s].size() != 1) continue;
        int prevEdge = g[s][0].second;
        int cur = g[s][0].first;
        int len = 1;
        while (g[cur].size() == 2) {
            pair<int, int> nxt = (g[cur][0].second == prevEdge) ? g[cur][1] : g[cur][0];
            prevEdge = nxt.second;
            cur = nxt.first;
            len++;
        }
        if (len > best) {
            best = len;
            ans.clear();
        }
        if (len == best) ans.push_back(s);
    }

    if (ans.empty()) {
        cout << -1 << '\n';
        return 0;
    }
    cout << best << '\n';
    for (size_t i = 0; i < ans.size(); i++) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
