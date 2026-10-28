/*
Megoldás lényege:
Minden napra külön eldöntjük, hogy sikertelen-e: a nap sikertelen, ha a fogott halak száma szigorúan kisebb a K küszöbnél. A napi halszámokat egyetlen ciklusban olvassuk be, és a kisebb értékeket összegezzük. A K értékét a napok számával együtt, a halak felsorolása előtt kapjuk meg, így a feltétel a beolvasás közben azonnal ellenőrizhető. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Ez feltételes összegzés: minden napot külön kell megvizsgálni, és csak a sikertelen napok halait kell összeadni. ||
Hint 2: || A feltétel: a napi halszám kisebb, mint K. Egy változóban gyűjtsd az összeget, és a végén írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    long long total = 0;
    for (int i = 0; i < n; i++) {
        int fish;
        cin >> fish;
        if (fish < k) {
            total += fish;
        }
    }

    cout << total << "\n";
    return 0;
}
