/*
Megoldás lényege:
Mindkét naptárban a dátumot egyetlen napsorszámra (0-tól számolva) alakítjuk, majd ebből számoljuk ki a másik naptár szerinti dátumot. Tzolkinban egy év 260 nap, 13 darab 20 napos hónappal. Haabban egy év 365 nap: 18 darab 20 napos hónap, utána az év végi 5 pótnap, amelyet a 0. hónapnak tekintünk, és a napsorszáma 360-tól indul. A feladat példái alapján mindkét naptár ugyanazt a napsorszámozást használja (52 haab év = 73 tzolkin év = 18 980 nap), így nincs eltolás. Visszaalakításnál az osztás hányadosa adja az évet, a maradékból osztással és maradékképzéssel kapjuk a hónapot és a napot. Az időigény állandó.
*/
/*
Hint 1: || Ne próbáld a két naptárat közvetlenül egymásba alakítani. Hozd mindkét dátumot egy közös napsorszámra (hány nap telt el a kezdőponttól), és onnan számold ki a másik naptár szerinti dátumot. ||
Hint 2: || Tzolkinban egy év 260 nap, egy hónap 20 nap. Haabban egy év 365 nap: 18 darab 20 napos hónap után jön az 5 pótnap, amely a 0. hónap, a napsorszáma 360-tól indul. Ebből felírható a sorszám képlete mindkét naptárra. ||
Hint 3: || Visszaalakításnál a sorszámot osztással és maradékkal bontsd. Az évhez a hányados és 1 összege kell. A maradék 20-szal osztva adja a hónapot (plusz 1), a 20-as maradéka a napot (plusz 1). Haabnál a 360 feletti maradék a 0. hónap. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Napsorszám (0-tól) -> haab dátum kiírása
void kiirHaab(int d) {
    int ev = d / 365 + 1;
    int maradek = d % 365;
    int ho, nap;
    if (maradek >= 360) {  // az év végi 5 pótnap
        ho = 0;
        nap = maradek - 360 + 1;
    } else {
        ho = maradek / 20 + 1;
        nap = maradek % 20 + 1;
    }
    cout << ev << ' ' << ho << ' ' << nap << '\n';
}

// Napsorszám (0-tól) -> tzolkin dátum kiírása
void kiirTzolkin(int d) {
    int ev = d / 260 + 1;
    int maradek = d % 260;
    cout << ev << ' ' << maradek / 20 + 1 << ' ' << maradek % 20 + 1 << '\n';
}

int main() {
    int tev, tho, tnap;
    cin >> tev >> tho >> tnap;
    int hev, hho, hnap;
    cin >> hev >> hho >> hnap;

    // Tzolkin dátum -> napsorszám
    int tSorszam = (tev - 1) * 260 + (tho - 1) * 20 + (tnap - 1);
    // Haab dátum -> napsorszám (az 5 pótnap a 360. naptól van)
    int hSorszam = (hev - 1) * 365 + (hho == 0 ? 360 + hnap - 1 : (hho - 1) * 20 + hnap - 1);

    kiirHaab(tSorszam);
    kiirTzolkin(hSorszam);
    return 0;
}
