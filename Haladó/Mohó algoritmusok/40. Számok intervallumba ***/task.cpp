/*
Megoldás lényege:
Az összhossz a legnagyobb és a legkisebb szám különbsége, mínusz a levágott hézagok összege, ezért a rendezett számok közötti hézagok közül a legnagyobb összegű vágáshalmazt keressük. Két vágás nem lehet egymás mellett (különben egyelemű csoport keletkezne), és az első, illetve az utolsó hézag sem vágható, mert a szélső csoportoknak is legalább két szám kell. Ezt dinamikus programozással oldjuk meg: dp[i] = max(dp[i-1], hézag[i] + dp[i-2]), a vágásokat pedig a táblázatból fejtjük vissza. Az időigény a rendezés miatt O(N log N).
*/
/*
Hint 1: || Az összhossz az első és utolsó szám különbségéből indul, és minden kivágott hézaggal csökken. ||
Hint 2: || Olyan hézagokat válassz, amelyek között legalább egy szám marad. ||
Hint 3: || Legyen dp[i] a legnagyobb összeg, amelyet az 1..i sorszámú hézagok közül választva érhetünk el: dp[i] = max(dp[i-1], hézag[i] + dp[i-2]). ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a.begin(), a.end());

    if (n == 2) {
        cout << a[1] - a[0] << '\n' << a[0] << ' ' << a[1] << '\n';
        return 0;
    }

    int m = n - 1;
    vector<long long> gap(m, 0);
    for (int i = 0; i < m; ++i) gap[i] = a[i + 1] - a[i];

    vector<long long> dp(m, 0);
    vector<int> choose(m, 0);
    for (int i = 1; i <= m - 2; ++i) {
        long long take = gap[i] + (i >= 2 ? dp[i - 2] : 0);
        long long skip = dp[i - 1];
        if (take > skip) {
            dp[i] = take;
            choose[i] = 1;
        } else {
            dp[i] = skip;
        }
    }

    vector<int> cuts;
    for (int i = m - 2; i >= 1;) {
        long long take = gap[i] + (i >= 2 ? dp[i - 2] : 0);
        long long skip = dp[i - 1];
        if (take >= skip) {
            cuts.push_back(i);
            i -= 2;
        } else {
            --i;
        }
    }
    sort(cuts.begin(), cuts.end());

    long long total = a.back() - a.front();
    for (int c : cuts) total -= gap[c];

    cout << total << '\n';
    int start = 0;
    for (int c : cuts) {
        cout << a[start] << ' ' << a[c] << '\n';
        start = c + 1;
    }
    cout << a[start] << ' ' << a.back() << '\n';
    return 0;
}