/*
Feladat: N napra adott napi kapacitások és M darab 1 órás munka határidővel. Maximum hány munka végezhető el határidőre?
Ötlet: Ha d napig összesen C[d] munkaóra áll rendelkezésre (prefix összeg), akkor legfeljebb C[d] darab, d-ig lejáró munka teljesíthető. A határidőket növekvőre rendezzük, és mohón elfogadunk egy munkát, ha az aktuális elfogadott darabszám +1 még belefér a megfelelő prefix-kapacitásba.
Hint 1: || Prefix-korlát: d-ig legfeljebb az addigi napi kapacitások összege teljesíthető. ||
Hint 2: || Határidő szerint rendezve minden munkáról azonnal eldönthető, hogy még befér-e. ||
Hint 3: || Ez a döntés optimális, mert csak darabszámot maximalizálunk. ||
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
