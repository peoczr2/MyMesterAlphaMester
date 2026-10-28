/*
Megoldás lényege:
Gyanús csak a belső mérés lehet, mert az első és az utolsó mérés biztosan helyes, és csak a belső méréseknek van két szomszédja. Egy belső mérés eltérését a két szomszédja átlagától mérjük. A törtek elkerülése végett ennek kétszeresét számoljuk: 2·Hi − H(i−1) − H(i+1), és vesszük az abszolút értékét. Egy menetben keressük a legnagyobb eltérést, és csak szigorúan nagyobb értéknél frissítünk, így több azonos eltérés esetén az első előfordulás marad. Ha minden belső mérés pontosan a szomszédai átlaga, akkor nincs gyanús mérés, és 0-t írunk ki. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Csak a 2. és az (N−1). mérés között lehet gyanús mérés, mert mindegyiknek van két szomszédja. ||
Hint 2: || Az átlagtól való eltérés helyett a 2·Hi − H(i−1) − H(i+1) értéket hasonlítsd össze, abszolút értékkel: így nem kell törtekkel dolgozni. ||
Hint 3: || Egy menetben tartsd nyilván az eddigi legnagyobb eltérést és a mérés sorszámát; ha nem találsz nullától különböző eltérést, a kimenet 0 marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    int bestIndex = 0;
    int bestDev = 0;
    for (int i = 1; i + 1 < n; i++) {
        int dev = abs(2 * h[i] - h[i - 1] - h[i + 1]);
        if (dev > bestDev) {
            bestDev = dev;
            bestIndex = i + 1;
        }
    }

    cout << bestIndex << "\n";
    return 0;
}
