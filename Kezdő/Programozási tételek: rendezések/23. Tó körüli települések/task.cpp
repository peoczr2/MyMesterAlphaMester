/*
Megoldás lényege:
A települések a tó körül egy kört alkotnak, és két település távolsága a körön mért rövidebb ív hossza. Az 1. településtől mért távolságokból minden település két lehetséges helyzete közül az egyik adódik: az 1-estől az egyik vagy a másik irányban van ugyanakkora távolságra. Egy r település (az 1-estől legközelebbi) és egy j település távolságából eldől, hogy ugyanazon az oldalon vannak-e: ha a távolságuk az 1-estől mért távolságaik különbsége, akkor igen, különben nem. Így az 1-estől kiindulva az egyik oldal a távolság szerint növekvő, a másik csökkenő sorrendben adja a körbejárást. A tárolás csak két sort igényel, az időigény a beolvasás miatt O(N^2).
*/
/*
Hint 1: || Egy kör mentén minden település az 1. településtől az egyik, vagy a másik irányban van; a távolságokból az 1-estől mért távolságot ismered, az irányt nem. ||
Hint 2: || Válassz egy r települést, amely az 1-hez a legközelebb van; az r-től és az 1-estől mért távolságok összevetéséből eldöntheted, hogy egy település ugyanazon az oldalon van-e, mint r. ||
Hint 3: || Ha két település ugyanazon az oldalon van, a köztük lévő távolság a két, 1-estől mért távolság különbsége; ellenkező oldalon ez nem igaz. Az egyik oldal távolság szerint növekvő, a másik csökkenő sorrendben adja a kör bejárását. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Gyors beolvasás: a bemenet akár 9 millió számot is tartalmazhat.
static char pufer[1 << 16];
static size_t pufHossz = 0, pufPoz = 0;

static inline int karakter() {
    if (pufPoz == pufHossz) {
        pufHossz = fread(pufer, 1, sizeof(pufer), stdin);
        pufPoz = 0;
        if (pufHossz == 0) return -1;
    }
    return pufer[pufPoz++];
}

static inline int szam() {
    int c = karakter();
    while (c != -1 && (c < '0' || c > '9')) c = karakter();
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = karakter();
    }
    return x;
}

int main() {
    int n = szam();

    // az 1. sor: az 1. településtől mért távolságok
    vector<int> d1(n + 1);
    for (int j = 1; j <= n; ++j) d1[j] = szam();

    // r: az 1. településhez legközelebbi település (a kör szerint az egyik szomszédja)
    int r = 2;
    for (int j = 3; j <= n; ++j)
        if (d1[j] < d1[r]) r = j;

    // a többi sort csak átolvassuk, de az r. sort eltároljuk
    vector<int> dr(n + 1, 0);
    for (int i = 2; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            int v = szam();
            if (i == r) dr[j] = v;
        }

    // plusz: r-rel azonos oldalon van, minusz: a másik oldalon
    vector<int> plusz, minusz;
    for (int j = 2; j <= n; ++j) {
        if (j == r) {
            plusz.push_back(j);
            continue;
        }
        if (dr[j] == abs(d1[r] - d1[j])) plusz.push_back(j);
        else minusz.push_back(j);
    }
    sort(plusz.begin(), plusz.end(), [&](int a, int b) { return d1[a] < d1[b]; });
    sort(minusz.begin(), minusz.end(), [&](int a, int b) { return d1[a] > d1[b]; });

    cout << 1;
    for (int j : plusz) cout << ' ' << j;
    for (int j : minusz) cout << ' ' << j;
    cout << '\n';
    return 0;
}
