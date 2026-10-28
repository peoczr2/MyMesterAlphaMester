/*
Megoldás lényege:
Minden mérést készültségi szintre alakítunk: 800 cm felett 1, 900 cm felett 2, 1000 cm felett 3, különben 0.
Az árvizek a legalább 1-es szintű mérések maximális, egymás utáni sorozatai, ezeket egy balról jobbra haladó bejárással találjuk meg.
Egy árvízen belül minden olyan szomszédos mérés-pár csökkenés, ahol a második mérés szintje kisebb az elsőénél, ezeket az árvíz bejárása közben számoljuk.
Az árvizek kezdetét, végét és csökkenésszámát eltároljuk, majd az első olyan árvizet írjuk ki, amelynek a csökkenésszáma maximális; ha ez 0, a negyedik sorba 0 kerül.
Az algoritmus egyetlen bejárás, így O(N) időben fut.
*/
/*
Hint 1: || Először minden mérést alakíts át készültségi szintté (0–3), majd az árvizek a legalább 1-es szintű mérések maximális, egymás utáni sorozatai. ||
Hint 2: || Egy árvízen belül akkor van csökkenés, amikor egy mérés szintje kisebb a közvetlenül előtte levő mérés szintjénél. Ezt az árvíz hossza alatt, egy bejárásban számold. ||
Hint 3: || Az árvíz végén jegyezd fel a kezdetét, a végét és a csökkenések számát. A legjobbat csak szigorúan nagyobb érték esetén cseréld le, így az első előfordulás marad meg. ||
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
    vector<int> s(n);
    for (int i = 0; i < n; i++) {
        int h;
        cin >> h;
        s[i] = szint(h);
    }

    vector<pair<int, int>> arviz;  // az árvizek [kezdet, vég] sorszámai (1-től)
    vector<int> csokkenes;         // az egyes árvizek készültség-csökkenéseinek száma

    int i = 0;
    while (i < n) {
        if (s[i] == 0) {
            i++;
            continue;
        }
        int kezdet = i;
        int db = 0;
        while (i < n && s[i] >= 1) {
            if (i > kezdet && s[i] < s[i - 1]) db++;
            i++;
        }
        arviz.push_back({kezdet + 1, i});
        csokkenes.push_back(db);
    }

    int k = arviz.size();
    cout << k << "\n";
    if (k == 0) return 0;

    for (int j = 0; j < k; j++) {
        if (j) cout << ' ';
        cout << arviz[j].first << ' ' << arviz[j].second;
    }
    cout << "\n";

    for (int j = 0; j < k; j++) {
        if (j) cout << ' ';
        cout << csokkenes[j];
    }
    cout << "\n";

    int legjobb = 0;
    for (int j = 1; j < k; j++) {
        if (csokkenes[j] > csokkenes[legjobb]) legjobb = j;
    }
    if (csokkenes[legjobb] == 0) {
        cout << 0 << "\n";
    } else {
        cout << arviz[legjobb].first << ' ' << arviz[legjobb].second << "\n";
    }
    return 0;
}
