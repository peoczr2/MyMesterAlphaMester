/*
Megoldás lényege:
A két csapatból csak a pólószín számít. Egy piros pólós játékos csak zöld pólós
ellenféllel, egy zöld pólós pedig csak piros pólós ellenféllel párosítható.
Ezért elegendő megszámolni mindkét csapatban a piros és zöld játékosokat, majd
két független minimummal megkapjuk a maximális párok számát.
Az időigény O(N + M), mert minden játékost egyszer nézünk meg.
*/
/*
Hint 1: || Egy pár akkor jó, ha a két játékos pólószíne különbözik. Így két független csoport van: az 1. csapat piros és a 2. csapat zöld, illetve az 1. csapat zöld és a 2. csapat piros. ||
Hint 2: || Számold meg mindkét csapatban a piros és a zöld pólósokat. Mindkét csoportban annyi pár alakítható, amennyi a két oldal kisebb száma; a két eredményt add össze. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string a;
    cin >> a;

    int m;
    cin >> m;
    string b;
    cin >> b;

    int piros1 = 0, zold1 = 0, piros2 = 0, zold2 = 0;
    for (char c : a) {
        if (c == 'p') ++piros1;
        else ++zold1;
    }
    for (char c : b) {
        if (c == 'p') ++piros2;
        else ++zold2;
    }

    cout << min(piros1, zold2) + min(zold1, piros2) << '\n';
    return 0;
}
