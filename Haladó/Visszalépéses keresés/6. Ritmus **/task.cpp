/*
Megoldás lényege: minden verssort dinamikus programozással bontunk fel ismert ritmusminták egymás utáni
illesztésére. A dp[i] azt jelzi, hogy a sor első i karaktere felbontható-e; ha dp[i] igaz, és egy minta
pontosan az i-edik pozíciótól illeszkedik, akkor a minta hosszával későbbi pozíció is elérhető. Az
elágazásokat eltároljuk, így a sor végétől visszafelé követve kapjuk a mintasorozatot. Egy sorra az
időigény O(L · n · 10), ahol L a sor hossza és n a minták száma.
*/
/*
Hint 1: || Dinamikus programozással: dp[i] legyen igaz, ha a sor első i karaktere felbontható ismert minták egymásutánjára (dp[0] igaz). ||
Hint 2: || Ha dp[i] igaz, és a j-edik minta pontosan az i-edik pozíciótól illeszkedik, akkor dp[i + a minta hossza] is igaz; a végétől visszafelé követve az eltárolt elágazásokkal kapod meg a mintasorozatot. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> minta(n + 1);
    for (int i = 1; i <= n; ++i) cin >> minta[i];
    int m;
    cin >> m;
    while (m--) {
        string sor;
        cin >> sor;
        int L = sor.size();
        vector<int> dp(L + 1, -1), prv(L + 1, -1);
        vector<int> pat(L + 1, -1);
        dp[0] = 0;
        for (int i = 0; i < L; ++i) if (dp[i] != -1) {
            for (int j = 1; j <= n; ++j) {
                int len = minta[j].size();
                if (i + len <= L && sor.compare(i, len, minta[j]) == 0) {
                    if (dp[i + len] == -1) {
                        dp[i + len] = dp[i] + 1;
                        prv[i + len] = i;
                        pat[i + len] = j;
                    }
                }
            }
        }
        if (dp[L] == -1) {
            cout << -1 << '\n';
            continue;
        }
        vector<int> sorozat;
        for (int i = L; i > 0; i = prv[i]) sorozat.push_back(pat[i]);
        reverse(sorozat.begin(), sorozat.end());
        cout << sorozat.size();
        for (int x : sorozat) cout << ' ' << x;
        cout << '\n';
    }
    return 0;
}