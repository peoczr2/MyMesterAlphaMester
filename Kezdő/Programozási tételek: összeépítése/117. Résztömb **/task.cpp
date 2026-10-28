/*
Megoldás lényege:
A legkisebb szorzatú részhalmaz esetekre bontható. Ha a nem nulla elemekből negatív szorzat képezhető, a
legnagyobb abszolútértékű negatív szorzatot keressük. Minden nem nulla elem abszolút értéke legalább 1, ezért
az összes nem nulla elem szorzata adja a legnagyobb abszolútértéket. Ha a negatív elemek száma páratlan, ez
a szorzat negatív, tehát ez a válasz. Ha páros, egyetlen negatív elemet kell kihagyni: azt, amelyiknek a
legkisebb az abszolútértéke, így az abszolútérték a lehető legkevésbé csökken. Ha nincs negatív elem, a
válasz 0 (ha van nulla), különben a legkisebb pozitív elem. Az időigény O(N), a szorzatokat nem számoljuk ki,
így nincs túlcsordulás.
*/
/*
Hint 1: || Először azt döntsd el, lehet-e negatív szorzatot kapni. Ez a negatív elemek számának paritásától függ, a szorzat konkrét értékét nem kell kiszámolni. ||
Hint 2: || Minden nem nulla elem abszolút értéke legalább 1, ezért a nem nulla elemek összessége adja a legnagyobb abszolútértéket. A nullát érdemes kihagyni, mert a nullát tartalmazó szorzat 0. ||
Hint 3: || Ha a negatív elemek száma páros, pontosan egy negatív elemet hagyj ki: azt, amelynek a legkisebb az abszolútértéke. Ha nincs negatív elem, a válasz a 0, ha van nulla, különben a legkisebb pozitív elem. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    // negatív elemek száma, legkisebb abszolútértékű negatív elem, első nulla, legkisebb pozitív elem
    int negCount = 0, negMin = -1, zero = -1, posMin = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            if (zero < 0) zero = i;
        } else if (a[i] < 0) {
            negCount++;
            if (negMin < 0 || a[i] > a[negMin]) negMin = i; // negatívoknál a nagyobb szám a kisebb abszolútérték
        } else {
            if (posMin < 0 || a[i] < a[posMin]) posMin = i;
        }
    }

    vector<char> keep(n, 0);
    if (negCount % 2 == 1) {
        // páratlan számú negatív: a nem nulla elemek szorzata negatív és a legnagyobb abszolútértékű
        for (int i = 0; i < n; i++) keep[i] = (a[i] != 0);
    } else if (negCount > 0) {
        // páros számú negatív: a legkisebb abszolútértékű negatívot kihagyjuk
        for (int i = 0; i < n; i++) keep[i] = (a[i] != 0);
        keep[negMin] = 0;
    } else if (zero >= 0) {
        keep[zero] = 1;
    } else {
        keep[posMin] = 1;
    }

    vector<int> res;
    for (int i = 0; i < n; i++)
        if (keep[i]) res.push_back(a[i]);

    cout << res.size() << '\n';
    for (size_t i = 0; i < res.size(); i++)
        cout << res[i] << (i + 1 < res.size() ? ' ' : '\n');
    return 0;
}
