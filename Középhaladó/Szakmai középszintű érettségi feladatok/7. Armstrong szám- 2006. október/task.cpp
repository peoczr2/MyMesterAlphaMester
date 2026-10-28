/*
Megoldás lényege:
A számot karakterláncként olvassuk be, így a jegyek száma a karakterlánc hossza. Minden jegyet az n-edik hatványra emelünk (n a jegyek száma), és az eredményeket összeadjuk. Ugyanebből a karakterláncból számértéket is építünk, és ha az összeg egyenlő az eredeti számmal, a szám Armstrong-szám. A 64 bites bemenet miatt az összeg akár 20 jegyű is lehet, ezért a hatványokat és az összeget __int128 típusban számoljuk, hogy ne csorduljon túl. Egy szám feldolgozása O(J^2) időben történik, ahol J legfeljebb 20, az összes számé O(N * J^2), a memóriaigény O(1).
*/
/*
Hint 1: || A jegyek számát a bemeneti karakterlánc hossza adja, így előre nem kell tudni, hány jegyű a szám. Minden jegyet emeld az n-edik hatványra, és adj hozzá egy összeghez. ||
Hint 2: || 64 bites számoknál az összeg túlcsordulhat, ezért használj __int128 típust az összegre és a hatványokra. A végén a számjegyekből épített értéket hasonlítsd össze az összeggel. ||
*/
#include <bits/stdc++.h>
using namespace std;

// A d szám k-adik hatványa (k legfeljebb 20, ezért 128 bites egész elég)
__int128 hatvany(int d, int k) {
    __int128 eredmeny = 1;
    for (int i = 0; i < k; i++) {
        eredmeny *= d;
    }
    return eredmeny;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        string szam;
        cin >> szam;

        int jegyek = (int)szam.size();
        __int128 osszeg = 0;
        __int128 ertek = 0;
        for (char c : szam) {
            int d = c - '0';
            osszeg += hatvany(d, jegyek);
            ertek = ertek * 10 + d;
        }

        cout << (osszeg == ertek ? "Igen" : "Nem") << "\n";
    }
    return 0;
}
