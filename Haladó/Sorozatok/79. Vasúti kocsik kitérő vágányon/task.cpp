/*
Megoldás lényege:
A kitérő egy verem: a kocsi csak a tetején lép ki, a balra kiengedett kocsik sorrendje pedig növekvő kell legyen. Egy kiválasztott kocsihalmaz akkor küldhető ki, ha a bemeneti sorrendben a verembe toljuk a kocsikat, és a verem tetején lévő következő várt számot azonnal kiengedjük; a végén a verem üres kell legyen. A feladat a legnagyobb ilyen halmaz mérete, amely ekvivalens a 231-mintát nem tartalmazó részsorozatok maximumával. A kódban minden részhalmazt bitmaszkkal kipróbálunk, ezért az időigény O(2^K * K), és csak K <= 22 esetén fut le; a K <= 100 000 esetre ez a változat nem gyors.
*/
/*
Hint 1: || A verem tetejéről csak akkor engedhetünk ki kocsit, ha ő a következő várt (legkisebb még ki nem engedett) szám; így a kiengedések sorrendje automatikusan növekvő lesz. ||
Hint 2: || Egy kiválasztott halmazra a bemeneti sorrendben tolj a verembe, és minden lépés után engedd ki a verem tetejét, amíg az a következő várt szám; a halmaz akkor jó, ha a verem a végére üres. ||
Hint 3: || A jó halmazok közül a legnagyobb méretűt keresd: K <= 22 esetén mind a 2^K bitmaszk végigpróbálható, és a legnagyobb jó maszk mérete a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int K;
    cin >> K;
    vector<int> a(K), pos(K + 1);
    for (int i = 0; i < K; i++) {
        cin >> a[i];
        pos[a[i]] = i;  // a sorszamok 1..K kozotti permutacio
    }
    if (K > 22) {
        cerr << "tul nagy K a teljes keresehez\n";
        return 1;
    }
    int best = 0;
    for (unsigned mask = 0; mask < (1u << K); mask++) {
        int cnt = __builtin_popcount(mask);
        if (cnt <= best) continue;
        // a kivalasztott kocsik novekvo sorrendje: ezt kell kiengedni
        vector<int> sorted_vals;
        for (int v = 1; v <= K; v++)
            if (mask >> pos[v] & 1) sorted_vals.push_back(v);
        vector<int> st;
        size_t idx = 0;
        for (int i = 0; i < K; i++) {
            if (!(mask >> i & 1)) continue;
            st.push_back(a[i]);
            while (!st.empty() && idx < sorted_vals.size() && st.back() == sorted_vals[idx]) {
                st.pop_back();
                idx++;
            }
        }
        if (st.empty()) best = cnt;
    }
    cout << best << "\n";
    return 0;
}
