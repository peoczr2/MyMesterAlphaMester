/*
Megoldás lényege:
Mivel az árak nemcsökkenő sorrendben vannak, minden első utazáshoz a másik két utazást kétmutatós módszerrel keressük: a bal mutató az első utáni utazástól, a jobb az utolsótól indul. Ha a három ár összege nagyobb F-nél, a jobb mutatót csökkentjük; különben az összeget összevetjük az eddigi legjobbal, és a bal mutatót növeljük. Az összes első utazásra együtt O(N^2) idő kell, a memóriaigény O(N).
*/
/*
Hint 1: || Rögzíts egy első utazást. A másik két utazást a rendezettség miatt kétmutatós kereséssel találod meg: a bal mutató az első utáni utazástól, a jobb mutató az utolsótól induljon. ||
Hint 2: || Ha a három ár összege F-nél nagyobb, a jobb mutatót csökkentsd, különben a hármas érvényes. Érvényes összegnél frissítsd a legjobb eddigi összeget, és a bal mutatót léptesd tovább. Ha egy hármas sem fér bele F forintba, a válasz -1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long f;
    cin >> n >> f;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    long long best = -1;
    int bi = -1, bj = -1, bk = -1;

    for (int i = 1; i <= n - 2; ++i) {
        int l = i + 1, r = n;
        while (l < r) {
            long long sum = a[i] + a[l] + a[r];
            if (sum > f) {
                --r;
            } else {
                if (sum > best) {
                    best = sum;
                    bi = i; bj = l; bk = r;
                }
                ++l;
            }
        }
    }

    if (best < 0) {
        cout << -1 << '\n';
    } else {
        cout << bi << ' ' << bj << ' ' << bk << '\n';
    }
    return 0;
}