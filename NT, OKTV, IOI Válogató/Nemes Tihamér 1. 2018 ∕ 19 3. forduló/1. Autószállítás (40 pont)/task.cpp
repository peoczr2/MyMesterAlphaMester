/*
Megoldás lényege:
Csúszó ablakkal (két mutatóval) keressük a legrövidebb szakaszt. A jobb mutató r minden napon egyet lép előre, és a [l..r] szakasz autóinak számát (sum) tartjuk nyilván. Ha sum eléri H-t, a bal mutatót l addig léptetjük jobbra, amíg az összeg H alá nem esne, így minden r-hez a legrövidebb, r-ben végződő, H-t elérő szakasz adódik. A napi darabszámok pozitívak, ezért a rövidebb szakasz mindig jobb; egyenlő hossznál a korábbi kezdést tartjuk meg. Mindkét mutató csak előre halad, így az időigény O(N).
*/
/*
Hint 1: || Minden jobb végponthoz (r) keresd azt a legnagyobb bal végpontot (l), amelyre a [l..r] szakasz összege még legalább H: így az r-hez tartozó legrövidebb jó szakaszt kapod. ||
Hint 2: || Az összeget egy változóban tartsd: új nap érkezésekor adj hozzá a napi darabszámot, majd a bal szélről vonj le, amíg az összeg a levonás után is legalább H marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, h;
    cin >> n >> h;
    vector<int> d(n + 1);
    for (int i = 1; i <= n; ++i) cin >> d[i];

    int l = 1;
    long long sum = 0;
    int bestL = -1, bestR = -1, bestLen = INT_MAX;
    for (int r = 1; r <= n; ++r) {
        sum += d[r];
        while (l <= r && sum - d[l] >= h) {
            sum -= d[l++];
        }
        if (sum >= h) {
            int len = r - l + 1;
            if (len < bestLen || (len == bestLen && l < bestL)) {
                bestLen = len;
                bestL = l;
                bestR = r;
            }
        }
    }

    if (bestL == -1) cout << -1 << '\n';
    else cout << bestL << ' ' << bestR << '\n';
    return 0;
}