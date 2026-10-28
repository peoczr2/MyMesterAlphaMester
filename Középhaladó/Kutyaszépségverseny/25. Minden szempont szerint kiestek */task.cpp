/*
Megoldás lényege:
Egy kutya minden szempont szerint kiesett, ha minden szempontban a pontszáma kisebb az adott szempont alsó határánál. Soronként ezt ellenőrizzük, és a megfelelő kutyák sorszámát (1-től számozva) a bejárás sorrendjében, vagyis növekvő sorrendben gyűjtjük. Először a darabszám, majd a sorszámok kerülnek egy sorba. Az időigény O(N·M).
*/
/*
Hint 1: || Egy kutyát akkor veszünk fel a válaszba, ha egyetlen szempontban sem éri el az alsó határt, vagyis minden szempontra külön ellenőrizni kell a pontját. ||
Hint 2: || Soronként haladj, a sorszámot a sor indexéből kapod (+1), a kiírásnál a darabszám és a sorszámok ugyanabban a sorban szerepelnek, szóközzel elválasztva. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> maxPont(m), minPont(m);
    for (int &x : maxPont) cin >> x;
    for (int &x : minPont) cin >> x;

    vector<int> kiesettek;
    for (int i = 0; i < n; i++) {
        bool mindenKiesett = true;
        for (int j = 0; j < m; j++) {
            int p;
            cin >> p;
            if (p >= minPont[j]) mindenKiesett = false;
        }
        if (mindenKiesett) kiesettek.push_back(i + 1);
    }

    cout << kiesettek.size();
    for (int x : kiesettek) cout << ' ' << x;
    cout << '\n';
    return 0;
}
