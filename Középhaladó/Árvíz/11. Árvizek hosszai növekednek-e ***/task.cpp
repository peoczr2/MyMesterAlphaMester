/*
Megoldás lényege:
A vízállásokból készültségi szint lesz: a 800 cm fölötti mérések legalább elsőfokú készültséget jelentenek.
Az árvizek ezek egymás utáni maximális sorozatai, amelyeket egyetlen balról jobbra haladó bejárással gyűjtünk ki a kezdő és záró indexükkel.
Az árvizek hossza záró - kezdő + 1; a hosszakat szomszédos páronként összevetve eldönthető, hogy szigorúan monoton növekvők-e.
Egyetlen árvíz esetén a feltétel triviálisan teljesül, így a válasz IGEN. Az időigény O(N), ami N ≤ 10 000 esetén az időlimit alatt van.
*/
/*
Hint 1: || Egy mérés akkor része árvíznek, ha vízállása meghaladja a 800 cm-t. Az árvizek ezek egymás utáni sorozatai. ||
Hint 2: || Egy bejárásban gyűjtsd ki minden árvíz kezdő és záró indexét. Az árvíz hossza a két index különbsége plusz egy. ||
Hint 3: || A szigorú monotonitás azt jelenti, hogy minden szomszédos hosszpárban az előző kisebb a következőnél. Ezt egyetlen végigmenéssel ellenőrizheted. ||
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

    // Az árvizek [kezdet, vége] párjai, 0-indexelve
    vector<pair<int, int>> arvizek;
    int i = 0;
    while (i < n) {
        if (szint(a[i]) == 0) {
            i++;
            continue;
        }
        int j = i;
        while (j + 1 < n && szint(a[j + 1]) > 0) j++;
        arvizek.push_back({i, j});
        i = j + 1;
    }

    int k = arvizek.size();
    cout << k << '\n';
    if (k == 0) return 0;

    auto hossz = [&](int t) { return arvizek[t].second - arvizek[t].first + 1; };

    for (int t = 0; t < k; t++) {
        if (t > 0) cout << ' ';
        cout << arvizek[t].first + 1 << ' ' << arvizek[t].second + 1;
    }
    cout << '\n';

    for (int t = 0; t < k; t++) {
        if (t > 0) cout << ' ';
        cout << hossz(t);
    }
    cout << '\n';

    // Szigorú monotonitás: minden szomszédos párban az előző hossz kisebb legyen
    bool szigoruan_novekvo = true;
    for (int t = 1; t < k; t++)
        if (hossz(t) <= hossz(t - 1)) szigoruan_novekvo = false;

    cout << (szigoruan_novekvo ? "IGEN" : "NEM") << '\n';
    return 0;
}
