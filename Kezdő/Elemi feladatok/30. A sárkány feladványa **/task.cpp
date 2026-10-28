/*
Megoldás lényege: az A és B számmal való oszthatóság egyszerre azt jelenti, hogy a keresett szám L = lnko-val kapott legkisebb közös többszörös (lkkt) többszöröse. Egy N-jegyű szám akkor jó, ha L többszöröse és 10^(N-1) ≤ szám < 10^N. A 10^(N-1)-nél nem kisebb legkisebb L-többszörös 10^(N-1) + r, ahol r = (L - 10^(N-1) mod L) mod L; ha ez már nem fér bele N jegybe, nincs megoldás. Mivel N akár 1000 is lehet, a számot nem tároljuk egész típusban, hanem jegyenként állítjuk elő, és r-et átvitellel adjuk hozzá. Az időigény O(N), ami bőven elég.
*/
/*
Hint 1: || A feladat kérdése az, hogy van-e N-jegyű szám, amely az A és B legkisebb közös többszöröse (L) többszöröse. Az L kiszámolható így: A / lnko(A, B) * B, és mivel A, B ≤ 100 000, L is belefér 64 bites egész számba. ||
Hint 2: || Az N-jegyű számok a 10^(N-1)-től 10^N - 1-ig terjednek. Keresd az első L-többszöröst 10^(N-1)-től felfelé: ez 10^(N-1) + r, ahol r azt mutatja, mennyi kell 10^(N-1) mod L-ből L-ig. Ha ez a szám már N-nél több jegyű, nincs megoldás. ||
Hint 3: || N akár 1000 is lehet, ezért 10^(N-1) mod L-t lépésenként, maradékos szorzással számold (a szorzat így nem lép túl a 64 biten). A 10^(N-1) + r számot jegyenként állítsd elő: az első jegy 1, a többi nulla, r-et pedig a végétől átvitellel add hozzá. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    for (int teszt = 0; teszt < 3; teszt++) {
        long long a, b;
        int n;
        cin >> a >> b >> n;

        long long l = a / gcd(a, b) * b;

        // 10^(n-1) mod l
        long long maradek = 1 % l;
        for (int i = 1; i < n; i++) {
            maradek = maradek * 10 % l;
        }

        // ennyi kell 10^(n-1)-hez, hogy l többszörösét kapjuk
        long long r = (l - maradek) % l;

        // 10^(n-1) + r jegyei: 1 és utána nullák, r-et a végétől átvitellel adjuk hozzá
        vector<int> jegy(n, 0);
        jegy[0] = 1;
        long long atvitel = r;
        for (int i = n - 1; i >= 0 && atvitel > 0; i--) {
            long long s = jegy[i] + atvitel;
            jegy[i] = s % 10;
            atvitel = s / 10;
        }

        if (atvitel > 0) {
            cout << -1 << "\n";
        } else {
            for (int d : jegy) cout << d;
            cout << "\n";
        }
    }
    return 0;
}
