/*
Megoldás lényege:
Mivel minden sziget lakosainak száma pozitív, a jobb végpont növelésével egy szakasz összege szigorúan nő, ezért kétmutatós (csúszóablakos) bejárással egyetlen menetben megtalálható a megoldás. A jobb szélt szigetről szigetre léptetjük, és ha az összeg K fölé nő, a bal szélt addig léptetjük előre, amíg az összeg nem lesz legfeljebb K. Az első olyan jobb szél, ahol az összeg pontosan K, egyben a legkisebb kezdő sorszámú megoldás is, mert két érvényes szakasz közül a korábban végződő kezdete is korábbi (pozitív elemek miatt). Ha nincs ilyen szakasz, a válasz -1. Az időigény O(N), mert minden sziget legfeljebb egyszer kerül be és ki az ablakból.
*/
/*
Hint 1: || Mivel az elemek pozitívak, egy szakasz összege csak a végpontjai kiterjesztésével nő, így nem kell minden szakaszt végigpróbálni, elég egy léptetett ablak. ||
Hint 2: || Tartsd az ablak bal (l) és jobb (r) szélét, valamint az összeget; minden r-léptetés után a bal szélt léptesd, amíg az összeg legfeljebb K; ha ekkor pontosan K, az ablak a keresett szakasz, mert az első találat adja a legkisebb kezdő sorszámot. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    int l = 1;
    long long sum = 0;
    int bestL = -1, bestR = -1;
    for (int r = 1; r <= n; ++r) {
        sum += a[r];
        while (l <= r && sum > k) sum -= a[l++];
        if (sum == k) {
            bestL = l;
            bestR = r;
            break;
        }
    }

    if (bestL == -1) cout << -1 << '\n';
    else cout << bestL << ' ' << bestR << '\n';
    return 0;
}