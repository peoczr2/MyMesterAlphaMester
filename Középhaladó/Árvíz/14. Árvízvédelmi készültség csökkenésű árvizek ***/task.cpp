/*
Megoldás lényege:
Minden mérésnek készültségi szintet rendelünk: 800 cm felett 1, 900 cm felett 2, 1000 cm felett 3, különben 0.
Az árvizek a legalább 1-es szintű mérések maximális, egymás utáni sorozatai, és ezeket egy balról jobbra haladó bejárással mind megtaláljuk.
Minden árvizen belül közben ellenőrizzük, hogy két egymás utáni mérés között csökken-e a szint, és ha igen, az árvizet a csökkenést tartalmazók listájába is felvesszük.
A kimenet első sora az árvizek darabszáma, a második sora ezek kezdete és vége, a harmadik sora a csökkenést tartalmazó árvizek darabszáma, a negyedik sora ezek kezdete és vége.
Ha nincs árvíz, illetve nincs csökkenést tartalmazó árvíz, a megfelelő darabszám 0 és nincs további sor.
Az algoritmus egyetlen lineáris bejárás, O(N) időben fut.
*/
/*
Hint 1: || Az árvizek a legalább elsőfokú készültségű mérések maximális, egymás utáni sorozatai; egyetlen balról jobbra haladó bejárás mindegyiket megtalálja. ||
Hint 2: || Egy árvízen belül elég a szomszédos mérések szintjét összehasonlítani: ha valahol kisebb a következő mérés szintje, az árvíz csökkenést tartalmaz. ||
Hint 3: || Tárold az összes árvizet és a csökkenést tartalmazókat kezdet-vég párokként két listában, majd a kimenetben előbb az összes árvizet, utána a csökkenést tartalmazókat írd ki. ||
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

void kiir(const vector<pair<int, int>>& v) {
    for (size_t j = 0; j < v.size(); j++) {
        if (j) cout << ' ';
        cout << v[j].first << ' ' << v[j].second;
    }
    cout << "\n";
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

    vector<pair<int, int>> arvizek;     // az összes árvíz [kezdet, vég]
    vector<pair<int, int>> csokkenok;   // a készültség csökkenést tartalmazó árvizek
    int i = 1;
    while (i <= n) {
        if (s[i] == 0) {
            i++;
            continue;
        }
        int a = i;
        bool csokkent = false;
        while (i <= n && s[i] >= 1) {
            if (i > a && s[i] < s[i - 1]) csokkent = true;
            i++;
        }
        int b = i - 1;
        arvizek.push_back({a, b});
        if (csokkent) csokkenok.push_back({a, b});
    }

    cout << arvizek.size() << "\n";
    if (arvizek.empty()) return 0;
    kiir(arvizek);

    cout << csokkenok.size() << "\n";
    if (csokkenok.empty()) return 0;
    kiir(csokkenok);
    return 0;
}
