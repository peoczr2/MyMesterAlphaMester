/*
Megoldás lényege:
Azokat a permutációkat állítjuk elő, ahol minden x[i] az i-1, i vagy i+1 értéke
lehet. Ezek pontosan úgy épülnek fel, hogy minden helyre vagy a helyén álló
számot tesszük, vagy a szomszédos két számot felcseréljük, és a cserék nem
fedhetik egymást. A visszalépéses keresés ezt a két lehetőséget járja be. A
sorozatok száma egy Fibonacci-szerű rekurzióval előre kiszámolható (N=30
esetén kb. 1,3 millió). A memóriakorlát miatt a sorozatokat nem tároljuk: a
számlálás után minden sorozatot azonnal, pufferelten kiírunk. Az időigény
O(DB * N), ahol DB a sorozatok száma.
*/
/*
Hint 1: || Gondoljuk végig, melyik szám kerülhet az i. helyre: csak i-1, i vagy i+1 lehet. ||
Hint 2: || Az i. helyről haladva két eset van: az i. számot magában tesszük le (ekkor i+1-től folytatjuk), vagy az i. és i+1. számot megcseréljük (ekkor i+2-től folytatjuk). ||
Hint 3: || Mivel a sorozatok száma több millió is lehet, ne tároljuk őket: előbb számoljuk meg őket a rekurzióval, majd a keresés közben írjuk ki. ||
*/

#include <bits/stdc++.h>
using namespace std;

int n;
int akt[64];
int hossz = 0;
char puffer[1 << 16];
int pozicio = 0;

void karakter(char c) {
    if (pozicio == (int)sizeof(puffer)) {
        fwrite(puffer, 1, pozicio, stdout);
        pozicio = 0;
    }
    puffer[pozicio++] = c;
}

void szam(int x) {
    char tmp[12];
    int len = 0;
    do {
        tmp[len++] = char('0' + x % 10);
        x /= 10;
    } while (x > 0);
    while (len > 0) karakter(tmp[--len]);
}

void kiir() {
    for (int i = 0; i < n; ++i) {
        if (i) karakter(' ');
        szam(akt[i]);
    }
    karakter('\n');
}

void dfs(int i) {
    if (i > n) {
        kiir();
        return;
    }
    akt[hossz++] = i;
    dfs(i + 1);
    --hossz;
    if (i + 1 <= n) {
        akt[hossz++] = i + 1;
        akt[hossz++] = i;
        dfs(i + 2);
        hossz -= 2;
    }
}

int main() {
    cin >> n;

    // db(m) = db(m-1) + db(m-2), ahol db(0) = db(1) = 1
    long long elozo = 1, aktualis = 1;
    for (int m = 2; m <= n; ++m) {
        long long uj = elozo + aktualis;
        elozo = aktualis;
        aktualis = uj;
    }
    printf("%lld\n", aktualis);

    dfs(1);
    fwrite(puffer, 1, pozicio, stdout);
    return 0;
}
