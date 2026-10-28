/*
Megoldás lényege:
A két naptár ugyanazt a 18980 napos ciklust írja le (52 haab év = 73 tzolkin év = 18980 nap), csak más
hosszúságú években és más hónapszerkezettel. Ezért mindkét dátumot egy abszolút sorszámmá alakítjuk: a
kezdőnaptól számolt napok száma (0-tól indexelve). A tzolkin évben 260, a haab évben 365 nap van, így az évet
a sorszám osztásával, a hónapot és a napot a maradékkal kapjuk vissza. A haab év végi 5 napja a 360–364-es
maradékot kapja, ezért ott a hónap 0. Az időigény és a memóriaigény O(1).
*/
/*
Hint 1: || Mindkét naptár a kezdettől eltelt napok számával írható le, ha ugyanazon a napon indulunk. Ezután már csak azt kell eldöntened, hogyan kapod vissza az évet, a hónapot és a napot ebből a sorszámból. ||
Hint 2: || Tzolkin dátumból: sorszám = (év-1)·260 + (hónap-1)·20 + (nap-1). Haab dátumból: sorszám = (év-1)·365 + (hónap-1)·20 + (nap-1), de ha HHO = 0 (az év végi 5 nap), akkor a hónap-tag helyett 360 áll. Visszafelé az évet a sorszám osztása adja, a maradékból a hónap és a nap számítható. ||
*/
#include <bits/stdc++.h>
using namespace std;

static pair<int, pair<int, int>> to_haab(long long sorszam) {
    int ev = sorszam / 365 + 1;
    int maradek = sorszam % 365;
    int honap, nap;
    if (maradek < 360) {
        honap = maradek / 20 + 1;
        nap = maradek % 20 + 1;
    } else {
        honap = 0;
        nap = maradek - 360 + 1;
    }
    return {ev, {honap, nap}};
}

static pair<int, pair<int, int>> to_tzolkin(long long sorszam) {
    int ev = sorszam / 260 + 1;
    int maradek = sorszam % 260;
    int honap = maradek / 20 + 1;
    int nap = maradek % 20 + 1;
    return {ev, {honap, nap}};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tev, tho, tnap;
    int hev, hho, hnap;
    cin >> tev >> tho >> tnap;
    cin >> hev >> hho >> hnap;

    long long t_sorszam = 1LL * (tev - 1) * 260 + 1LL * (tho - 1) * 20 + (tnap - 1);
    long long h_sorszam = 1LL * (hev - 1) * 365 + (hho == 0 ? 360 : 1LL * (hho - 1) * 20) + (hnap - 1);

    auto [hev2, hn] = to_haab(t_sorszam);
    auto [tev2, tn] = to_tzolkin(h_sorszam);

    cout << hev2 << ' ' << hn.first << ' ' << hn.second << '\n';
    cout << tev2 << ' ' << tn.first << ' ' << tn.second << '\n';
    return 0;
}
