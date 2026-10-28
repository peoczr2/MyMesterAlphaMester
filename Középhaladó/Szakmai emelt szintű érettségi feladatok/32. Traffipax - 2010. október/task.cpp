/*
Megoldás lényege: egyetlen beolvasással minden járműnél eldöntjük, hogy betartotta-e a sebességkorlátot (v ≤ vlimit). A betartók sebességének összegét és darabszámát, a túllépők darabszámát pedig külön számoljuk. Az átlagot egész aritmetikával képezzük: a 100-szorosát kerekítjük a legközelebbi egészre (fél esetén felfelé), így nincs lebegőpontos kerekítési hiba. Ha nincs betartó jármű, a feladat szerint a 0 kiírása a helyes eredmény. Minden részfeladat eredménye elé # sor kerül a formai előírás szerint. Az algoritmus O(N) időben fut, N ≤ 10^5 esetén bőven időben van.
*/
/*
Hint 1: || Egyetlen bejárással mindkét részfeladathoz elég adat: a betartóknál az összeg és a darabszám, a túllépőknél csak a darabszám kell. Figyelj arra, hogy a határértéken lévő sebesség még betartottnak számít. ||
Hint 2: || Az átlag kiszámításához az összeget és a darabszámot egész típusban tárold, és csak a végén oszd el őket egymással. A két tizedesjegyre kerekítést a kiíráskor kézzel is megoldhatod, például a 100-szoros érték kerekítésével. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, limit;
    cin >> n >> limit;

    long long sumOk = 0;    // a sebességkorlátot betartó járművek sebességeinek összege
    long long cntOk = 0;    // a betartó járművek száma
    long long cntOver = 0;  // a túllépő járművek száma

    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        if (v <= limit) {
            sumOk += v;
            cntOk++;
        } else {
            cntOver++;
        }
    }

    cout << "#\n";
    if (cntOk == 0) {
        cout << "0\n";
    } else {
        // az átlag 100-szorosa, félre felfelé kerekítve: floor(100 * sum / cnt + 1/2)
        long long hundredths = (sumOk * 200 + cntOk) / (2 * cntOk);
        long long rest = hundredths % 100;
        cout << hundredths / 100 << '.' << (rest < 10 ? "0" : "") << rest << '\n';
    }

    cout << "#\n";
    cout << cntOver << '\n';
    return 0;
}
