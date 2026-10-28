/*
Megoldás lényege:
Legyen A azoknak a fogadóirodáknak a halmaza, ahol az első kimenetre fogadunk, B pedig ahol a másodikra; k = |A| + |B| a fogadások száma, és minden fogadás 1 eurót kerül. Az első kimenet esetén a nyereség (sum a_i, i az A-ban) - k, a másodiknál (sum b_i, i a B-ben) - k, a garantált nyereség a kettő minimuma.
Ha |A| = i és |B| = j, akkor a legjobb választás A-ba az a-k i legnagyobbja, B-be a b-k j legnagyobbja, mert a két oldal egymástól csak a darabszámokon keresztül függ. Ezért mindkét sorozatot csökkenő sorrendbe rendezzük és prefixösszegeket számolunk.
A maximumot bináris kereséssel keressük: egy V érték elérhető, ha van olyan (i, j), amelyre mindkét nyereség legalább V; ezt prefix-maximum tömbbel O(N) időben ellenőrizzük. Az odd-ok legfeljebb 4 tizedesjegyűek, ezért 10^-4 egységben egész számokkal számolunk, így nincs kerekítési hiba. Az időigény O(N log(összeg)).
*/
/*
Hint 1: || Egy fogadás mindig 1 eurót kerül, ezért a nyereség a nyerő fogadások visszakapott odd-jainak összegéből és a fogadások teljes számából adódik. Gondold végig, hogy adott darabszámú fogadásnál (i az első, j a második kimenetre) melyik irodákat érdemes választani. ||
Hint 2: || Rendezd az összes a_i-t és b_i-t csökkenő sorrendbe, és számold ki a prefixösszegeket: így bármely (i, j) párra O(1) alatt megkapod mindkét nyereséget. A garantált nyereség maximumát bináris kereséssel keresd, és a számokat 10^-4-es egységekben, egész számokkal kezeld. ||
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const ll S = 10000; // 1 euró értéke a 10^-4-es egész skálán

    int n;
    cin >> n;
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) {
        double x, y;
        cin >> x >> y;
        a[i] = llround(x * S);
        b[i] = llround(y * S);
    }
    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());

    vector<ll> SA(n + 1, 0), SB(n + 1, 0);
    for (int i = 0; i < n; i++) {
        SA[i + 1] = SA[i] + a[i];
        SB[i + 1] = SB[i] + b[i];
    }

    vector<ll> pm(n + 1);

    // Igaz, ha van olyan (i, j), amelyre mindkét kimenetelnél a nyereség legalább V.
    auto feasible = [&](ll V) -> bool {
        // SB[j] - (i+j)S >= V  <=>  SB[j] - jS - V >= iS
        ll best = LLONG_MIN;
        for (int j = 0; j <= n; j++) {
            best = max(best, SB[j] - (ll)j * S - V);
            pm[j] = best;
        }
        for (int i = 0; i <= n; i++) {
            // SA[i] - (i+j)S >= V  <=>  jS <= SA[i] - iS - V
            ll r = SA[i] - (ll)i * S - V;
            if (r < 0) continue;
            ll f = min<ll>(n, r / S);
            if (pm[f] >= (ll)i * S) return true;
        }
        return false;
    };

    ll lo = 0;               // elérhető (nincs fogadás)
    ll hi = SA[n] + 1;       // biztosan nem elérhető
    while (hi - lo > 1) {
        ll mid = lo + (hi - lo) / 2;
        if (feasible(mid)) lo = mid;
        else hi = mid;
    }

    cout << lo / S << '.' << setw(4) << setfill('0') << lo % S << '\n';
    return 0;
}
