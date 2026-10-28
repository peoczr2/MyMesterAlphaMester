/*
Megoldás lényege:
Egy kutya csak arra a szempontra nézve esik ki, amelyben az alsó ponthatár alatt maradt, a többi szempontban továbbra is értékelhető. Ezért szempontonként külön számoljuk, hány kutya éri el az adott szempont alsó ponthatárát. Ha ez legalább kettő, a szempont szerepel a kimenetben. Minden pontot egyszer vizsgálunk, így az időigény O(N·M), a memóriaigény O(M).
*/
/*
Hint 1: || Egy kutya egy szempontban akkor marad bent, ha ott eléri az alsó ponthatárt, függetlenül attól, hogy más szempontokban mit kapott. Szempontonként külön kell nézni a bent maradókat. ||
Hint 2: || Szempontonként tarts egy számlálót: a pontok beolvasása közben növeld, ha a pont nem kisebb a szempont alsó ponthatáránál. A végén a legalább 2-es számlálójú szempontok számát és sorszámait írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> mx(m), mn(m);
    for (int &x : mx) cin >> x;
    for (int &x : mn) cin >> x;

    vector<int> remain(m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            int p;
            cin >> p;
            if (p >= mn[j]) remain[j]++;
        }

    vector<int> res;
    for (int j = 0; j < m; j++)
        if (remain[j] >= 2) res.push_back(j + 1);

    cout << res.size();
    for (int x : res) cout << ' ' << x;
    cout << '\n';
    return 0;
}
