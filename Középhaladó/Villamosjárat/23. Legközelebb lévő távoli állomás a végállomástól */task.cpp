/*
Megoldás lényege:
Az állomások távolságát az induló állomástól prefixösszegként számoljuk, a végállomás távolsága pedig az összes szakasz hossza. Egy állomás távolsága a végállomástól ennek a két értéknek a különbsége. A K-nál távolabbi állomások közül a legközelebbit úgy kapjuk, hogy az induló állomástól az utolsó előttiig végigmegyünk, és minden találatot felülírunk, mert a végállomáshoz közeledve a távolság csökken. Az időigény O(N).
*/
/*
Hint 1: || Egy állomás távolsága a végállomástól az összes szakasz hosszának és az induló állomástól mért távolságnak a különbsége. ||
Hint 2: || Mivel az állomások a végállomáshoz közeledve egyre közelebb vannak, a K-nál távolabbiak közül az utoljára talált lesz a legközelebbi. Ha egyik sem megfelelő, a kimenet -1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> pos(n + 1, 0);  // pos[i]: az induló állomástól mért távolság
    for (int i = 1; i <= n; i++) {
        int t, arr, dep;
        cin >> t >> arr >> dep;
        pos[i] = pos[i - 1] + t;
    }

    int total = pos[n];  // a végállomás távolsága az induló állomástól
    int ansIdx = -1, ansDist = -1;
    for (int i = 0; i < n; i++) {
        int fromEnd = total - pos[i];  // távolság a végállomástól
        if (fromEnd > k) {
            ansIdx = i;
            ansDist = fromEnd;
        }
    }

    if (ansIdx == -1) {
        cout << -1 << '\n';
    } else {
        cout << ansIdx << ' ' << ansDist << '\n';
    }
    return 0;
}
