/*
Megoldás lényege:
A szavazatokat olvassuk addig, amíg el nem érjük a 0-t vagy a M szavazatot. Egy szavazat érvényes, ha 1 és N közötti szám, ezért ilyenkor a jelölt számlálóját növeljük, különben az érvénytelenek számát. A kerekítéses százalékokat egész számokkal számoljuk: egy c részt a d összesből a (200 * c + d) / (2 * d) egész osztás adja, ami félértéknél felfelé kerekít. A szavazás akkor érvényes, ha az érvényes szavazatok száma több mint a jogosultak fele, vagyis 2 * érvényes > M. A jelöltek listáját a szavazatok száma szerint csökkenő, azonos szavazatszámnál a sorszám szerint növekvő sorrendben rendezzük, és így írjuk ki. Az időigény O(M + N log N), a memóriaigény O(N).
*/
/*
Hint 1: || Minden szavazatot egyszer olvass be: az érvényesség a szám tartományától függ, az érvénytelen szavazatokat külön számold. A 0 jelzi a bemenet végét. ||
Hint 2: || A százalékot a jogosultak számához vagy az érvényes szavazatok számához kell viszonyítani, és egészre kerekítve kell kiírni. A kerekítést egész számokkal oldd meg, így nincs lebegőpontos hiba. ||
Hint 3: || A jelölteket egy vektorban számold, majd rendezd úgy, hogy a nagyobb szavazatszám legyen előbb, azonos szavazatszámnál a kisebb sorszám. Ehhez a rendezésnél egy összehasonlító függvényt adj meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> szavazat(n + 1, 0);
    long long ervenyes = 0, ervenytelen = 0;
    for (int i = 0; i < m; i++) {
        long long x;
        if (!(cin >> x) || x == 0) break;
        if (x >= 1 && x <= n) {
            szavazat[x]++;
            ervenyes++;
        } else {
            ervenytelen++;
        }
    }

    auto szazalek = [](long long c, long long d) -> long long {
        if (d == 0) return 0;
        return (200 * c + d) / (2 * d);
    };

    cout << "#\n";
    cout << ervenyes << " " << ervenytelen << "\n";

    cout << "#\n";
    cout << szazalek(ervenyes, m) << "%\n";

    cout << "#\n";
    if (2 * ervenyes > m) {
        cout << "igen\n";
    } else {
        cout << "nem\n";
    }

    vector<int> sorrend;
    for (int i = 1; i <= n; i++) sorrend.push_back(i);
    sort(sorrend.begin(), sorrend.end(), [&](int a, int b) {
        if (szavazat[a] != szavazat[b]) return szavazat[a] > szavazat[b];
        return a < b;
    });

    cout << "#\n";
    for (int j : sorrend) {
        cout << j << " " << szavazat[j] << " " << szazalek(szavazat[j], ervenyes) << "%\n";
    }

    return 0;
}
