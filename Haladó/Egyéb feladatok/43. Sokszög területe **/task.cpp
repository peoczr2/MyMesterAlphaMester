/*
Megoldás lényege:
A sokszög csúcsai egész koordinátájúak, ezért a rácspontok száma a Pick-tétellel számolható: ha a terület A, a belső rácspontok száma I, a határon lévő rácspontok száma B, akkor A = I + B/2 - 1. A keresett szám a sokszöghöz tartozó rácspontok összesítése, vagyis I + B = A + B/2 + 1, a határ is beleszámít. A területet a cipőformulával számoljuk ki kétszeres értékben (egész számként, így nincs törtes művelet), a határpontokat pedig élenként a gcd(|dx|, |dy|) adja meg. Így az eredmény (2A + B)/2 + 1, a futási idő O(N log M), ahol N a csúcsok száma.
*/
/*
Hint 1: || Nem kell a képpontokat egyenként végigvizsgálni: a sokszög rácspontjai a Pick-tétellel kiszámolhatók. Gondold át, milyen kapcsolat van a terület, a belső és a határon lévő rácspontok száma között. ||
Hint 2: || A kétszeres területet a csúcsok koordinátáiból a cipőformulával kapod meg egész számként. A határon lévő rácspontok száma az egyes élek mentén gcd(|dx|, |dy|), ahol dx és dy az él két végpontjának koordinátakülönbsége. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long m;  // a rácsméret; a számításhoz nem kell
    cin >> n >> m;

    vector<long long> x(n), y(n);
    for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];

    // Cipőformula: a kétszeres terület (előjeltől függetlenül).
    // Határ: az egyes élekre eső rácspontok száma (a végpont nélkül), összegezve gcd-vel.
    long long twiceArea = 0;
    long long boundary = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        twiceArea += x[i] * y[j] - x[j] * y[i];
        boundary += gcd(llabs(x[j] - x[i]), llabs(y[j] - y[i]));
    }
    twiceArea = llabs(twiceArea);

    // Pick-tétel: A = I + B/2 - 1, így I + B = (2A + B) / 2 + 1.
    long long answer = (twiceArea + boundary) / 2 + 1;
    cout << answer << '\n';
    return 0;
}
