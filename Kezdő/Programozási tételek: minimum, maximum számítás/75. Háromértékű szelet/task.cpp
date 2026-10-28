/*
Megoldás lényege: keressük a leghosszabb olyan folytonos részt, amelyben legfeljebb három különböző érték van.
Csúszóablakot használunk: a jobb mutatót egyesével léptetjük, és egy map-ben számoljuk, hogy az ablakban melyik értékből hány darab van.
Ha a különböző értékek száma négyre nőne, a bal mutatót addig léptetjük előre (a számlálókat csökkentve), amíg újra legfeljebb három érték marad.
Minden elemet legfeljebb kétszer érintünk, a map-ben legfeljebb négy kulcs lehet, így az időigény O(N log 4), gyakorlatilag O(N).
*/
/*
Hint 1: || Ez csúszóablak-feladat: a jobb végponttal haladj a sorozaton, és mindig tartsd az ablakot úgy, hogy benne legfeljebb három különböző szám legyen. ||
Hint 2: || Tartsd nyilván az ablakban lévő számok darabszámát egy map<int,int>-ben. Ha a map mérete négy lesz, a bal oldali elemeket vond ki az ablakból, amíg újra csak három különböző érték nem marad. ||
Hint 3: || Ha egy szám darabszáma nullára csökken, töröld a kulcsát a map-ből, különben rossz lesz a méret. Az ablak hossza minden lépés után r - l + 1, ezzel frissítsd a legjobb eredményt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> s(n);
    for (auto &x : s) cin >> x;

    map<int, int> cnt;
    int l = 0, best = 0;
    for (int r = 0; r < n; r++) {
        cnt[s[r]]++;
        while ((int)cnt.size() > 3) {
            if (--cnt[s[l]] == 0) cnt.erase(s[l]);
            l++;
        }
        best = max(best, r - l + 1);
    }
    cout << best << "\n";
    return 0;
}
