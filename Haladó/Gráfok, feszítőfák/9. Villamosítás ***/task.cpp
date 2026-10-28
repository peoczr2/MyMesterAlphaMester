/*
Megoldás lényege:
A legkisebb összköltséget Kruskal-algoritmussal kapjuk: az éleket súly szerint dolgozzuk fel, és csak az összeköti a még különálló csomópontokat. Egy él pontosan akkor szerepelhet valamelyik legkisebb költségű hálózatban, ha végpontjait nem köti össze már szigorúan olcsóbb élekből álló út. Ezért minden azonos súlyú csoportot két lépésben kezelünk: először minden élre megnézzük, hogy végpontjai a csoport előtti állapotban különböző halmazban vannak-e (ekkor szóba jön), majd csak ezután uniózzuk a csoport éleit. Így a döntés nem függ a csoporton belüli sorrendtől. Az élek súly szerinti csoportosítása számlálórendezéssel történik (súly legfeljebb 1000), a DSU-műveletek gyakorlatilag állandó idejűek, az összidő O(M + N + 1000).
*/
/*
Hint 1: || A legkisebb összköltség Kruskal-algoritmussal számolható; a nehézség abban van, hogy meg kell határoznod, mely élek jöhetnek szóba, és ez az azonos súlyú éleknél külön figyelmet igényel. ||
Hint 2: || Egy él akkor szerepelhet legolcsóbb hálózatban, ha végpontjait még nem köti össze szigorúan kisebb súlyú élekből álló út; ezt az állapotot uniós-megtalálós (DSU) struktúrával ellenőrizheted, az élek feldolgozása előtt. ||
Hint 3: || Dolgozd fel az éleket súly szerint csoportonként: a csoport minden élét először a csoport előtti állapot alapján vizsgáld meg, és csak utána uniózd a csoport éleit; így az azonos súlyú élek nem zárják ki egymást. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> dsu;

int findSet(int x) {
    while (dsu[x] != x) {
        dsu[x] = dsu[dsu[x]];
        x = dsu[x];
    }
    return x;
}

bool unite(int x, int y) {
    x = findSet(x);
    y = findSet(y);
    if (x == y) return false;
    dsu[x] = y;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> a(m + 1), b(m + 1), w(m + 1);
    for (int i = 1; i <= m; i++) cin >> a[i] >> b[i] >> w[i];

    // Élek súly szerint csoportosítva (súly legfeljebb 1000).
    vector<vector<int>> bucket(1001);
    for (int i = 1; i <= m; i++) bucket[w[i]].push_back(i);

    dsu.resize(n + 1);
    iota(dsu.begin(), dsu.end(), 0);

    vector<char> candidate(m + 1, 0);
    long long total = 0;
    for (int c = 1; c <= 1000; c++) {
        // 1. lépés: a csoport előtti állapot alapján döntjük el, szóba jön-e az él.
        for (int i : bucket[c]) {
            if (findSet(a[i]) != findSet(b[i])) candidate[i] = 1;
        }
        // 2. lépés: a csoport éleit unióozzuk, és a költséget számoljuk.
        for (int i : bucket[c]) {
            if (unite(a[i], b[i])) total += c;
        }
    }

    vector<int> list;
    for (int i = 1; i <= m; i++) {
        if (candidate[i]) list.push_back(i);
    }

    cout << total << '\n' << list.size() << '\n';
    for (size_t j = 0; j < list.size(); j++) {
        if (j) cout << ' ';
        cout << list[j];
    }
    cout << '\n';
    return 0;
}
