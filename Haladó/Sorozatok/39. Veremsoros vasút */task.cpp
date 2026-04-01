/*
Megoldas lenyege:
Az egyik segélysínre a kocsikat olyan sorrendben érdemes gyűjteni, hogy az ott
lévő sorozat nemcsökkenő legyen, a másikra pedig úgy, hogy az ottani sorrend
nemnövekvő legyen. Ha ez a két subsequence felbontható, akkor a két sínről a
megfelelő sorrendben le tudjuk adni a kocsikat az A sínre. Mivel csak 1..4
értékek szerepelnek, egy kis dinamikus programmal nyomon követhető, hogy a két
szekvencia utolsó értékei mellett mely prefixelosztások lehetségesek.
*/
/*
Hint 1: || Gondolj úgy a két oldalsínre, mint két rész-sorozatra: az egyiknek növekvőnek, a másiknak csökkenőnek kell maradnia. ||
Hint 2: || Minden új kocsit vagy az első, vagy a második rész-sorozathoz rendelsz. ||
Hint 3: || A négyféle címke miatt elég az utolsó értékeket állapotként tárolni. ||
*/
#include <bits/stdc++.h>
using namespace std;

static bool canSort(const vector<int>& a) {
    bool dp[5][6] = {};
    dp[0][5] = true;

    for (int x : a) {
        bool nextDp[5][6] = {};
        for (int qLast = 0; qLast <= 4; ++qLast) {
            for (int sLast = 1; sLast <= 5; ++sLast) {
                if (!dp[qLast][sLast]) continue;
                if (x >= qLast) nextDp[x][sLast] = true;
                if (x <= sLast) nextDp[qLast][x] = true;
            }
        }
        memcpy(dp, nextDp, sizeof(dp));
    }

    for (int qLast = 0; qLast <= 4; ++qLast) {
        for (int sLast = 1; sLast <= 5; ++sLast) {
            if (dp[qLast][sLast]) return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    while (m--) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        cout << (canSort(a) ? "IGEN" : "NEM") << '\n';
    }
    return 0;
}
