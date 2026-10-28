/*
Megoldás lényege:
Minden napra a két mért vízállás különbségének abszolút értéke adja a napi ingadozást, hiszen a napi maximum és minimum pontosan ennyivel tér el egymástól. Az ingadozásokat egy tömbben tároljuk, közben összegezzük. Az átlagot egészre kerekítjük úgy, hogy a félértéknél felfelé kerekítünk, ezt az (2 * összeg + N) / (2 * N) egész osztás adja. Az első részfeladat eredménye ez a kerekített átlag. A második részfeladatban az első olyan napot keressük, amelyre a tömbben tárolt ingadozás nagyobb a kerekített átlagnál, és az első találatnál megállunk. Ha nincs ilyen nap, a 0 marad. Az időigény O(N).
*/
/*
Hint 1: || Egy napra a két mért érték különbségének abszolút értéke a napi ingadozás. Először minden napra számold ki ezt, és csak utána dolgozz az ingadozásokkal. ||
Hint 2: || Az átlagot az összeg és a napok száma alapján számolod, de egészre kell kerekíteni, a félértéknél felfelé. Ehhez az (2 * összeg + N) / (2 * N) egész osztás jó, mert csak egész számokkal dolgozik. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> ingadozas(n);
    long long osszeg = 0;
    for (int i = 0; i < n; i++) {
        long long h1, h2;
        cin >> h1 >> h2;
        ingadozas[i] = llabs(h1 - h2);
        osszeg += ingadozas[i];
    }

    // Egészre kerekített átlag, a félértéknél felfelé kerekítve.
    long long atlag = (2 * osszeg + n) / (2 * n);

    // 1. részfeladat: a kerekített átlagos napi ingadozás
    cout << "#\n";
    cout << atlag << "\n";

    // 2. részfeladat: az első olyan nap sorszáma, amelynek ingadozása nagyobb az átlagnál
    cout << "#\n";
    int elso = 0;
    for (int i = 0; i < n; i++) {
        if (ingadozas[i] > atlag) {
            elso = i + 1;
            break;
        }
    }
    cout << elso << "\n";

    return 0;
}
