/*
Megoldás lényege:
A készültségi szinteket most is a 800, 900 és 1000 cm határok szerint számoljuk, az árvizek pedig a legalább 1-es szintű maximális, egymás utáni szakaszok.
Balról jobbra haladva azt az első árvizet keressük, amelyben van legalább 2 hosszú, folyamatos 3-as szintű szakasz, mert csak ez az árvíz kell.
Ezen az árvízen belül összegyűjtjük a legalább 2 hosszú, 3-as szintű folyószakaszokat (kezdet, vég), kiszámoljuk a hosszukat, majd kiválasztjuk a leghosszabbat; egyenlő hossz esetén az elsőt.
Ha nincs ilyen árvíz, a program csak a 0 0 sort írja ki.
Az algoritmus minden mérést legfeljebb kétszer érint, ezért O(N) időben fut.
*/
/*
Hint 1: || Az árvizek megkeresése egyetlen balról jobbra haladó bejárással történik: a legalább 1-es szintű, maximális egymás utáni szakaszok az árvizek. Az első olyan kell, amelyben van legalább 2 hosszú 3-as szakasz. ||
Hint 2: || Egy árvízen belül a 3-as szintű mérések futamait kell kiszedni: egy futam akkor marad meg, ha legalább 2 elemből áll. Ehhez az árvíz határain belül egy második, belső bejárás kell. ||
Hint 3: || A kimenet sorrendje: az árvíz kezdete és vége, a megmaradt futamok darabszáma, a futamok kezdete és vége, a hosszaik, végül a leghosszabb futam kezdete és vége (egyenlőség esetén az elsőt). ||
*/
#include <bits/stdc++.h>
using namespace std;

// Készültségi szint: 0 (nincs), 1 (elsőfokú), 2 (másodfokú), 3 (harmadfokú)
int szint(int h) {
    if (h <= 800) return 0;
    if (h <= 900) return 1;
    if (h <= 1000) return 2;
    return 3;
}

int main() {
    int n;
    cin >> n;
    vector<int> s(n + 2, 0);  // 1-től indexelünk
    for (int i = 1; i <= n; i++) {
        int h;
        cin >> h;
        s[i] = szint(h);
    }

    int i = 1;
    while (i <= n) {
        if (s[i] == 0) {
            i++;
            continue;
        }
        int a = i;
        while (i <= n && s[i] >= 1) i++;
        int b = i - 1;  // az árvíz [a, b]

        // Az árvízen belüli, legalább 2 hosszú, 3-as szintű folyószakaszok
        vector<pair<int, int>> futamok;
        int p = a;
        while (p <= b) {
            if (s[p] != 3) {
                p++;
                continue;
            }
            int q = p;
            while (q + 1 <= b && s[q + 1] == 3) q++;
            if (q - p + 1 >= 2) futamok.push_back({p, q});
            p = q + 1;
        }

        if (!futamok.empty()) {
            int legjobb = 0;  // az első leghosszabb
            for (size_t j = 1; j < futamok.size(); j++) {
                int hossz_j = futamok[j].second - futamok[j].first + 1;
                int hossz_legjobb = futamok[legjobb].second - futamok[legjobb].first + 1;
                if (hossz_j > hossz_legjobb) legjobb = j;
            }
            cout << a << ' ' << b << "\n";
            cout << futamok.size() << "\n";
            for (size_t j = 0; j < futamok.size(); j++) {
                if (j) cout << ' ';
                cout << futamok[j].first << ' ' << futamok[j].second;
            }
            cout << "\n";
            for (size_t j = 0; j < futamok.size(); j++) {
                if (j) cout << ' ';
                cout << futamok[j].second - futamok[j].first + 1;
            }
            cout << "\n";
            cout << futamok[legjobb].first << ' ' << futamok[legjobb].second << "\n";
            return 0;
        }
    }

    cout << "0 0\n";
    return 0;
}
