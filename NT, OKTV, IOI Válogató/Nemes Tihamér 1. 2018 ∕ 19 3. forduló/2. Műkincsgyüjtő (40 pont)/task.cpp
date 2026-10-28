/*
Megoldás lényege:
Az i-edik kép árát összevetjük a korábbi képek áraival: ha a P-ből hiányzó rész (P - ár) már előfordult, a két kép összege pontosan P, és a párt azonnal kiírjuk. A korábbi árak első előfordulási sorszámát egy P méretű tömbben tároljuk, egyetlen menetben. A P-nél drágább képek nem lehetnek párok tagjai, ezeket kihagyjuk. Ha P az ár kétszerese, a komplementer ugyanaz az ár, így a pár a tömbben korábbi indexen álló kép és az aktuális kép. Az időigény O(N + P), a memóriaigény O(P).
*/
/*
Hint 1: || Ne próbálj minden párt végigellenőrizni: az i-edik képnél csak azt kérdezd meg, hogy a korábbi képek között van-e P − ár árú kép. ||
Hint 2: || Tárold minden árnak az első előfordulási sorszámát egy tömbben, és az aktuális kép ellenőrzését végezd el a beírása előtt, így egy kép nem párosodhat önmagával. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p;
    cin >> n >> p;
    vector<int> first(p + 1, -1);
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        if (x <= p && first[x] != -1 && first[x] != i && x * 2 == p) {
            cout << first[x] << ' ' << i << '\n';
            return 0;
        }
        int need = p - x;
        if (need >= 1 && need <= p && first[need] != -1) {
            cout << first[need] << ' ' << i << '\n';
            return 0;
        }
        if (x <= p && first[x] == -1) first[x] = i;
    }
    cout << -1 << '\n';
    return 0;
}