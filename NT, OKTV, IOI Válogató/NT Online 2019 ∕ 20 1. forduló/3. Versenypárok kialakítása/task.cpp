/*
Megoldás lényege:
A két csapatból csak a pólószín számít. Egy piros pólós játékos csak zöld pólós
ellenféllel, egy zöld pólós pedig csak piros pólós ellenféllel párosítható.
Ezért elegendő megszámolni mindkét csapatban a piros és zöld játékosokat, majd
két független minimummal megkapjuk a maximális párok számát.
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
