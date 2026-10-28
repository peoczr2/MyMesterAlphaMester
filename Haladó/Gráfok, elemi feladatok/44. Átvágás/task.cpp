/*
Megoldás lényege: egy átvágás művelet az élnek az egyik végpontját (b) egy másik csúcsra (c) húzza át, így b fokszáma eggyel csökken, c fokszáma eggyel nő.
Bambusz: minden fokszám legfeljebb 2 lehet, a többlet Σ max(0, d−2) kezdetben pontosan (levelek száma − 2), és egy művelet ezt legfeljebb eggyel csökkenti.
Ez el is érhető: egy legalább 3-as fokú b csúcsnál az egyik éle b-végpontját áthúzzuk egy b másik ágában lévő levélre, így a többlet eggyel csökken, a fa pedig fa marad.
Csillag: a középpont a legnagyobb fokú csúcs, és minden hozzá nem kapcsolódó él távolabbi végpontját egy művelettel a középpontra húzzuk át, ez N−1−(maximális fok) művelet.
Az időigény O(N).
*/
/*
Hint 1: || Egy műveletnél az élnek az egyik végpontja megmarad, a másik végpont fokszáma eggyel csökken, egy harmadik csúcsé eggyel nő. Vizsgáljuk meg, mit kell a fokszámoknak elérniük a bambuszhoz és a csillaghoz. ||
Hint 2: || A bambuszban minden fokszám legfeljebb 2. A fokszámok összege állandó (2·(N−1)), ezért számoljuk meg, mekkora a 2-nél nagyobb fokú csúcsok összes többlete a levelek számához képest. ||
Hint 3: || A csillag középpontja legyen a legnagyobb fokú csúcs. Az olyan éleknél, amelyek nem a középponthoz kapcsolódnak, húzzuk át a középpontól távolabbi végpontot a középpontra. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> deg(n + 1, 0);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        deg[a]++;
        deg[b]++;
    }

    int leaves = 0, maxdeg = 0;
    for (int v = 1; v <= n; v++) {
        if (deg[v] == 1) leaves++;
        maxdeg = max(maxdeg, deg[v]);
    }

    cout << leaves - 2 << ' ' << (n - 1 - maxdeg) << '\n';
    return 0;
}
