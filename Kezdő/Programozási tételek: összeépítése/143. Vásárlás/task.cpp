/*
Megoldás lényege:
Az A áruházlánc csak összefüggő szakaszt vásárolhat meg: ha L és R nála van, a köztes termékek is nála kell legyenek, így az A-nál vett termékek halmaza egy [L;R] intervallum, vagy üres. Ha mindent a B-nél vennénk, a költség a b_i értékek összege; az intervallum elemeit A-ra cserélve az i-edik termék többlete a_i - b_i. A feladat tehát a b_i-k összege plusz a legkisebb összegű összefüggő részsorozat az a_i - b_i értékekből (az üres részsorozat megengedett). Ezt egyetlen bejárással (Kadane-algoritmus) megoldjuk, az időigény O(N).
*/
/*
Hint 1: || Az A-nál vett termékek halmazára a feltétel azt jelenti, hogy összefüggő szakasz (vagy üres). Képzeld el, hogy mindent a B-nél veszel, és csak az A-nál vett szakasz elemeit cseréled le. ||
Hint 2: || Az i-edik termék cseréjének többlete a_i - b_i, ami lehet negatív is. Egy bejárásban tartsd nyilván az aktuális elemnél végződő legkisebb összeget és az eddigi legjobb találatot, az üres szakaszt is figyelembe véve. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;

    long long sumB = 0;
    for (long long x : b) sumB += x;

    long long bestDelta = 0, curDelta = 0;
    for (int i = 0; i < n; i++) {
        long long d = a[i] - b[i];
        curDelta = min(d, curDelta + d);
        bestDelta = min(bestDelta, curDelta);
    }

    cout << sumB + bestDelta << "\n";
    return 0;
}
