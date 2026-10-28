/*
Megoldás lényege:
Egy bűvös négyzetben minden sor és minden oszlop összege ugyanaz az S szám. Ha a négyzet már ilyen, a válasz HELYES.
Tudjuk, hogy legfeljebb egy szám hibás, ezért minden cellát kipróbálunk: egy olyan sor összegéből, amely nem tartalmazza az adott cellát,
megkapjuk S értékét, és kiszámoljuk, mennyi kellene a cellába, hogy a cella sora S-re jöjjön ki.
A javított négyzetben ellenőrizzük az összes sor és oszlop összegét, és az első működő cella koordinátáit és helyes értékét írjuk ki.
Mivel N legfeljebb 5, az időigény O(N^4), ami bőven elég.
*/
/*
Hint 1: || Egy bűvös négyzetben minden sor és minden oszlop összege ugyanannyi: ezt a közös értéket kell megtalálni egy olyan sorból, amelyik nem tartalmazza a gyanús cellát. ||
Hint 2: || Ha egy cella hibás, a sorának összege tér el a helyes S-től: a cella helyes értékét a sor többi elemének összegéből és S-ből kapod meg. ||
Hint 3: || Minden cellát kipróbálhatsz: a helyes érték behelyezése után ellenőrizd, hogy minden sor és minden oszlop összege S-e. Az első ilyen cella adja a két kimeneti sort. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Igaz, ha minden sor és minden oszlop összege megegyezik az első sor összegével.
bool isMagic(const vector<vector<long long>> &g, int n) {
    long long s = 0;
    for (int j = 0; j < n; ++j) {
        s += g[0][j];
    }
    for (int i = 0; i < n; ++i) {
        long long rowSum = 0;
        long long colSum = 0;
        for (int j = 0; j < n; ++j) {
            rowSum += g[i][j];
            colSum += g[j][i];
        }
        if (rowSum != s || colSum != s) {
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    cin >> n;

    vector<vector<long long>> g(n, vector<long long>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
        }
    }

    if (isMagic(g, n)) {
        cout << "HELYES\n";
        return 0;
    }

    cout << "HELYTELEN\n";
    for (int i = 0; i < n; ++i) {
        // egy olyan sor, amely nem tartalmazza az i. sor gyanús celláját, adja az S összeget
        int other = (i == 0) ? 1 : 0;
        long long s = 0;
        for (int j = 0; j < n; ++j) {
            s += g[other][j];
        }

        long long rowI = 0;
        for (int j = 0; j < n; ++j) {
            rowI += g[i][j];
        }

        for (int j = 0; j < n; ++j) {
            long long correct = s - (rowI - g[i][j]);
            vector<vector<long long>> fixedGrid = g;
            fixedGrid[i][j] = correct;
            if (isMagic(fixedGrid, n)) {
                cout << i + 1 << " " << j + 1 << " " << correct << "\n";
                return 0;
            }
        }
    }
    return 0;
}
