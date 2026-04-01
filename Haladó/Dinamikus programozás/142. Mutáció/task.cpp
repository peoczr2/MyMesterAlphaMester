/*
Megoldási ötlet:
Legyen az első kód s, a második t. Egy betű másik betűvé alakításának ára a két irány közül a
kisebb körkörös ábécébeli távolság, mert ugyanazon a helyen végig csak növelő vagy végig csak
csökkentő lépésekre van szükség. A beszúrás ára 2, a belső törlés ára 2, de az s elejéről levágott
prefix és a végéről levágott suffix betűi csak 1-1 energiába kerülnek.

Ezért az optimális szerkesztés három szakaszra bontható:
1. még nem használtunk fel betűt s-ből, tehát csak olcsó prefix-törléseket és beszúrásokat végzünk;
2. már bent vagyunk a középső, valóban összeillesztett részben, itt a szokásos súlyozott edit
    distance lépései élnek;
3. már nem fogunk több betűt felhasználni s-ből, ezért csak olcsó suffix-törlések és beszúrások
    maradnak.

Dinamikus programozással vezetjük mindhárom szakasz legjobb árát az s első i és t első j betűjére.
Az "előtte" állapotból olcsó törléssel vagy beszúrással maradhatunk ugyanebben a szakaszban.
A "középen" állapotban lehet törölni 2-ért, beszúrni 2-ért, illetve az aktuális két betűt
egymásnak megfeleltetni az átalakítási árral. Az "utána" állapotba akkor lépünk át, amikor a
középső rész már befejeződött; innen kezdve a törlés ismét 1-be kerül, a beszúrás továbbra is 2.

Mindhárom átmenet csak az előző sorból és a bal szomszédból dolgozik, ezért elég soronként három
darab N+1 hosszú tömb. Az algoritmus időigénye O(M*N), memóriaigénye O(N).
*/
/*
Hint 1: || Az olcsó törlések csak az első kód egy prefixén és egy suffixén történhetnek, középen nem. ||
Hint 2: || Emiatt érdemes három fázist külön kezelni: a középső rész előtt, a középső részben és a középső rész után. ||
Hint 3: || A középső fázis átmenetei ugyanazok, mint egy súlyozott edit distance-nél: törlés, beszúrás, illetve két betű összepárosítása. ||
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int atalakitasi_ar(char bal, char jobb) {
    int elteres = abs(bal - jobb);
    return min(elteres, 26 - elteres);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    string s, t;

    cin >> m >> s >> n >> t;

    const int VEGTELEN = 1'000'000'000;

    vector<int> elo_elott(n + 1), elo_kozep(n + 1, VEGTELEN), elo_utana(n + 1, VEGTELEN);
    for (int j = 0; j <= n; ++j) {
        elo_elott[j] = 2 * j;
    }

    for (int i = 1; i <= m; ++i) {
        vector<int> most_elott(n + 1, VEGTELEN);
        vector<int> most_kozep(n + 1, VEGTELEN);
        vector<int> most_utana(n + 1, VEGTELEN);

        most_elott[0] = elo_elott[0] + 1;
        if (min(elo_kozep[0], elo_utana[0]) < VEGTELEN) {
            most_utana[0] = min(elo_kozep[0], elo_utana[0]) + 1;
        }

        for (int j = 1; j <= n; ++j) {
            most_elott[j] = min(elo_elott[j] + 1, most_elott[j - 1] + 2);

            int ar = atalakitasi_ar(s[i - 1], t[j - 1]);
            most_kozep[j] = min({
                elo_kozep[j] + 2,
                most_kozep[j - 1] + 2,
                elo_kozep[j - 1] + ar,
                elo_elott[j - 1] + ar
            });

            most_utana[j] = min({
                min(elo_kozep[j], elo_utana[j]) + 1,
                min(most_kozep[j - 1], most_utana[j - 1]) + 2,
                most_kozep[j]
            });
        }

        swap(elo_elott, most_elott);
        swap(elo_kozep, most_kozep);
        swap(elo_utana, most_utana);
    }

    cout << min({elo_elott[n], elo_kozep[n], elo_utana[n]}) << '\n';
    return 0;
}