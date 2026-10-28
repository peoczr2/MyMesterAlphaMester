/*
Megoldás lényege:
Minden mérést készültségi szintre alakítunk: 800 cm-ig a szint 0 (nincs árvíz), különben legalább 1.
Az árvizek a legfeljebb 0-nál nagyobb szintű mérések maximális, egymás utáni sorozatai, ezeket egyetlen balról jobbra haladó bejárással gyűjtjük ki.
Egy árvíz csúcsmagassága a benne szereplő legnagyobb vízmagasság; ennek helyeként az első előfordulását írjuk ki.
Az árvíz akkor tartalmaz több, egymással nem szomszédos csúcsmagasságot, ha a csúcsmagasság első és utolsó előfordulásának sorszáma legalább 2-vel különbözik, mert így van köztük nem szomszédos pár.
Az időigény O(N), mivel minden árvízen belül egy lineáris bejárás fut.
*/
/*
Hint 1: || Az árvizek a nullától nagyobb készültségi szintű mérések maximális, összefüggő sorozatai. Haladj balról jobbra, és minden árvízhez jegyezd fel a kezdő és a záró sorszámát. ||
Hint 2: || Egy árvíz csúcsmagassága a benne lévő legnagyobb vízmagasság. Az árvízen belül keresd meg ennek első és utolsó előfordulását. ||
Hint 3: || Az árvíz pontosan akkor tartalmaz több, egymással nem szomszédos csúcsmagasságot, ha az utolsó és az első előfordulás sorszáma legalább 2-vel tér el egymástól. A kiíráskor a helyet az első előfordulással add meg. ||
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

// Egy árvíz: [bal, jobb] sorszámok, csúcsmagasság első helye és értéke, és a több csúcs jelzője
struct Arviz {
    int bal, jobb, hely, csucs;
    bool tobbCsucs;
};

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1), s(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s[i] = szint(a[i]);
    }

    vector<Arviz> arvizek;
    int i = 1;
    while (i <= n) {
        if (s[i] == 0) {
            i++;
            continue;
        }
        int j = i;
        while (j + 1 <= n && s[j + 1] >= 1) j++;

        // Csúcsmagasság: az árvíz legnagyobb vízmagassága, első és utolsó előfordulásával
        int csucs = a[i], elso = i, utolso = i;
        for (int p = i; p <= j; p++) {
            if (a[p] > csucs) {
                csucs = a[p];
                elso = p;
                utolso = p;
            } else if (a[p] == csucs) {
                utolso = p;
            }
        }
        arvizek.push_back({i, j, elso, csucs, utolso - elso >= 2});
        i = j + 1;
    }

    int k = arvizek.size();
    cout << k << '\n';
    if (k == 0) return 0;

    for (int t = 0; t < k; t++) {
        if (t > 0) cout << ' ';
        cout << arvizek[t].bal << ' ' << arvizek[t].jobb;
    }
    cout << '\n';

    for (int t = 0; t < k; t++) {
        if (t > 0) cout << ' ';
        cout << arvizek[t].hely << ' ' << arvizek[t].csucs;
    }
    cout << '\n';

    vector<Arviz> tobb;
    for (const Arviz& arviz : arvizek) {
        if (arviz.tobbCsucs) tobb.push_back(arviz);
    }

    int m = tobb.size();
    cout << m << '\n';
    if (m == 0) return 0;

    for (int t = 0; t < m; t++) {
        if (t > 0) cout << ' ';
        cout << tobb[t].bal << ' ' << tobb[t].jobb;
    }
    cout << '\n';
    return 0;
}
