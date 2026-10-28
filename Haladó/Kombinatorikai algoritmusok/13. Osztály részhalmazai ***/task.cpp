/*
   Osztály részhalmazai: az N bites számok növekvő sorrendje. A K elemű
   csoport M-edik elemét a legnagyobb bit felől haladva, binomiális
   számolással állítjuk elő. A már eldöntött felső bitek mellett a bit 0
   értékű csoportok mind kisebbek a bit 1 értékűeknél, számuk pedig C(bit, K),
   mert a K elemet a bit alatti bitekből választjuk. Ezért M <= C(bit, K)
   esetén a bit nincs a csoportban; különben benne van, M-ből levonjuk a
   C(bit, K) értéket, és K-t csökkentjük. A binomiális táblázat (N <= 40)
   egyszer épül fel O(N^2) időben, egy lekérdezés pedig O(N) időben fut.
*/
/*
Hint 1: || A csoportok sorrendje ugyanaz, mint a bináris számoké: a legnagyobb helyiértékű bit (az N-1-es tanuló) dönt elsőnek. Számold meg, hány K tagú csoport nincs benne a legnagyobb sorszámú tanulóban, és ez alapján döntsd el, hogy benne van-e. ||
Hint 2: || Ha a tanuló nincs a csoportban, akkor a K tagot a tőle kisebb sorszámú tanulókból kell választani: ez C(bit, K) lehetőség, ahol C a binomiális együttható. ||
Hint 3: || Építs Pascal-háromszöget a binomiális együtthatókhoz (40-ig az ull típus elég). Bitenként a legnagyobbtól haladj: ha M nagyobb C(bit, K)-nál, a bit benne van a csoportban, M-ből vond le C(bit, K)-t, és K-t csökkentsd; különben a bit kimarad. ||
*/
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
static ull C[41][41];

vector<int> unrankSubset(int N, int K, ull M) {
    vector<int> ans;
    for (int bit = N - 1; bit >= 0 && K > 0; --bit) {
        ull cnt = C[bit][K];
        if (M > cnt) {
            ans.push_back(bit);
            M -= cnt;
            --K;
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int n = 0; n <= 40; ++n) {
        C[n][0] = C[n][n] = 1;
        for (int k = 1; k < n; ++k) C[n][k] = C[n - 1][k - 1] + C[n - 1][k];
    }

    int N, K, Q;
    cin >> N >> K >> Q;
    while (Q--) {
        ull M;
        cin >> M;
        vector<int> ans = unrankSubset(N, K, M);
        for (int i = 0; i < (int)ans.size(); ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}