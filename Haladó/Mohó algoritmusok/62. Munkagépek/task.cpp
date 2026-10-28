/*
Megoldás lényege:
Egy gép naponta egy munkát végez, így d napig legfeljebb G*d munka fér el. Ha pref(d) a d-ig esedékes munkák száma, akkor minden d-re G >= ceil(pref(d)/d) szükséges, és ezek a korlátok együtt elegendők is. A válasz ezért a korlátok maximuma. Az időigény O(N + H), ahol H a legnagyobb határidő, mert a határidők gyakorisági tömbjéből egy bejárással megkapjuk az összes prefixösszeget.
*/
/*
Hint 1: || Írd fel a „d napig hány munka készülhet el” kapacitáskorlátot. ||
Hint 2: || A szükséges gépszámot minden d-re alsó korlát adja: ceil(prefix(d)/d). ||
Hint 3: || A válasz a korlátok maximuma. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> h(N);
    int maxH = 0;
    for (int i = 0; i < N; ++i) {
        cin >> h[i];
        maxH = max(maxH, h[i]);
    }

    vector<int> cnt(maxH + 1, 0);
    for (int x : h) cnt[x]++;

    long long pref = 0;
    long long ans = 0;
    for (int d = 1; d <= maxH; ++d) {
        pref += cnt[d];
        ans = max(ans, (pref + d - 1) / d);
    }

    cout << ans << '\n';
    return 0;
}
