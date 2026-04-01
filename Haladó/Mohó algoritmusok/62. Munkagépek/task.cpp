/*
Feladat: Egynapos munkák adott határidőkkel, mindet határidőre kell teljesíteni. Egy munkagép naponta egy munkát végez. A minimális gépszámot kell meghatározni.
Ötlet: d napig legfeljebb G*d munkát tud elvégezni G gép. Ha prefix(d) a d-ig esedékes munkák száma, akkor szükséges G >= ceil(prefix(d)/d) minden d-re. A minimális G ezért ezen értékek maximuma.
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
