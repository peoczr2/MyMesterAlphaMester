/*
Megoldás lényege:
Egy [L,R] intervallum akkor jó, ha minden kézbesítőnek van legalább egy munkanapja ebben az ablakban.
Mivel a napok sorszáma legfeljebb 100000, a teljes idővonalon végigmehetünk naponként, és minden naphoz
meg tudjuk mondani, mely kézbesítők dolgoznak aznap.

Ezután kétmutatós csúszóablakkal keressük a legrövidebb napintervallumot, amelyben minden kézbesítő
legalább egyszer szerepel. Az ablak bővítésekor és szűkítésekor a napi aktív kézbesítők számlálóit
frissítjük.
*/
/*
Hint 1: || A feladat ekvivalens azzal, hogy minden kézbesítő munkanap-halmaza metssze az ablakot. ||
Hint 2: || A napok felső korlátja csak 100000, ezért az idővonal naponként végigjárható. ||
Hint 3: || Ha minden kézbesítő már szerepel az ablakban, balról érdemes szűkíteni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;

    const int MAX_DAY = 100000;
    vector<vector<pair<int,int>>> intervals(k);
    vector<vector<int>> starts(MAX_DAY + 2), ends(MAX_DAY + 2);
    int maxDay = 0;

    for (int courier = 0; courier < k; ++courier) {
        int cnt;
        cin >> cnt;
        intervals[courier].reserve(cnt);
        for (int i = 0; i < cnt; ++i) {
            int l, r;
            cin >> l >> r;
            starts[l].push_back(courier);
            if (r + 1 <= MAX_DAY) ends[r + 1].push_back(courier);
            maxDay = max(maxDay, r);
        }
    }

    vector<vector<int>> activeByDay(maxDay + 1);
    vector<char> active(k, 0);
    for (int day = 1; day <= maxDay; ++day) {
        for (int courier : ends[day]) active[courier] = 0;
        for (int courier : starts[day]) active[courier] = 1;
        activeByDay[day].reserve(k);
        for (int courier = 0; courier < k; ++courier) {
            if (active[courier]) activeByDay[day].push_back(courier);
        }
    }

    vector<int> count(k, 0);
    int covered = 0;
    int bestL = 1;
    int bestR = maxDay;
    int left = 1;

    for (int right = 1; right <= maxDay; ++right) {
        for (int courier : activeByDay[right]) {
            if (count[courier] == 0) ++covered;
            ++count[courier];
        }

        while (covered == k && left <= right) {
            if (right - left < bestR - bestL || (right - left == bestR - bestL && left < bestL)) {
                bestL = left;
                bestR = right;
            }
            for (int courier : activeByDay[left]) {
                --count[courier];
                if (count[courier] == 0) --covered;
            }
            ++left;
        }
    }

    cout << bestL << ' ' << bestR << '\n';
    return 0;
}