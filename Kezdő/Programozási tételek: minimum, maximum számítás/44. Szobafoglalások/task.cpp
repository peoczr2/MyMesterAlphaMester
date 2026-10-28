/*
Megoldás lényege:
Egy K és V közötti foglalás a K., K+1, ..., V−1. éjszakát foglalja le, a V. napon a szoba már kiadható. Ezért a foglalást a [K, V) félnyílt intervallumként kezeljük: a K. éjszakához +1-et, a V. éjszakához −1-et írunk egy különbségtömbbe. A prefix összeggel minden éjszakára megkapjuk a foglalt szobák számát, egy menetben kiválasztjuk a maximumot, és megszámoljuk, hány éjszakán fordul elő. Az időigény O(N + M), a memóriaigény O(M).
*/
/*
Hint 1: || A foglalás a K. napon kezdődik, és a V. napon már nincs benne: a V. nap éjszakáját már nem foglalja. Így a foglalt éjszakák a K-tól V−1-ig tartanak. ||
Hint 2: || Használj különbségtömböt az éjszakák számára: a K-adik helyhez +1-et, a V-edik helyhez −1-et írj, majd a prefix összeg minden éjszakára megadja a foglalt szobák számát. Az egyszerre foglalt szobák maximumát és az azt elérő éjszakák számát egy végigfutással határozd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> diff(m + 1, 0);
    for (int i = 0; i < n; i++) {
        int from, to;
        cin >> from >> to;
        diff[from]++;
        diff[to]--;
    }

    int booked = 0, best = 0, nights = 0;
    for (int night = 0; night < m; night++) {
        booked += diff[night];
        if (booked > best) {
            best = booked;
            nights = 1;
        } else if (booked == best) {
            nights++;
        }
    }

    cout << best << "\n" << nights << "\n";
    return 0;
}
