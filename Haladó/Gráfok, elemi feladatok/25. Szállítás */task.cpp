/*
Megoldás lényege:
A szállítási útvonalakat irányított gráfnak tekintjük: egy "A B" sor A -> B élt jelent, vagyis A-ból B-be visznek árut. Mivel minden telephely csak egy tevékenységet végez, a típusa a be- és kimenő élekből dönthető el: termelő, ha nincs bejövő éle, de van kimenő éle; árusító, ha van bejövő éle, de nincs kimenő éle; raktározó, ha mindkettő van. A C-nél az árusító telephely minden bejövő szomszédjának termelőnek kell lennie. A D-nél a raktározó telephely egyik szomszédja sem lehet termelő vagy árusító. Az E-nél a raktározó telephelyre legfeljebb egy bejövő és legfeljebb egy kimenő él juthat, különben gyűjtő vagy szétosztó funkciója van. Az ismétlődő éleket rendezéssel szűrjük, így a fokszámok a különböző kapcsolatokat számolják. Az időigény O(M log M + N).
*/
/*
Hint 1: || A telephelyeket a bejövő és kimenő élek megléte alapján sorold típusba: nincs bejövő, de van kimenő él a termelő; van bejövő, de nincs kimenő él az árusító; a kettő együtt a raktározó. ||
Hint 2: || Az élekből szomszédsági listát építs (bejövő és kimenő külön). C-nél a bejövő szomszédok mind termelők legyenek, D-nél a szomszédok között nincs termelő és árusító, E-nél a bejövő és a kimenő élek száma is legfeljebb 1. ||
*/
#include <bits/stdc++.h>
using namespace std;

static void printList(const vector<int>& v) {
    cout << v.size();
    for (int x : v) cout << ' ' << x;
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

    vector<vector<int>> in(n + 1), out(n + 1);
    for (long long code : edges) {
        int a = code / (n + 1);
        int b = code % (n + 1);
        out[a].push_back(b);
        in[b].push_back(a);
    }

    auto isProducer = [&](int v) { return in[v].empty() && !out[v].empty(); };
    auto isSeller = [&](int v) { return !in[v].empty() && out[v].empty(); };
    auto isStorage = [&](int v) { return !in[v].empty() && !out[v].empty(); };

    vector<int> A, B, C, D, E;
    for (int v = 1; v <= n; v++) {
        if (isProducer(v)) A.push_back(v);
        if (isSeller(v)) {
            B.push_back(v);
            if (all_of(in[v].begin(), in[v].end(), isProducer)) C.push_back(v);
        }
        if (isStorage(v)) {
            bool touchesProducer = any_of(in[v].begin(), in[v].end(), isProducer);
            bool touchesSeller = any_of(out[v].begin(), out[v].end(), isSeller);
            if (!touchesProducer && !touchesSeller) D.push_back(v);
            if (in[v].size() <= 1 && out[v].size() <= 1) E.push_back(v);
        }
    }

    printList(A);
    printList(B);
    printList(C);
    printList(D);
    printList(E);
    return 0;
}
