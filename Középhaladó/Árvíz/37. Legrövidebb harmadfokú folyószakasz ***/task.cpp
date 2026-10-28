/*
Megoldás lényege:
A mérések készültségi szintje a vízállásból adódik: 1000 cm-nél magasabb vízállás esetén a szint 3, 900 cm felett 2, 800 cm felett 1, egyébként 0.
A folyószakaszok a leghosszabb egymás melletti, azonos szintű mérések, amelyeket egyetlen balról jobbra haladó bejárással gyűjthetünk ki.
A harmadfokú folyószakaszok a 3-as szintű szakaszok: számukat, kezdő és záró sorszámukat, valamint hosszukat ebből a bejárásból megkapjuk.
A legrövidebb közülük az első, amelynek a hossza minimális, így a kiíráshoz már csak egy minimumkeresés kell.
Az időigény O(N), ami N ≤ 10 000 esetén messze az időlimit (0,1 mp) alatt van.
*/
/*
Hint 1: || Haladj balról jobbra, és amíg a készültségi szint nem változik, ugyanazt a folyószakaszt növeld. Csak a 3-as szintű szakaszokra van szükséged. ||
Hint 2: || Egy mérés harmadfokú, ha a vízállása 1000 cm-nél magasabb. Minden ilyen szakasz kezdő és záró sorszámát tárold el, a hossz záró - kezdő + 1. ||
Hint 3: || A legrövidebb szakasz keresésénél csak szigorúan kisebb hossz esetén cseréld a jelöltet, így az első ilyen szakasz marad meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Készültségi szint: 0 = nincs árvíz, 1 = elsőfokú, 2 = másodfokú, 3 = harmadfokú
int szint(int magassag) {
    if (magassag > 1000) return 3;
    if (magassag > 900) return 2;
    if (magassag > 800) return 1;
    return 0;
}

// Egy folyószakasz: a [bal, jobb] mérései azonos szintűek
struct Szakasz {
    int bal, jobb, szint;

    int hossz() const { return jobb - bal + 1; }
};

// A leghosszabb egymás melletti, azonos szintű mérések sorozatai (1-től indexelve)
vector<Szakasz> folyoszakaszok(const vector<int>& a, int n) {
    vector<Szakasz> eredmeny;
    int i = 1;
    while (i <= n) {
        int j = i;
        while (j + 1 <= n && szint(a[j + 1]) == szint(a[i])) j++;
        eredmeny.push_back({i, j, szint(a[i])});
        i = j + 1;
    }
    return eredmeny;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<Szakasz> harmadfokuak;
    for (const Szakasz& sz : folyoszakaszok(a, n)) {
        if (sz.szint == 3) harmadfokuak.push_back(sz);
    }

    int k = harmadfokuak.size();
    cout << k << '\n';
    if (k == 0) return 0;

    for (int t = 0; t < k; t++) {
        if (t > 0) cout << ' ';
        cout << harmadfokuak[t].bal << ' ' << harmadfokuak[t].jobb;
    }
    cout << '\n';

    for (int t = 0; t < k; t++) {
        if (t > 0) cout << ' ';
        cout << harmadfokuak[t].hossz();
    }
    cout << '\n';

    int legrovidebb = 0;
    for (int t = 1; t < k; t++) {
        if (harmadfokuak[t].hossz() < harmadfokuak[legrovidebb].hossz()) legrovidebb = t;
    }
    cout << harmadfokuak[legrovidebb].bal << ' ' << harmadfokuak[legrovidebb].jobb << '\n';
    return 0;
}
