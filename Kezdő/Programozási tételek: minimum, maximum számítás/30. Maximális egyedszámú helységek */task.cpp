/*
Megoldás lényege:
A helységeket soronként olvassuk be, és fajonként külön maximumkiválasztást végzünk: minden fajhoz tároljuk az eddig látott legnagyobb egyedszámot és annak helységének sorszámát. Csak szigorúan nagyobb érték esetén frissítünk, így egyenlőségnél a kisebb sorszámú helység marad. A teljes mátrixot nem kell eltárolni, ezért a memóriaigény O(N), az időigény O(M·N).
*/
/*
Hint 1: || Minden fajra külön kell maximumot keresni: egy faj értékei az összes helységben ugyanabban a sorszámú oszlopban vannak. ||
Hint 2: || Elég N darab maximumot és N darab helységsorszámot nyilvántartani: a mátrixot beolvasás közben, soronként dolgozd fel, és a csere feltétele legyen szigorú (>). ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;

    vector<int> bestCount(n, -1);
    vector<int> bestTown(n, 0);
    for (int town = 1; town <= m; town++) {
        for (int bird = 0; bird < n; bird++) {
            int count;
            cin >> count;
            if (count > bestCount[bird]) {
                bestCount[bird] = count;
                bestTown[bird] = town;
            }
        }
    }

    for (int bird = 0; bird < n; bird++) {
        if (bird > 0) cout << ' ';
        cout << bestTown[bird];
    }
    cout << "\n";
    return 0;
}
