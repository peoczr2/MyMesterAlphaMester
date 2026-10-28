/*
Megoldás lényege:
A lakásokat sorban egyszer olvassuk be. Az alapterületet nem használjuk fel a döntéshez, csak az árat hasonlítjuk össze K millió forinttal (mindkettő millió forintban van). A K millió forintnál drágább lakások sorszámát (1-től számozva) az olvasás sorrendjében gyűjtjük egy vektorba, így a lista növekvő sorrendben lesz. A kiírás első száma a darabszám, utána a sorszámok szóközzel elválasztva következnek. Az idő O(N).
*/
/*
Hint 1: || Az alapterület a feladatban nem befolyásolja a döntést: csak az árat kell K-val összehasonlítanod, mindkettő millió forintban van. ||
Hint 2: || A drágább lakások sorszámát az olvasás sorrendjében gyűjtsd egy vektorba: a darabszám és a sorszámok sorrendje így a kiíráshoz már készen áll. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> sorszamok;
    for (int i = 1; i <= n; i++) {
        int terulet, ar;
        cin >> terulet >> ar;
        if (ar > k) sorszamok.push_back(i);
    }

    cout << sorszamok.size();
    for (int s : sorszamok) cout << ' ' << s;
    cout << '\n';
    return 0;
}
