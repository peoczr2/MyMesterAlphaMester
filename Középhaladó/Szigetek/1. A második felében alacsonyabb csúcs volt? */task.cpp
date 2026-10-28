/*
Megoldás lényege:
Egyszer végigmegyünk a méréseken, és minden B mérésre ellenőrizzük a csúcs feltételét: 0 < A < B és B > C > 0. Közben nyilvántartjuk az eddig talált csúcsok közül a legalacsonyabbat. Ha egy csúcs a második felben van (a p-edik mérésnél 2p > N), és kisebb az eddigi csúcsok minimumánál, akkor előtte csak magasabb csúcsokkal találkoztunk, így a válasz 1. Ha még nem volt korábbi csúcs, a minimum végtelen, így az első csúcs is teljesíti a feltételt. Az időigény O(N), a memóriaigény O(N) a beolvasott tömb miatt.
*/
/*
Hint 1: || A csúcs feltétele csak a szomszédos mérésektől függ: a B bal oldali szomszédja A, jobb oldali szomszédja C. Egyetlen bejárás elegendő, és minden B-t csak egyszer kell megvizsgálni. ||
Hint 2: || Tartsd nyilván az eddigi csúcsok legalacsonyabb magasságát egy változóban. A második felet a sorszámból döntsd el: az 1-től számolt p-edik mérés akkor van benne, ha 2p > N. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> m(n);
    for (auto &x : m) cin >> x;

    int legalacsonyabb = INT_MAX;  // az eddigi csúcsok minimuma
    bool van = false;

    for (int i = 1; i + 1 < n; i++) {
        int a = m[i - 1], b = m[i], c = m[i + 1];
        if (0 < a && a < b && b > c && c > 0) {
            int sorszam = i + 1;  // 1-től számozva
            if (2 * sorszam > n && b < legalacsonyabb) {
                van = true;
            }
            legalacsonyabb = min(legalacsonyabb, b);
        }
    }

    cout << (van ? 1 : 0) << "\n";
    return 0;
}
