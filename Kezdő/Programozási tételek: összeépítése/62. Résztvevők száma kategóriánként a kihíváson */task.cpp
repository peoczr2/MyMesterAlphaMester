/*
Megoldás lényege: minden nevezőnél a lélekszám alapján eldöntjük a kategóriát (a határok szerinti
tartományellenőrzéssel), és a részvevők számát az adott kategória számlálójához adjuk. A helységnév nem befolyásolja
a kiírást, ezért a sorát beolvassuk és eldobjuk. Időigény: O(N).
*/
/*
Hint 1: || A kiíráshoz csak a kategória és a részvevők száma kell, a helységnév nem számít. ||
Hint 2: || Hét számlálót tarts nyilván. Egy nevezőnél a lélekszám határai szerint válaszd ki a kategóriát, és ahhoz
a számlálóhoz add hozzá a részvevők számát. A helységnév sorát olvasd be és dobd el, a lélekszám és a
részvevők száma már külön sorban jön. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long sum[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    string line;
    for (int i = 0; i < n; i++) {
        do {
            getline(cin, line);
        } while (line.find_first_not_of(" \t\r") == string::npos);

        long long h, r;
        cin >> h >> r;

        int c;
        if (h < 700) c = 1;
        else if (h < 1500) c = 2;
        else if (h < 3000) c = 3;
        else if (h < 8000) c = 4;
        else if (h < 25000) c = 5;
        else if (h < 70000) c = 6;
        else c = 7;
        sum[c] += r;
    }

    for (int c = 1; c <= 7; c++) {
        cout << sum[c] << (c < 7 ? ' ' : '\n');
    }
    return 0;
}
