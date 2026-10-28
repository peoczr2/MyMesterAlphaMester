/*
Megoldás lényege:
Ha d napig összesen C[d] munkaóra áll rendelkezésre (prefixösszeg), akkor a d-ig lejáró munkákból legfeljebb C[d] teljesíthető. A határidőket növekvő sorrendben dolgozzuk fel, és egy munkát akkor fogadunk el, ha az eddig elfogadott munkák számánál eggyel nagyobb szám még belefér a munka határidejéig tartó prefix-kapacitásba. Mivel a korábban elfogadott munkák határideje nem nagyobb, elegendő az aktuális határidőt ellenőrizni. A mohó döntés optimális, mert a feladat a párosítások matroidjának esete. Az időigény O(N + M log M).
*/
/*
Hint 1: || Prefix-korlát: d-ig legfeljebb az addigi napi kapacitások összege teljesíthető. ||
Hint 2: || Határidő szerint rendezve minden munkáról azonnal eldönthető, hogy még befér-e. ||
Hint 3: || Ha az elfogadott darabszám + 1 nem fér be a munka határidejéig tartó kapacitásba, a munkát kihagyod. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<long long> pref(N + 1, 0);
    for (int d = 1; d <= N; ++d) {
        long long x;
        cin >> x;
        pref[d] = pref[d - 1] + x;
    }

    vector<int> dl(M);
    for (int i = 0; i < M; ++i) cin >> dl[i];
    sort(dl.begin(), dl.end());

    long long done = 0;
    for (int d : dl) {
        if (done + 1 <= pref[d]) ++done;
    }

    cout << done << '\n';
    return 0;
}
