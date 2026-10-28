/*
Megoldás lényege:
Minden madár territóriuma egy négyzet, amelynek bal és jobb széle X-R, illetve X+R, alsó és felső széle Y-R, illetve Y+R.
Egy madár territóriuma akkor része egy másik madárénak, ha mindkét tengelyen az egész intervallum benne van a másik
intervallumában, vagyis elég a sarokkoordinátákat összehasonlítani. Minden madárra megnézzük az összes többi madarat,
és ha van olyan, amelynek négyzete tartalmazza, a madarat számoljuk. Az időigény O(M²), ami M ≤ 1000 mellett 10^6 művelet.
*/
/*
Hint 1: || Két négyzet akkor van egymásban, ha mindkét tengelyen az egyik intervallum része a másiknak. Ezt a feltételt kell minden madárpárra vizsgálni. ||
Hint 2: || Minden madárhoz tárold a négyzet négy határát: bal = X-R, jobb = X+R, alsó = Y-R, felső = Y+R. Az i madár akkor számít, ha van olyan j ≠ i, amelyre bal_j ≤ bal_i, jobb_i ≤ jobb_j, alsó_j ≤ alsó_i és felső_i ≤ felső_j. ||
Hint 3: || Két egymásba ágyazott ciklussal (a külső az i, a belső a j) O(M²)-ben kiszámolható. A j = i esetet ki kell hagyni, és elég az első olyan j-nél megállni, amelyre a feltétel teljesül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    vector<int> left(m), right(m), bottom(m), top(m);
    for (int i = 0; i < m; i++) {
        int x, y, r;
        cin >> x >> y >> r;
        left[i] = x - r;
        right[i] = x + r;
        bottom[i] = y - r;
        top[i] = y + r;
    }
    int ans = 0;
    for (int i = 0; i < m; i++) {
        bool inside = false;
        for (int j = 0; j < m && !inside; j++) {
            if (j == i) continue;
            if (left[j] <= left[i] && right[i] <= right[j] &&
                bottom[j] <= bottom[i] && top[i] <= top[j]) {
                inside = true;
            }
        }
        if (inside) ans++;
    }
    cout << ans << "\n";
    return 0;
}
