/*
Megoldás lényege:
Az emberek és a dinnyeárusító helyek is rendezett sorrendben vannak. Két mutatóval
végigmegyünk a két sorozaton, és mindig a legkisebb még nem használt embert és
helyet próbáljuk párosítani. Ha a hely túl balra van, előre lépünk a helyekben;
ha túl jobbra van, az adott ember nem tud már senkihez menni, ezért őt hagyjuk ki.
Az időigény O(N + M), mert mindkét mutató legfeljebb a saját sorozata hosszáig lép.
*/
/*
Hint 1: || Mindkét sorozat rendezett, ezért mindig a legkisebb még nem párosított embert és a legkisebb még nem használt helyet érdemes összehasonlítani. ||
Hint 2: || Ha a távolság legfeljebb K, párosítsd őket, és mindkét mutató lép. Ha a hely több mint K-val az ember előtt van, a helyet eldobod; ha a hely több mint K-val az ember után van, az embernek nincs használható helye, ezért őt hagyod ki. ||
Hint 3: || Addig lépkedj a két mutatóval, amíg valamelyik sorozat el nem fogy, és minden párosításnál növeld a számlálót; a számláló értéke lesz a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> emb(n);
    for (int i = 0; i < n; ++i) cin >> emb[i];

    int m;
    cin >> m;
    vector<int> hely(m);
    for (int i = 0; i < m; ++i) cin >> hely[i];

    int k;
    cin >> k;

    int i = 0, j = 0, ans = 0;
    while (i < n && j < m) {
        if (abs(emb[i] - hely[j]) <= k) {
            ++ans;
            ++i;
            ++j;
        } else if (hely[j] < emb[i] - k) {
            ++j;
        } else {
            ++i;
        }
    }

    cout << ans << '\n';
    return 0;
}
