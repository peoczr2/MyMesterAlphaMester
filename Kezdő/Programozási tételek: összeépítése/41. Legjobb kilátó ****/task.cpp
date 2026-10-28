/*
Megoldás lényege:
Minden szárazföldi (magasság > 0) pontból megszámoljuk, hány mérési pont látszik, a két irányt külön-külön véve, majd összeadjuk.
Jobbra haladva a j pont akkor látszik az i-edikről, ha a (h_j - h_i)/(j - i) meredekség nem kisebb, mint az i és j közötti k pontokhoz tartozó (h_k - h_i)/(k - i) meredekségek maximuma.
Balra ugyanez a feltétel, a távolságot i - j értelemben véve.
A maximumot egy futó értékben tartjuk, a törteket szorzással, egész számokkal hasonlítjuk, így nincs lebegőpontos pontatlanság.
Egy megfigyelőre O(N), az összes szárazföldi pontra O(N^2), ami N = 10000 esetén is belefér az időlimitbe.
A legtöbb pontot látó szárazföldi pont sorszámát írjuk ki, döntetlennél a kisebb sorszámút; ha nincs szárazföld, 0 a válasz.
*/
/*
Hint 1: || Két pont akkor látja egymást, ha a közéjük húzott egyenes a köztes pontok mindegyike fölött halad. Ezt érdemes meredekségekkel ellenőrizni, nem magasságokkal. ||
Hint 2: || Egy i-ből jobbra lévő j pontot akkor látsz, ha (h_j - h_i)/(j - i) nem kisebb, mint az i és j közötti k pontok (h_k - h_i)/(k - i) meredekségeinek a maximuma. Ezt a maximumot elég futva tartani. ||
Hint 3: || A törtek összehasonlításához szorozz keresztbe egész számokkal, így nem kell lebegőpontos számokat használni. Balra ugyanez a logika érvényes, csak a távolság i - j. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> h(n);
    for (auto &x : h) cin >> x;

    // Hány mérési pont látszik az i-edik pontról; step = +1 jobbra, -1 balra.
    auto visible = [&](int i, int step) {
        int cnt = 0;
        bool first = true;
        long long bn = 0, bd = 1;   // a futó maximum meredekség: bn / bd, bd > 0
        for (int j = i + step; j >= 0 && j < n; j += step) {
            long long num = h[j] - h[i];
            long long den = (long long)(j - i) * step;   // mindig pozitív
            if (first || num * bd >= bn * den) cnt++;
            if (first || num * bd > bn * den) {
                bn = num;
                bd = den;
            }
            first = false;
        }
        return cnt;
    };

    int best = 0, bestCnt = -1;
    for (int i = 0; i < n; i++) {
        if (h[i] <= 0) continue;   // csak szárazföldi pont lehet megfigyelő
        int cnt = visible(i, 1) + visible(i, -1);
        if (cnt > bestCnt) {
            bestCnt = cnt;
            best = i + 1;
        }
    }
    cout << best << "\n";
    return 0;
}
