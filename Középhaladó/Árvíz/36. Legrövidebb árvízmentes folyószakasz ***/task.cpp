/*
Megoldás lényege:
A mérések készültségi szintje a vízállásból adódik: 800 cm-nél nem magasabb vízállás esetén nincs árvíz (0-s szint), egyébként a szint legalább 1.
A folyószakaszok a leghosszabb egymás melletti, azonos szintű mérések, amelyeket egyetlen balról jobbra haladó bejárással gyűjthetünk ki.
Az árvízmentes folyószakaszok a 0-s szintű szakaszok: számukat, kezdő és záró sorszámukat, valamint hosszukat ebből a bejárásból közvetlenül megkapjuk.
A legrövidebb közülük az első, amelynek a hossza minimális, így a kiíráshoz már csak egy minimumkeresés kell.
Az időigény O(N), ami N ≤ 10 000 esetén messze az időlimit (0,1 mp) alatt van.
*/
/*
Hint 1: || Haladj balról jobbra, és amíg a készültségi szint nem változik, ugyanazt a folyószakaszt növeld. Az árvízmentes folyószakasz a 0-s szintű futam. ||
Hint 2: || Minden egyes szakaszhoz tárold el a kezdő és a záró sorszámát. A hossz záró - kezdő + 1, ezt a kiíráshoz külön is ki lehet számolni. ||
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

    vector<Szakasz> arvizmentes;
    for (const Szakasz& sz : folyoszakaszok(a, n)) {
        if (sz.szint == 0) arvizmentes.push_back(sz);
    }

    int k = arvizmentes.size();
    cout << k << '\n';
    if (k == 0) return 0;

    for (int t = 0; t < k; t++) {
        if (t > 0) cout << ' ';
        cout << arvizmentes[t].bal << ' ' << arvizmentes[t].jobb;
    }
    cout << '\n';

    for (int t = 0; t < k; t++) {
        if (t > 0) cout << ' ';
        cout << arvizmentes[t].hossz();
    }
    cout << '\n';

    int legrovidebb = 0;
    for (int t = 1; t < k; t++) {
        if (arvizmentes[t].hossz() < arvizmentes[legrovidebb].hossz()) legrovidebb = t;
    }
    cout << arvizmentes[legrovidebb].bal << ' ' << arvizmentes[legrovidebb].jobb << '\n';
    return 0;
}
