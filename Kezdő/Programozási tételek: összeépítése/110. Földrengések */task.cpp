/*
Megoldás lényege:
Az időszak első napja csak olyan nap lehet, amelyen volt földrengés, és az időszaknak az N. napon belül kell maradnia. A földrengések napsorszámai monoton növekvő sorozatot alkotnak, így minden jelölt kezdőnapra az [s, s+K-1] intervallumba eső földrengések száma két bináris kereséssel gyorsan megkapható. A jelöltek növekvő sorrendben érkeznek, ezért döntetlen esetén az első, legkisebb kezdőnap marad meg. Az időigény O(M log M).
*/
/*
Hint 1: || Az időszak kezdőnapja csak olyan nap lehet, amelyen volt földrengés, és az időszak nem nyúlhat az N. nap után. Elég ezeket a napokat kipróbálni kezdőnapnak. ||
Hint 2: || A földrengések napjai rendezett sorozatot alkotnak, ezért egy [s, s+K-1] intervallumba eső földrengések számát két bináris kereséssel (alsó és felső határ) meg lehet kapni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> f(m);
    for (int &x : f) cin >> x;

    int bestStart = -1;
    int bestCount = -1;
    for (int i = 0; i < m; ++i) {
        int start = f[i];
        int end = start + k - 1;
        if (end > n) continue;

        int count = upper_bound(f.begin(), f.end(), end) - lower_bound(f.begin(), f.end(), start);
        if (count > bestCount) {
            bestCount = count;
            bestStart = start;
        }
    }

    cout << bestStart << '\n';
    return 0;
}
