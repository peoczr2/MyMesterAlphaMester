/*
Megoldás lényege:
Minden mérést készültségi szintre alakítunk: 800 cm-ig a szint 0 (nincs árvíz), különben legalább 1.
Az árvízmentes folyószakaszok a 0-s szintű mérések maximális, egymás utáni sorozatai, ezeket egyetlen balról jobbra haladó bejárással gyűjtjük ki.
Két szomszédos árvízmentes szakasz távolsága a második szakasz kezdő sorszáma mínusz az első szakasz záró sorszáma.
A legtávolabbi párt maximumkereséssel találjuk meg; csak szigorúan nagyobb távolságnál cserélünk, így ha több ilyen pár van, az első marad.
Az algoritmus O(N) időben fut, ami N ≤ 10 000 esetén messze az időlimit (0,1 mp) alatt van.
*/
/*
Hint 1: || Az árvízmentes szakaszok a 0-s készültségi szintű mérések maximális, összefüggő sorozatai. Haladj balról jobbra, és amíg a szint 0, növeld az aktuális szakaszt. ||
Hint 2: || Két szomszédos árvízmentes szakasz távolsága: a következő szakasz kezdő sorszáma mínusz az előző szakasz záró sorszáma. Ezeket a távolságokat egy tömbben tárold. ||
Hint 3: || A távolságok között keresd a maximumot, és csak szigorúan nagyobb értéknél frissíts. Ha K < 2, a második sor után nincs több kiírás. ||
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

// Egy árvízmentes folyószakasz [bal, jobb] sorszámokkal (1-től indexelve)
struct Szakasz {
    int bal, jobb;
};

int main() {
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++) {
        int magassag;
        cin >> magassag;
        s[i] = szint(magassag);
    }

    vector<Szakasz> arvizmentes;
    int i = 1;
    while (i <= n) {
        if (s[i] != 0) {
            i++;
            continue;
        }
        int j = i;
        while (j + 1 <= n && s[j + 1] == 0) j++;
        arvizmentes.push_back({i, j});
        i = j + 1;
    }

    int k = arvizmentes.size();
    cout << k << '\n';
    if (k == 0) return 0;

    for (int t = 0; t < k; t++) {
        if (t > 0) cout << ' ';
        cout << arvizmentes[t].bal << ' ' << arvizmentes[t].jobb;
    }
    cout << '\n';
    if (k < 2) return 0;

    // Szomszédos szakaszok távolsága: a második kezdete mínusz az első vége
    vector<int> tav(k - 1);
    for (int t = 0; t + 1 < k; t++) {
        tav[t] = arvizmentes[t + 1].bal - arvizmentes[t].jobb;
    }
    for (int t = 0; t < k - 1; t++) {
        if (t > 0) cout << ' ';
        cout << tav[t];
    }
    cout << '\n';

    int legtavolabb = 0;
    for (int t = 1; t < k - 1; t++) {
        if (tav[t] > tav[legtavolabb]) legtavolabb = t;
    }
    cout << arvizmentes[legtavolabb].bal << ' ' << arvizmentes[legtavolabb].jobb << ' '
         << arvizmentes[legtavolabb + 1].bal << ' ' << arvizmentes[legtavolabb + 1].jobb << '\n';
    return 0;
}
