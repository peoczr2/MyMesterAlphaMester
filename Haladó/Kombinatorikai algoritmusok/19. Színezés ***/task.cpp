/*
Megoldás lényege:
A sorozatban két szomszédos 1-es nem állhat, ezért egy pozíció szabadsága csak az előző bit értékétől függ. A ways(pos, prev) függvény azt adja meg, hányféleképpen lehet a pos-tól kezdődő részt kitölteni, ha az előző bit prev; ezt memoizálva számoljuk, az állapotok száma O(N). A teljes szám a ways(0, 0). A K-adik sorozatot elemenként építjük: ha az előző bit 1, a következő 0 kötelező; különben megnézzük, hány folytatás van 0-val, és ha K ennyinél nem nagyobb, 0-t írunk, egyébként K-ból levonjuk ezt a számot és 1-et írunk. Mivel a 0 az ábécében az 1 előtt áll, ez a lépés a lexikografikus K-adik sorozatot adja, az összes munka O(N).
*/
/*
Hint 1: || Az 1-esek nem állhatnak egymás mellett, ezért a következő bit lehetséges értékei az előző bittől függnek: ez DP-állapot, amelynek paraméterei a pozíció és az előző bit. ||
Hint 2: || Jelölje ways(pos, prev) a pos-tól kezdődő kitöltések számát, ha az előző bit prev: ha a pos bit 0, a folytatás ways(pos+1, 0), ha 1, akkor ways(pos+1, 1), de ez csak akkor lehetséges, ha prev = 0. Memoizálással az összes állapot kiszámolható. ||
Hint 3: || A K-adik sorozatot bitenként építsd: ha a 0-val kezdődő folytatások száma legalább K, a 0 következik, különben vond le K-ból ezt a számot és írj 1-et. Az 1 után mindig 0 jön. ||
*/
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ull K;
    cin >> N >> K;
    int L = N + 1;
    vector<array<ull, 2>> memo(L + 1);
    vector<array<char, 2>> vis(L + 1);

    function<ull(int, int)> ways = [&](int pos, int prev) -> ull {
        if (pos == L) return 1;
        if (vis[pos][prev]) return memo[pos][prev];
        vis[pos][prev] = 1;
        ull res = ways(pos + 1, 0);
        if (!prev) res += ways(pos + 1, 1);
        return memo[pos][prev] = res;
    };

    ull total = ways(0, 0);
    cout << total << '\n';

    vector<int> ans;
    int prev = 0;
    for (int pos = 0; pos < L; ++pos) {
        if (prev == 1) {
            ans.push_back(0);
            prev = 0;
            continue;
        }
        ull cnt0 = ways(pos + 1, 0);
        if (K <= cnt0) {
            ans.push_back(0);
            prev = 0;
        } else {
            K -= cnt0;
            ans.push_back(1);
            prev = 1;
        }
    }

    for (int i = 0; i < L; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
