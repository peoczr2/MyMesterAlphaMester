/*
Megoldás lényege:
Nem kell eltárolni a teljes menetrendet: a sorokat egyesével olvassuk be, és közben figyeljük, van-e olyan sor, ahol a városnév Szekszard, az érkezési idő pedig -1. Az érkezési idő -1 a kezdőállomást jelöli, vagyis azt a sort, ahol a busz indul. Egy logikai változó jelzi, találtunk-e ilyen sort. Mivel minden sort egyszer nézünk meg, az időigény N-nel arányos.
*/
/*
Hint 1: || Nem kell a teljes menetrendet tárolni. Elég minden sort egyszer beolvasni, és mindig ugyanarra a két feltételre figyelni: a városnév Szekszard legyen, és az érkezési idő -1 legyen. ||
Hint 2: || Használj egy logikai változót, amelyet kezdetben hamisra állítasz, és igazra, ha találsz megfelelő sort. A ciklus után a változó alapján írd ki a VAN vagy a NINCS szót. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    bool van = false;
    for (int i = 0; i < n; i++) {
        string varos;
        int erkezes, indulas;
        cin >> varos >> erkezes >> indulas;
        if (varos == "Szekszard" && erkezes == -1) {
            van = true;
        }
    }

    cout << (van ? "VAN" : "NINCS") << '\n';
    return 0;
}
