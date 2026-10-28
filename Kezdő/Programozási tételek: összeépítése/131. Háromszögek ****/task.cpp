/*
Megoldás lényege:
Egy A hosszúságú szakasz a B és C szakaszokkal pontosan akkor ad háromszöget, ha A < B + C, B < A + C és C < A + B. A két utóbbi feltétel együtt azt jelenti, hogy A > |B − C|. Így a jó hosszúságok a (|B − C|, B + C) nyílt intervallumba esnek. Kázmér szakaszait egyszer rendezzük, majd minden kérdésre két bináris kereséssel megszámoljuk, hány hossz esik az intervallumba. Az idő O(N log N + Q log N); az összegek miatt 64 bites egészeket használunk.
*/
/*
Hint 1: || Az A szakasz pontosan akkor jó, ha |B − C| < A < B + C. Írd fel ezt az intervallumot minden kérdésre. ||
Hint 2: || Ha a szakaszokat rendezed, az intervallumba eső hosszak a rendezett sorozatban egy összefüggő szakaszt alkotnak. ||
Hint 3: || Két bináris kereséssel (upper_bound a |B − C|-re, lower_bound a B + C-re) megkapod az intervallumba eső elemek határát; a különbségük a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;
    sort(a.begin(), a.end());

    for (int i = 0; i < q; ++i) {
        long long b, c;
        cin >> b >> c;
        long long lo = (b > c) ? b - c : c - b;  // A > lo
        long long hi = b + c;                     // A < hi
        auto first = upper_bound(a.begin(), a.end(), lo);
        auto last = lower_bound(a.begin(), a.end(), hi);
        cout << (last - first) << '\n';
    }
    return 0;
}
