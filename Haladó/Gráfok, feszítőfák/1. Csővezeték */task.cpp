/*
Megoldás lényege:
A finomítók között nem kell csövet építeni, elég, hogy minden benzinkút valamelyik finomítóból kapjon ellátást, ezért a finomítók úgy kezelhetők, mintha egyetlen közös, nulla költségű csomópontot alkotnának. A csatlakozás csak csomópontnál lehet, így nincs Steiner-pont: a feladat a Manhattan-távolságokkal súlyozott, finomítók összevont gráfjának minimális feszítőfája. Prim-algoritmussal dolgozunk: kezdetben minden benzinkúthoz kiszámítjuk a legközelebbi finomítót, majd mindig azt a még nem csatlakoztatott benzinkutat kötjük be, amelyik a hálózathoz a legközelebb van, és a többi benzinkút távolságát az újonnan bekötött csomópont szerint frissítjük. A fa pontosan N élt tartalmaz, az időigény O(N^2 + N·K), ami N <= 3000 és K <= 100 mellett bőven belefér.
*/
/*
Hint 1: || A finomítók között nincs szükség csőre: úgy gondolkodj, mintha minden finomítót egyetlen csomópontba olvasztanál, és a benzinkutakat ehhez a csomóponthoz kellene minimális összhosszúságú hálózattal kötni. ||
Hint 2: || A két pont közötti távolság |x1-x2| + |y1-y2|. Egy benzinkút legolcsóbb bekötése mindig a már a hálózatban lévő csomópontok közül a legközelebbi, ezért tartsd nyilván minden benzinkútra a legkisebb eddigi távolságot és a hozzá tartozó csomópontot. ||
Hint 3: || Prim-algoritmus: minden lépésben válaszd a még nem bekötött benzinkutak közül a legkisebb távolságút, add hozzá a hosszához az értékét, majd frissítsd a többi benzinkút távolságát az új csomópont alapján. A végén a benzinkutakat sorszám szerint haladva írd ki a (szülő, gyerek) párokat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K, N;
    cin >> K >> N;
    vector<int> x(K + N), y(K + N);
    for (int i = 0; i < K + N; i++) {
        cin >> x[i] >> y[i];
    }

    auto dist = [&](int a, int b) {
        return abs(x[a] - x[b]) + abs(y[a] - y[b]);
    };

    const int INF = INT_MAX;
    vector<int> best(K + N, INF), parent(K + N, -1);
    vector<bool> used(K + N, false);

    // A benzinkutak kezdeti távolsága a legközelebbi finomítótól.
    for (int s = K; s < K + N; s++) {
        for (int r = 0; r < K; r++) {
            int d = dist(s, r);
            if (d < best[s]) {
                best[s] = d;
                parent[s] = r;
            }
        }
    }

    long long total = 0;
    for (int step = 0; step < N; step++) {
        int v = -1;
        for (int s = K; s < K + N; s++) {
            if (!used[s] && (v == -1 || best[s] < best[v])) {
                v = s;
            }
        }
        used[v] = true;
        total += best[v];

        for (int s = K; s < K + N; s++) {
            if (!used[s]) {
                int d = dist(s, v);
                if (d < best[s]) {
                    best[s] = d;
                    parent[s] = v;
                }
            }
        }
    }

    // Minden benzinkúthoz egy él tartozik: (szülő, benzinkút), sorszám szerint.
    cout << total << "\n";
    for (int s = K; s < K + N; s++) {
        cout << parent[s] + 1 << " " << s + 1 << "\n";
    }
    return 0;
}
