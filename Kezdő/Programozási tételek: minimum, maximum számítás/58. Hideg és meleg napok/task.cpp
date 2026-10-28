/*
Megoldás lényege:
Minden napot besorolunk: hideg (-1), meleg (+1), vagy egyik sem (0). Az első és az utolsó nap mindig 0. Egy intervallum pontosan akkor kedvező, ha a két szélén hideg vagy meleg nap áll, és a benne lévő -1 és +1 értékek összege 0. Ezt egyenlegekkel (prefixösszegekkel) vizsgáljuk: ha P[i] az első i nap összege, akkor az [l..r] összeg P[r] - P[l-1], tehát akkor 0, ha P[r] = P[l-1]. Bejárás közben egy gyakorisági tömbben számoljuk, hogy az eddigi speciális kezdőnapok közül melyik egyenlegértékhez hány tartozik, és minden hideg vagy meleg napnál ezt a számot hozzáadjuk a válaszhoz. Az időigény O(N).
*/
/*
Hint 1: || Az első és az utolsó nap sosem hideg és sosem meleg. Minden más napra a két szomszédjával való összehasonlítás dönti el a típusát, ezt érdemes előre kiszámolni. ||
Hint 2: || Rendeld a hideg napokhoz -1-et, a meleg napokhoz +1-et, a többihez 0-t. Egy intervallum akkor jó, ha az összege 0, és a két szélén speciális nap áll. ||
Hint 3: || Ha P[i] az első i nap összege, akkor az [l..r] összeg P[r] - P[l-1]. Számold, hogy az eddig látott kezdőnapok közül melyik P[l-1] értékből hány van, és r-nél ezt a gyakoriságot add a válaszhoz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> h(n + 2, 0);
    for (int i = 1; i <= n; i++) cin >> h[i];

    // tipus[i]: +1 meleg nap, -1 hideg nap, 0 egyik sem (az első és az utolsó nap is 0)
    vector<int> tipus(n + 2, 0);
    for (int i = 2; i < n; i++) {
        if (h[i] > h[i - 1] && h[i] > h[i + 1]) tipus[i] = 1;
        else if (h[i] < h[i - 1] && h[i] < h[i + 1]) tipus[i] = -1;
    }

    // egyenleg: a speciális napok (meleg +1, hideg -1) összege az eddigi napokon
    // cnt[x + OFFSET]: hány olyan l kezdőnap volt eddig, amelyre az l-1-ig tartó egyenleg x
    const int OFFSET = n + 1;
    vector<long long> cnt(2 * n + 3, 0);
    long long ans = 0;
    int egyenleg = 0;
    for (int i = 1; i <= n; i++) {
        if (tipus[i] == 0) continue;
        int uj = egyenleg + tipus[i];
        ans += cnt[uj + OFFSET];   // [l..i] intervallumok, ahol l < i és az egyenleg egyezik
        cnt[egyenleg + OFFSET]++;  // i mint lehetséges kezdőnap (l = i)
        egyenleg = uj;
    }
    cout << ans << "\n";
    return 0;
}
