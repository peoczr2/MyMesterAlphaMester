/*
Megoldás lényege:
Ha a végső fok X, akkor az i. hús alatt X - A_i alkalommal kell égnie a gáznak. Egy hús a t-edik lépésben történő kikapcsolással pontosan t-1 növekedést kap, és egy lépésben csak egy gázt kezelhetünk, így a húsoknak különböző lépésekben kell kikapcsolódniuk. A legnagyobb j húsra (ezek mind legfeljebb A_j-hez tartozó X - A_j értéket kapnak) j különböző lépés kell, ezért j <= X - A_j + 1, azaz X >= A_j + j - 1. Ez a feltétel elegendő is, ezért a válasz a rendezett sorozat A_j + (j-1) értékeinek maximuma. A megoldás rendezéssel O(N log N) időben fut.
*/
/*
Hint 1: || Gondolkodj visszafelé: ha a végső fok X, akkor az i. hús alatt X - A_i alkalommal kell égnie a gáznak. Egy hús a t-edik lépésben történő kikapcsolással pontosan t-1 növekedést kap. ||
Hint 2: || Egy lépésben csak egy gázt kapcsolhatunk, ezért a húsok kikapcsolási lépései különbözőek kell legyenek. Rendezd a húsokat csökkenő sorrendbe: a j-edik legnagyobb húsra A_j + (j-1) alsó korlát a végső fokra, és a válasz ezek maximuma. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    sort(a.begin(), a.end(), greater<long long>());

    long long ans = 0;
    for (int j = 0; j < n; j++)
        ans = max(ans, a[j] + j);

    cout << ans << "\n";
    return 0;
}
