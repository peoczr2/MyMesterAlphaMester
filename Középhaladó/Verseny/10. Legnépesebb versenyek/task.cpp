/*
Megoldás lényege:
Minden versenyre megszámoljuk, hányan értek el legalább annyi pontot, mint az adott versenyhez tartozó minimális pontszám. Az egyes versenyek számlálóit egyetlen beolvasás közben növeljük, mert minden tanuló pontját csak egyszer kell megnézni. A legnagyobb számláló adja a legnépesebb versenyek értékét, és az ezt elérő versenyek sorszámait növekvő sorrendben írjuk ki. Az időigény O(N·M) a bemenet méretével arányosan, ami a korlátok mellett elhanyagolható.
*/
/*
Hint 1: || Minden versenyhez külön számold meg, hány résztvevő érte el az adott verseny minimális pontszámát. Ehhez a versenyhez tartozó Mini értéket használd, ne egy közöset. ||
Hint 2: || Tárolj egy számlálót versenyenként: beolvasás közben, ha a pont legalább a verseny Mini értéke, növeld a számlálót. Utána keresd meg a számlálók maximumát, és írd ki a maximumot elérő versenyek sorszámát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> mini(m);
    for (int i = 0; i < m; i++) {
        cin >> mini[i];
    }

    vector<int> cnt(m, 0);
    for (int i = 0; i < m; i++) {
        int ind;
        cin >> ind;
        for (int j = 0; j < ind; j++) {
            int s, p;
            cin >> s >> p;
            if (p >= mini[i]) {
                cnt[i]++;
            }
        }
    }

    int best = *max_element(cnt.begin(), cnt.end());
    vector<int> ans;
    for (int i = 0; i < m; i++) {
        if (cnt[i] == best) {
            ans.push_back(i + 1);
        }
    }

    cout << ans.size();
    for (int x : ans) {
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
