/*
Megoldás lényege:
Egy településen egy nap akkor átlag feletti, ha a hőmérséklete nagyobb a település M napos átlagánál, és átlag alatti, ha kisebb. Soronként először kiszámoljuk a hőmérsékletek összegét, majd megszámoljuk az átlag feletti és az átlag alatti napokat. A törtes átlag elkerülhető: a napi értéket M-mel szorozzuk, és ezt hasonlítjuk az összeghez. A település akkor kerül a listába, ha az átlag feletti napok száma nagyobb az átlag alatti napok számánál. Az idő O(N·M), a memória O(M).
*/
/*
Hint 1: || Egy településre elég két dolgot tudni: az átlagát, és hogy hány napja van átlag felett, illetve átlag alatt. Az átlaggal egyenlő napok egyik csoportba sem tartoznak. ||
Hint 2: || Az átlag törtszám is lehet, ezért ne oszd el az összeget M-mel, hanem szorozd meg a napi értéket M-mel, és ezt hasonlítsd az összeghez. Mivel az összeg csak a sor végén ismert, a sor értékeit előbb tárold el. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> tobb;
    vector<int> h(m);
    for (int i = 1; i <= n; i++) {
        int osszeg = 0;
        for (int j = 0; j < m; j++) {
            cin >> h[j];
            osszeg += h[j];
        }
        int felett = 0, alatt = 0;
        for (int j = 0; j < m; j++) {
            int e = h[j] * m;
            if (e > osszeg) felett++;
            else if (e < osszeg) alatt++;
        }
        if (felett > alatt) tobb.push_back(i);
    }

    cout << tobb.size();
    for (int s : tobb) cout << ' ' << s;
    cout << '\n';
    return 0;
}
