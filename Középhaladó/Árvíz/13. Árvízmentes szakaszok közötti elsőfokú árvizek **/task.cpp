/*
Megoldás lényege:
Minden mérést átalakítunk készültségi szintre: 800 cm felett 1, 900 cm felett 2, 1000 cm felett 3, különben 0.
Az árvíz a legalább 1-es szintű mérések maximális, egymás utáni sorozata, ezeket egy balról jobbra haladó bejárással találjuk meg.
Egy árvíz akkor elsőfokú, ha minden pontja pontosan 1-es szintű, így az egész árvíz egyetlen, egyforma tulajdonságú folyószakasz.
Az árvíz két szélén álló szomszédos szakasz szükségképpen árvízmentes (0-s szintű), ezért csak azt kell ellenőrizni, hogy az árvíz nem kezdődik a legelső vagy nem végződik a legutolsó méréssel.
A kimenet első sorába az kerül, hogy van-e egyáltalán 0-s szintű mérés; ha nincs, a program 0-t ír ki és véget ér.
Az algoritmus egyetlen lineáris bejárás, O(N) időben fut.
*/
/*
Hint 1: || Egyetlen bejárásban keresd meg a legalább elsőfokú készültségű, egymás utáni mérések maximális sorozatait, és nézd meg, hogy mindegyikben csak 1-es szint szerepel-e. ||
Hint 2: || Ellenőrizd, hogy a sorozat előtt és után is van mérés (nem a sor elején vagy végén kezdődik vagy végződik), és csak ezeket az árvizeket írd ki. ||
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
    bool van_mentes = false;
    for (int i = 1; i <= n; i++) {
        int h;
        cin >> h;
        s[i] = szint(h);
        if (s[i] == 0) van_mentes = true;
    }

    if (!van_mentes) {
        cout << 0 << "\n";
        return 0;
    }

    vector<int> eredmeny;  // a megfelelő szakaszok kezdete és vége, párokban
    int i = 1;
    while (i <= n) {
        if (s[i] == 0) {
            i++;
            continue;
        }
        int a = i;
        bool csak_elso = true;
        while (i <= n && s[i] >= 1) {
            if (s[i] != 1) csak_elso = false;
            i++;
        }
        int b = i - 1;
        if (csak_elso && a > 1 && b < n) {
            eredmeny.push_back(a);
            eredmeny.push_back(b);
        }
    }

    cout << 1 << "\n" << eredmeny.size() / 2 << "\n";
    for (size_t j = 0; j < eredmeny.size(); j++) {
        if (j) cout << ' ';
        cout << eredmeny[j];
    }
    if (!eredmeny.empty()) cout << "\n";
    return 0;
}
