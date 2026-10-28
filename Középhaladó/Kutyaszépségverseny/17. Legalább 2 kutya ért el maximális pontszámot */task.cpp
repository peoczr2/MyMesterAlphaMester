/*
Megoldás lényege:
Egy szempont akkor kerül a kimenetbe, ha legalább két kutya pontosan a szempont maximumát kapta. Az alsó ponthatár itt nem számít, mert a maximumot elérő pont mindig eléri a ponthatárt is, így a kiesési szabály nem változtatja a számlálást. Ezért a pontok beolvasása közben szempontonként egy számlálót növelünk, ha a pont egyenlő a szempont maximumával. A végén a legalább kettes számlálójú szempontok számát és sorszámait írjuk ki növekvő sorrendben. Az időigény O(N·M), a memóriaigény O(M).
*/
/*
Hint 1: || Egy szempontnál nem kell foglalkozni a ponthatárral: aki eléri a szempont maximumát, az a ponthatárt is biztosan eléri. Elég megszámolni, hány kutya kapta meg a maximumot. ||
Hint 2: || Tarts M darab számlálót, és a pontok beolvasása közben növeld azt, ahol a pont megegyezik a szempont maximumával. A kiírásnál csak a legalább 2-es számlálójú szempontok kellenek. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> mx(m), mn(m);
    for (int &x : mx) cin >> x;
    for (int &x : mn) cin >> x;

    vector<int> cnt(m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            int p;
            cin >> p;
            if (p == mx[j]) cnt[j]++;
        }

    vector<int> res;
    for (int j = 0; j < m; j++)
        if (cnt[j] >= 2) res.push_back(j + 1);

    cout << res.size();
    for (int x : res) cout << ' ' << x;
    cout << '\n';
    return 0;
}
