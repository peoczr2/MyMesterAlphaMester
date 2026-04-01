/*
Megoldas lenyege:
Olyan négyes kell, ahol a harmadik elem a legnagyobb, a negyedik pedig a
legkisebb. Ez azt jelenti, hogy van egy középső pozíció, amely előtt legalább két
elem található a következő feltétellel: nagyobbak a későbbi legkisebb elemnél,
de kisebbek a középsőnél. A permutáció prefixében Fenwick-fával megszámoljuk,
hány már látott elem esik ebbe az intervallumba, és ha legalább kettő van,
akkor ki tudunk választani két korábbi értéket, a középsőt és a későbbi minimumot.
*/
/*
Hint 1: || A negyedik elem legyen a jobb oldali legkisebb elem. ||
Hint 2: || A harmadik elemhez a prefixben két olyan szám kell, amely a jobb oldali minimum fölött, de a harmadik alatt van. ||
Hint 3: || A látott értékek számolására elég egy Fenwick-fa. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> bit;
    Fenwick(int n) : n(n), bit(n + 1, 0) {}
    void add(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) bit[idx] += val;
    }
    int sum(int idx) const {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx) res += bit[idx];
        return res;
    }
    int kth(int k) const {
        int idx = 0;
        int pw = 1;
        while ((pw << 1) <= n) pw <<= 1;
        for (int step = pw; step; step >>= 1) {
            int next = idx + step;
            if (next <= n && bit[next] < k) {
                idx = next;
                k -= bit[next];
            }
        }
        return idx + 1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n + 1), pos(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pos[a[i]] = i;
    }

    vector<int> suffixMinVal(n + 2, n + 1), suffixMinPos(n + 2, n + 1);
    for (int i = n; i >= 1; --i) {
        if (a[i] < suffixMinVal[i + 1]) {
            suffixMinVal[i] = a[i];
            suffixMinPos[i] = i;
        } else {
            suffixMinVal[i] = suffixMinVal[i + 1];
            suffixMinPos[i] = suffixMinPos[i + 1];
        }
    }

    Fenwick fw(n);
    for (int i = 1; i <= n; ++i) {
        int third = a[i];
        int fourthVal = suffixMinVal[i + 1];
        if (fourthVal <= n) {
            int low = fw.sum(fourthVal);
            int high = fw.sum(third - 1);
            if (high - low >= 2) {
                int v1 = fw.kth(low + 1);
                int v2 = fw.kth(low + 2);
                vector<pair<int,int>> firstTwo = {{pos[v1], v1}, {pos[v2], v2}};
                sort(firstTwo.begin(), firstTwo.end());
                cout << firstTwo[0].second << ' ' << firstTwo[1].second << ' ' << third << ' ' << fourthVal << '\n';
                return 0;
            }
        }
        fw.add(a[i], 1);
    }

    cout << 0 << '\n';
    return 0;
}
