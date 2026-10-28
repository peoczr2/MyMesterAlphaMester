/*
Megoldás lényege:
Minden terméknél a kötelező MD_i darabot mindenképpen el kell vinni, ezért ezeknek a súlyát és bevételét először levonjuk: ha a kötelező összsúly már meghaladja a K kapacitást, nincs megoldás, és -1 a válasz. A maradék kapacitásra a termékek további (M_i - MD_i) darabja egy hátizsák-feladatot ad, ahol minden darab külön tárgy, amelynek súlya T_i és értéke A_i.
Ezt az egyszerű 0/1 hátizsák-DP-vel oldjuk meg: dp[c] a c kapacitásba legfeljebb beférő legnagyobb bevétel, és minden darabot c szerint csökkenő sorrendben, egyszer-egyszer hozzáadunk. A végső válasz a kötelező bevétel plusz dp[K - kötelező súly].
Az időigény O(D · K), ahol D ≤ 2000 a darabok száma, így 2 · 10^6 művelet adódik.
*/
/*
Hint 1: || A kötelező darabszámokat mindenképpen elviszed, ezért ezek súlyát vond le a kapacitásból, bevételét pedig előre jóváírhatod. Ha a kötelező tömeg már nagyobb a kapacitásnál, a válasz -1. ||
Hint 2: || A maradék kapacitásra a többi (M_i - MD_i) darab már sima hátizsák-feladat: minden darab egy külön tárgy, amelynek a súlya T_i, az értéke A_i. Mivel legfeljebb 20 darab van terméktípusonként, a darabokat egyesével vedd végig. ||
Hint 3: || Egy dp tömbben dp[c] legyen a legnagyobb bevétel, amit c kg-ig el lehet érni, kezdetben minden 0. Minden darabnál a kapacitásokat csökkenő sorrendben frissítsd, így minden darabot legfeljebb egyszer használsz. A végén a válasz a kötelező bevétel plusz dp[K - kötelező tömeg]. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    long long baseWeight = 0, baseValue = 0;
    vector<int> dp(k + 1, 0);

    for (int i = 0; i < n; i++) {
        int t, a, m, md;
        cin >> t >> a >> m >> md;

        baseWeight += (long long)md * t;
        baseValue += (long long)md * a;

        // A még nem kötelező darabok egyesével, mint 0/1 tárgyak.
        int extra = m - md;
        for (int u = 0; u < extra; u++) {
            for (int c = k; c >= t; c--) {
                dp[c] = max(dp[c], dp[c - t] + a);
            }
        }
    }

    if (baseWeight > k) {
        cout << -1 << "\n";
        return 0;
    }

    cout << baseValue + dp[k - baseWeight] << "\n";
    return 0;
}
