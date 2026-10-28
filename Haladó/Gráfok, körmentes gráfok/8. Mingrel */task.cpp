/*
Megoldás lényege:
Két egymás utáni szó első olyan pozíciója, ahol a betűk különböznek, megmondja, hogy a mingrel ábécében melyik betű
van előrébb. Ezekből egy 26 csúcsú irányított gráf épül, amelynek éle a-ból b-be megy, ha a előbb van. Egy betűsorrend
pontosan akkor felel meg a szavak sorrendjének, ha betartja ezeket az éleket, vagyis a gráf egy topologikus rendezése.
Ha egy szó az utána következő szó valódi előtagja, a két szó sorrendje nem ad új információt. Ha fordítva áll,
vagyis a hosszabb szó van elöl, a sorrend lehetetlen, és -1 a válasz. A 26 betűt Kahn-algoritmussal rendezzük, minden lépésben a
legkisebb elérhető betűt választva. Több helyes válasz is létezhet, bármelyik elfogadható.
Az időigény O(a szavak összes karaktere + 26^2).
*/
/*
Hint 1: || Hasonlítsd össze minden két szomszédos szót, és keresd meg az első pozíciót, ahol a betűk különböznek. Ez a két betű sorrendjét adja meg. ||
Hint 2: || Az így kapott 26 csúcsú gráfban topologikus rendezés adja a keresett ábécét. Kahn-algoritmussal dolgozz: mindig a legkisebb olyan betűt vedd, amelynek már nincs előtte álló betűje. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> words(n);
    for (int i = 0; i < n; ++i) {
        cin >> words[i];
    }

    // before[a][b]: az a betű a mingrel ábécében előrébb van, mint a b.
    bool before[26][26] = {};
    for (int i = 0; i + 1 < n; ++i) {
        const string &x = words[i];
        const string &y = words[i + 1];
        size_t len = min(x.size(), y.size());
        size_t j = 0;
        while (j < len && x[j] == y[j]) ++j;
        if (j < len) {
            before[x[j] - 'a'][y[j] - 'a'] = true;
        } else if (x.size() > y.size()) {
            cout << -1 << "\n";
            return 0;
        }
    }

    int indeg[26] = {};
    for (int a = 0; a < 26; ++a) {
        for (int b = 0; b < 26; ++b) {
            if (before[a][b]) ++indeg[b];
        }
    }

    // Kahn-algoritmus: mindig a legkisebb betű, amelynek nincs előtte álló betűje.
    string result;
    bool used[26] = {};
    for (int step = 0; step < 26; ++step) {
        int pick = -1;
        for (int c = 0; c < 26; ++c) {
            if (!used[c] && indeg[c] == 0) {
                pick = c;
                break;
            }
        }
        if (pick < 0) {
            cout << -1 << "\n";
            return 0;
        }
        used[pick] = true;
        result.push_back(char('a' + pick));
        for (int b = 0; b < 26; ++b) {
            if (before[pick][b]) --indeg[b];
        }
    }

    cout << result << "\n";
    return 0;
}
