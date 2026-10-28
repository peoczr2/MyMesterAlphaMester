/*
Megoldás lényege:
Az árvíz a legalább elsőfokú, egymás melletti mérések maximális sorozata, ezeket egyetlen balról jobbra haladó bejárással gyűjtjük ki.
Egy árvíz csak akkor kerül a válaszba, ha minden mérése pontosan elsőfokú, vagyis a bejárás közben nem fordul elő másod- vagy harmadfokú mérés.
A megfelelő árvizek kezdő és záró sorszámát növekvő sorrendben írjuk ki, együttes hosszuk pedig a záró és a kezdő index különbsége plusz egy, összegezve.
Az időigény O(N), ami N ≤ 10 000 esetén messze az időlimit alatt van.
*/
/*
Hint 1: || Egy árvíz olyan maximális sorozat, ahol minden mérés legalább elsőfokú. A végét nem kell előre tudnod: addig haladj, amíg a szint nulla nem lesz. ||
Hint 2: || Az aktuális árvízben közben jegyezd fel, előfordult-e másod- vagy harmadfokú mérés. Csak azok az árvizek számítanak, ahol ez nem történt meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Készültségi szint: 0 = nincs, 1 = elsőfokú, 2 = másodfokú, 3 = harmadfokú
int szint(int magassag) {
    if (magassag > 1000) return 3;
    if (magassag > 900) return 2;
    if (magassag > 800) return 1;
    return 0;
}

int main() {
    int n;
    cin >> n;
    vector<int> sz(n);
    for (int &x : sz) {
        int a;
        cin >> a;
        x = szint(a);
    }

    // A csak elsőfokú árvizek [kezdet, vége] párjai, 0-indexelve
    vector<pair<int, int>> arvizek;
    long long osszhossz = 0;
    int i = 0;
    while (i < n) {
        if (sz[i] == 0) {
            i++;
            continue;
        }
        int j = i;
        bool csak_elsofoku = true;
        while (j < n && sz[j] > 0) {
            if (sz[j] != 1) csak_elsofoku = false;
            j++;
        }
        // Az árvíz: [i, j-1]
        if (csak_elsofoku) {
            arvizek.push_back({i, j - 1});
            osszhossz += j - i;
        }
        i = j;
    }

    int k = arvizek.size();
    cout << k << '\n';
    if (k == 0) return 0;

    for (int t = 0; t < k; t++) {
        if (t > 0) cout << ' ';
        cout << arvizek[t].first + 1 << ' ' << arvizek[t].second + 1;
    }
    cout << '\n' << osszhossz << '\n';
    return 0;
}
