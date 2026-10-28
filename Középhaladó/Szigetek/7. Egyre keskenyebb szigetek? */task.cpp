/*
Megoldás lényege:
Megkeressük a szigeteket: a 0-ás mérésekkel elválasztott pozitív szakaszokat, amelyeknek mindkét partja
mért. Egy sziget hossza a két part sorszámának különbsége. Az út akkor lesz egyre keskenyebb,
ha minden sziget hossza szigorúan kisebb az előzőnél, ezt a szomszédos szigetpárokra ellenőrizzük
egyszer végigmenve. Ha nincs sziget, a válasz 0, egyetlen sziget esetén nincs összehasonlítás,
így a válasz 1. Az időigény O(N).
*/
/*
Hint 1: || Szigetek keresése ugyanúgy, mint a csúcs nélküli sziget feladatnál: a 0-ás mérések közötti pozitív szakaszok, amelyeknek van bal és jobb partjuk. ||
Hint 2: || Egyszerre csak két szomszédos sziget hosszát kell összehasonlítani: ha egy sziget hossza nem kisebb az előzőénél, a válasz 0. Az üres és az egyszigetes eset külön kezelendő. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> h(n + 2, 0);  // h[1..n] a mérések, h[0] és h[n+1] nulla
    for (int i = 1; i <= n; i++) cin >> h[i];

    // a szigetek hossza (a két part sorszámának különbsége), balról jobbra
    vector<int> hossz;
    int i = 1;
    while (i <= n) {
        if (h[i] == 0) {
            i++;
            continue;
        }
        int l = i;
        while (i <= n && h[i] > 0) i++;
        int r = i - 1;
        if (l > 1 && r < n) hossz.push_back(r - l);
    }

    if (hossz.empty()) {
        cout << 0 << '\n';
        return 0;
    }

    bool egyre_keskenyebb = true;
    for (size_t k = 1; k < hossz.size(); k++) {
        if (hossz[k] >= hossz[k - 1]) {
            egyre_keskenyebb = false;
            break;
        }
    }

    cout << (egyre_keskenyebb ? 1 : 0) << '\n';
    return 0;
}
