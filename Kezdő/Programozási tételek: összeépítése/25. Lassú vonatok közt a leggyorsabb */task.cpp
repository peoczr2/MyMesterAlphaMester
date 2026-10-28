/*
Megoldás lényege:
Egyetlen menetben végigmegyünk a vonatokon, és csak a 120 percnél hosszabb menetidejűeket vesszük figyelembe.
Megjegyezzük az eddigi legjobb (legkisebb menetidejű) jelöltet és annak sorszámát; csak szigorúan kisebb menetidő esetén cseréljük, így döntetlennél a korábbi, kisebb sorszám marad.
Ha egyetlen vonat sem lassúbb 120 percnél, nincs jelölt, és -1 a válasz.
Az idő O(N), ami N ≤ 100 esetén bőven belefér a 0,1 mp-es időlimitbe.
*/
/*
Hint 1: || Nem kell az összes vonatot eltárolni: elég egyetlen menetben nyilvántartani a jelenleg legjobb jelöltet. ||
Hint 2: || Két értéket tarts nyilván: a legjobb menetidőt és a hozzá tartozó sorszámot. A feltétel a 120 percnél nagyobb menetidő, és egyenlőség esetén a korábbi vonat maradjon. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int legjobb_sorszam = -1;
    int legjobb_ido = 0;
    for (int i = 1; i <= n; i++) {
        int ido;
        cin >> ido;
        if (ido > 120 && (legjobb_sorszam == -1 || ido < legjobb_ido)) {
            legjobb_sorszam = i;
            legjobb_ido = ido;
        }
    }
    if (legjobb_sorszam == -1) {
        cout << -1 << "\n";
    } else {
        cout << legjobb_sorszam << " " << legjobb_ido << "\n";
    }
    return 0;
}
