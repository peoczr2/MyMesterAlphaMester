/*
Megoldás lényege:
A vízállásokból készültségi szint lesz: az árvízmentes mérés szintje 0, vagyis legfeljebb 800 cm.
Az árvízmentes folyószakasz az azonos (0) szintű mérések maximális, egymás utáni sorozata, ezeket egyetlen balról jobbra haladó bejárással gyűjtjük ki.
Minden ilyen szakasz kezdő és záró indexét és hosszát kiírjuk, a hosszakat pedig egy összegző változóban összeadjuk a negyedik sorhoz.
Az időigény O(N), ami N ≤ 10 000 esetén az időlimit alatt van.
*/
/*
Hint 1: || Egy mérés akkor árvízmentes, ha vízállása legfeljebb 800 cm. Az árvízmentes folyószakasz ezeknek az egymás utáni sorozata. ||
Hint 2: || Egy bejárásban gyűjtsd ki a szakaszok kezdő és záró indexét. A szakasz hossza a két index különbsége plusz egy. ||
Hint 3: || Az összes árvízmentes szakasz hosszát egyetlen összegző változóban gyűjtsd. Ha nincs ilyen szakasz, elég a 0 kiírása. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Készültségi szint: 0 = nincs árvíz, 1..3 = elsőfokú..harmadfokú
int szint(int magassag) {
    if (magassag > 1000) return 3;
    if (magassag > 900) return 2;
    if (magassag > 800) return 1;
    return 0;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    // Az árvízmentes folyószakaszok [kezdet, vége] párjai, 0-indexelve
    vector<pair<int, int>> szakaszok;
    int i = 0;
    while (i < n) {
        if (szint(a[i]) > 0) {
            i++;
            continue;
        }
        int j = i;
        while (j + 1 < n && szint(a[j + 1]) == 0) j++;
        szakaszok.push_back({i, j});
        i = j + 1;
    }

    int k = szakaszok.size();
    cout << k << '\n';
    if (k == 0) return 0;

    for (int t = 0; t < k; t++) {
        if (t > 0) cout << ' ';
        cout << szakaszok[t].first + 1 << ' ' << szakaszok[t].second + 1;
    }
    cout << '\n';

    long long osszes = 0;
    for (int t = 0; t < k; t++) {
        int hossz = szakaszok[t].second - szakaszok[t].first + 1;
        osszes += hossz;
        if (t > 0) cout << ' ';
        cout << hossz;
    }
    cout << '\n';

    cout << osszes << '\n';
    return 0;
}
