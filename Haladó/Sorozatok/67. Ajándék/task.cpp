/*
Megoldas lenyege:
Az ajandekok szama egy osszefuggo szigetszakasz lakossagszamanak osszege. Mivel minden lakossag
pozitiv, ket mutatoval linearis idoben megkeresheto az a legbaloldalibb reszszakasz, amelynek
osszege pontosan K.

Jobb veggel noveljuk az aktualis osszeget, es amig az nagyobb K-nal, balrol elhagyunk szigeteket.
Amikor az osszeg pontosan K lesz, a jelenlegi [L,R] szakasz mar a legbaloldalibb ilyen jobb veghez,
es mivel a bal veg csak jobbra mozoghat, ez globalisan is a legkisebb elso indexet adja.
*/
/*
Hint 1: || A pozitiv lakossagszamok miatt a ket mutatos technika mukodik. ||
Hint 2: || Ha az aktualis osszeg tul nagy, csak a bal veg novelese segithet. ||
Hint 3: || Az elso megtalalt pontos osszegu ablak automatikusan a legbaloldalibb megoldas. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    int left = 1;
    long long sum = 0;
    for (int right = 1; right <= n; ++right) {
        sum += a[right];
        while (sum > k && left <= right) sum -= a[left++];
        if (sum == k) {
            cout << left << ' ' << right << '\n';
            return 0;
        }
    }

    cout << -1 << '\n';
    return 0;
}