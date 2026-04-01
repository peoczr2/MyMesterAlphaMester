/*
Megoldási ötlet:
A bevételi cél F legfeljebb 10000, ezért érdemes pénz szerinti dinamikus programozást használni. Legyen dp[v]
az a minimális idő, amely alatt pontosan v forintot, illetve F fölött bármit F-re lekerekítve legalább F forintot
meg lehet keresni.

Minden munkát legfeljebb egyszer választhatunk, ezért 0/1 hátizsák jellegű DP-t futtatunk. Rekonstrukcióhoz eltároljuk,
hogy egy állapot javításához melyik munka kellett. A végén a dp[F] adja a minimális időt.
*/
/*
Hint 1: || A bevételi cél kicsi, ezért a „minimum idő adott bevételhez” típusú DP kényelmes. ||
Hint 2: || Ha egy munkával túllépnéd F-et, nyugodtan az F állapotba gyűjtheted. ||
Hint 3: || Visszafejtéshez jegyezd meg, hogy melyik előző bevételből és melyik munkával jutottál az új állapotba. ||
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, target;
    cin >> n >> target;
    vector<int> timeCost(n + 1), revenue(n + 1);
    for (int i = 1; i <= n; ++i) cin >> timeCost[i] >> revenue[i];

    const int inf = numeric_limits<int>::max() / 4;
    vector<int> previous(target + 1, inf), current(target + 1, inf);
    vector<vector<char>> take(n + 1, vector<char>(target + 1, 0));
    vector<vector<int>> parentValue(n + 1, vector<int>(target + 1, -1));
    previous[0] = 0;

    for (int item = 1; item <= n; ++item) {
        current = previous;
        for (int value = 0; value <= target; ++value) {
            if (previous[value] == inf) continue;
            int nextValue = min(target, value + revenue[item]);
            int candidate = previous[value] + timeCost[item];
            if (candidate < current[nextValue]) {
                current[nextValue] = candidate;
                take[item][nextValue] = 1;
                parentValue[item][nextValue] = value;
            }
        }
        swap(previous, current);
    }

    vector<int> chosen;
    int currentValue = target;
    for (int item = n; item >= 1; --item) {
        if (!take[item][currentValue]) continue;
        chosen.push_back(item);
        currentValue = parentValue[item][currentValue];
    }
    sort(chosen.begin(), chosen.end());

    cout << previous[target] << '\n';
    cout << chosen.size();
    for (int index : chosen) cout << ' ' << index;
    cout << '\n';
    return 0;
}