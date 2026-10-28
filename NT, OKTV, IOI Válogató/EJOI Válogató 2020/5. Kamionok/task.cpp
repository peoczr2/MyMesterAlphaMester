/*
Megoldas: a rendezett hataridok elso i elemehez tartozik egy p_i kapacitas,
amely megadja, hogy egy kamion legfeljebb hanyadik szallitmanyt viheti el, ha a
szallitmanyok sorrendje ezen a kamionon belul megmarad. Ez p_i = floor((H_i+S)/(2S)).

Az elso i igenyhez legalabb ceil(i / p_i) kamion kell, mert egy kamion ebben a
prefixben legfeljebb p_i igenyt kepes elvinni. Ez a hatar minden prefixre eleg,
tehat a minimis kamionszam a prefixek ilyen lower boundjainak maximuma.

Ha K kamion kell, akkor a requesteket k darab kamionra ciklikusan szetosztva
mindegyik kamionra vagy floor(N/K), vagy ceil(N/K) darab jut, es ez mar mindig
felelosen tarthato a fenti kapacitasok mellett. A legutolso kamion visszaerkezesi
napja ezert 2*S*ceil(N/K).
*/
/*
Hint 1: || Egy kamion egyszerre egy szállítmányt visz. Ha d a kamion indulási napja, az igény teljesül, ha d+S-1 nem nagyobb a határidőnél, a kamion következő indulása pedig legkorábban d+2*S lehet. ||
Hint 2: || Határidő szerint növekvő sorrendben haladva minden igényhez számold ki, hány indulási lehetőség (az első naptól kezdve 2*S-ként) fér a határidőbe. Ha K kamion van, a legfeljebb c indulási lehetőségű igények közül legfeljebb K*c fér el; a minimális K ezekből a korlátokból adódik. ||
Hint 3: || A második kérdésnél a legkorábbi visszaérés az a nap, amikor a legtöbb utat megtevő kamion visszaér: N igényt K kamion ciklikusan osztva visz, így valamelyik kamionnak legalább ceil(N/K) útja lesz, és az utak 2*S-ként követik egymást. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s;
    cin >> n >> s;

    long long trucks = 0;
    for (int i = 1; i <= n; ++i) {
        long long h;
        cin >> h;
        long long cap = (h + s) / (2LL * s);
        long long need = (i + cap - 1) / cap;
        trucks = max(trucks, need);
    }

    long long lastReturn = 2LL * s * ((n + trucks - 1) / trucks);
    cout << trucks << '\n' << lastReturn << '\n';
    return 0;
}