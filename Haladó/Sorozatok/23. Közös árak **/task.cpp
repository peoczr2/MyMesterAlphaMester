/*
Megoldas lenyege:
A két piacon legfeljebb 1000 féle ár fordulhat elő, ezért elég megjelölni,
mely árak szerepelnek az első és a második piacon. Ezután végigellenőrizzük az
árakat 1-től 1000-ig, és megkeressük a közös értékek közül a legkisebbet és a
legnagyobbat.
*/
/*
Hint 1: || Az árak kicsik, ezért egy 1001 elemű jelölő tömb elég. ||
Hint 2: || Először az egyik, majd a másik piac árainak jelenlétét jelöld. ||
Hint 3: || A közös árak közül a legkisebb és a legnagyobb kell, vagy 0 0, ha nincs ilyen. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];

    vector<char> inA(1001, 0), inB(1001, 0);
    for (int x : a) inA[x] = 1;
    for (int x : b) inB[x] = 1;

    int mn = -1, mx = -1;
    for (int x = 1; x <= 1000; ++x) {
        if (inA[x] && inB[x]) {
            if (mn == -1) mn = x;
            mx = x;
        }
    }

    if (mn == -1) cout << "0 0\n";
    else cout << mn << ' ' << mx << '\n';
    return 0;
}
