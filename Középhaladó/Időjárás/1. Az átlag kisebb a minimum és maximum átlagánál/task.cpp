/*
Megoldás lényege:
Soronként (egy településen) egyszer végigmegyünk a M napi értéken, és közben kiszámoljuk az összeget, a legkisebb és a legnagyobb értéket.
A feladat címe szerint a település akkor kerül a listába, ha az átlag kisebb, mint a minimum és a maximum átlaga, azaz összeg / M < (min + max) / 2.
Mivel az átlag törtszám lehet, az egyenlőtlenséget szorzással alakítjuk egész számokra: 2 · összeg < M · (min + max), így nincs lebegőpontos pontatlanság.
A minta szerint a harmadik településnél az átlag pont 16, és (12 + 20) / 2 = 16, ezért ott a feltétel nem teljesül.
Az idő O(N · M), ami 10^6 érték esetén is gyors.
*/
/*
Hint 1: || A feladat címe adja a kulcsot: a település átlagát kell összehasonlítani a legkisebb és a legnagyobb érték átlagával. Ez egy sorra egyetlen bejárással kiszámolható. ||
Hint 2: || Ha S a sor összege, akkor a feltétel 2 · S < M · (min + max) alakban írható, így nem kell törtet használni. A teljesülő sorok sorszámait a bejárás sorrendjében gyűjtsd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> chosen;
    for (int i = 1; i <= n; i++) {
        int sum = 0, mx = INT_MIN, mn = INT_MAX;
        for (int j = 0; j < m; j++) {
            int h;
            cin >> h;
            sum += h;
            mx = max(mx, h);
            mn = min(mn, h);
        }
        if (2 * sum < m * (mx + mn))
            chosen.push_back(i);
    }

    cout << chosen.size();
    for (int x : chosen)
        cout << ' ' << x;
    cout << '\n';
    return 0;
}
