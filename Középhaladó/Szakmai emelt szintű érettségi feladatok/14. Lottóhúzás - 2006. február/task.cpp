/*
Megoldás lényege:
A véletlen számokat a feladatban megadott lineáris kongruens generátorral állítjuk elő, a seed értékét a hívások között globális változóban őrizzük. Egy húzásban már kihúzott számot elvetünk, és addig generálunk újat, amíg olyan szám nem jön, amely még nem szerepelt. A kihúzott számokat logikai tömbben jegyezzük, így az ellenőrzés O(1). A szorzat meghaladja a 32 bites egész tartományt, ezért 64 bites egészekkel számolunk. A sorsolások száma K = N esetén is nagyjából N·ln N, ami N ≤ 10 000 mellett néhány százezer lépés, ez bőven belefér az időkorlátba.
*/
/*
Hint 1: || A seed állapotát a hívások között meg kell őrizni: tartsd globális változóban, és minden híváskor a megadott képlet szerint frissítsd. A random(1, N) hívás 1 és N közötti számot ad. ||
Hint 2: || Egy szám újrasorsolásához ciklus kell: addig hívd a generátort, amíg a kapott szám még nem szerepelt a húzásban. A nyilvántartásra egy N+1 elemű logikai tömb elegendő. ||
Hint 3: || A 1103515245 · seed szorzat nagyobb lehet 2^31-nél, ezért a számításokat 64 bites egész típussal (long long) végezd el. ||
*/
#include <bits/stdc++.h>
using namespace std;

long long seed = 42;

long long randomInt(long long lo, long long hi) {
    seed = (1103515245LL * seed + 12345LL) % 2147483648LL;
    return lo + (seed % hi);
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<bool> used(n + 1, false);
    for (int i = 0; i < k; i++) {
        long long x;
        do {
            x = randomInt(1, n);
        } while (used[x]);
        used[x] = true;
        if (i > 0) cout << ' ';
        cout << x;
    }
    cout << "\n";
    return 0;
}
