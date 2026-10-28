/*
Megoldás lényege:
A kérdés a legkorábbi háborús évtől a legkésőbbi befejezésig tartó időszak azon éveinek száma, amelyekben nincs háború. Ezt úgy kapjuk meg, hogy a teljes időszak éveinek számából kivonjuk a háborús évek számát.
A háborúkat kezdő év szerint rendezzük, majd egy menetben egyesítjük az egymást átfedő intervallumokat, és összeadjuk az egyesített szakaszok éveit. Az egyesítés után a háborús évek száma pontosan a lefedett évek száma lesz.
Az idő O(K log K), ahol K a háborúk száma, a rendezés miatt.
*/
/*
Hint 1: || Az időszak a legkorábbi kezdéstől a legkésőbbi befejezésig tart, és ebben kell megszámolni azokat az éveket, amelyeket egyetlen háború sem fed le. Gondold át, hogy a háborúk kezdő és befejező éveiből hogyan lehet megtudni a lefedett éveket. ||
Hint 2: || Rendezd a háborúkat a kezdő év szerint, majd menet közben vond össze az átfedő intervallumokat: ha a következő háború kezdő éve nem nagyobb az aktuális szakasz befejező événél, meghosszabbítod a szakaszt, különben új szakaszt nyitsz. Az összevont szakaszok éveinek összegét vond ki a teljes időszak éveinek számából. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    // A minta be1 fájlja elején UTF-8 BOM állhat (3 bájt): ezt átugorjuk.
    if (cin.peek() == 0xEF) cin.ignore(3);

    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> haboru(k);  // (kezdő év, befejező év)
    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b >> haboru[i].first >> haboru[i].second;
    }
    if (k == 0) {
        cout << 0 << '\n';
        return 0;
    }
    sort(haboru.begin(), haboru.end());

    int elso = haboru.front().first;  // legkorábbi háborús év
    int utolso = 0;                   // legkésőbbi háborús év
    for (const auto& p : haboru) utolso = max(utolso, p.second);

    // Az átfedő háborús intervallumok egyesítése, és a lefedett évek összeszámolása.
    long long haboruEv = 0;
    int cs = haboru[0].first, ce = haboru[0].second;
    for (int i = 1; i < k; i++) {
        int s = haboru[i].first, e = haboru[i].second;
        if (s <= ce) {
            ce = max(ce, e);
        } else {
            haboruEv += ce - cs + 1;
            cs = s;
            ce = e;
        }
    }
    haboruEv += ce - cs + 1;

    cout << (utolso - elso + 1) - haboruEv << '\n';
}
