/*
Megoldás lényege:
Egyetlen bejárással végigmegyünk a napokon, és közben nyilvántartjuk, hogy éppen tart-e szmogriadó.
Új riadó akkor rendelődik el, amikor a szennyezettség 100 fölé emelkedik, és még nincs érvényben riadó.
A riadó addig marad érvényben, amíg a szennyezettség 100 alá nem csökken; 100-on a riadó nem szűnik meg.
Az első napnak nincs előző mérése, ezért az 1. napon csak az állapotot rögzítjük, új riadót nem rendelünk el.
Kiírásnál előbb az elrendelt riadók száma, utána a napok sorszámai következnek, szóközzel elválasztva.
Az időigény N-nel arányos, ami legfeljebb 100 lépés, így a korlátok mellett bőven belefér.
*/
/*
Hint 1: || Elég egyetlen bejárás és egy logikai változó, amely azt tárolja, hogy a legutóbbi napon érvényben van-e riadó. ||
Hint 2: || Riadó akkor kezdődik, ha a szennyezettség 100 fölött van és nincs érvényben riadó; riadó akkor szűnik, ha 100 alá megy. Az első napot csak állapotként vedd figyelembe, és kiírás előtt számold meg a riadókat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> level(n);
    for (int& x : level) cin >> x;

    bool alert = level[0] > 100;  // az 1. napnak nincs előző mérése: csak állapotot rögzítünk
    vector<int> ordered;
    for (int i = 1; i < n; ++i) {
        if (!alert && level[i] > 100) {
            ordered.push_back(i + 1);
            alert = true;
        } else if (alert && level[i] < 100) {
            alert = false;
        }
    }

    cout << ordered.size();
    for (int day : ordered) cout << ' ' << day;
    cout << '\n';
    return 0;
}
