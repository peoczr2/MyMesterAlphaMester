/*
Megoldás lényege:
Egy szempont akkor jelent kiesést, ha a kutya pontszáma az adott alsó határ alatt van.
Egy pluszpont csak egy szempont pontszámát változtatja, ezért a kutya csak akkor marad bent a pluszpont után, ha pontosan egy szempontban esik ki.
Ha ez az egyetlen kiesés pontosan 1 ponttal van az alsó határ alatt, akkor az egy pluszpont éppen eléri a határt, és a kutya bent marad: ezt a kutyát kell kiírni.
Ha több szempontban esik ki, vagy az egyetlen kiesésnél nagyobb a hiány, a kutya nem felel meg.
Kutyánként egy beolvasással számoljuk a kiesési szempontokat, és az utolsó kiesésnél a hiányt.
Az idő O(N · M), a memóriaigény O(N + M).
*/
/*
Hint 1: || Egy pluszpont csak egy szempont pontszámát növeli, ezért a kutyának pontosan egy kiesési szempontja lehet. Ha két szempontban is az alsó határ alatt van, az egy pluszponttal nem változik. ||
Hint 2: || Kutyánként számold meg a kiesési szempontokat, és az egyetlen kiesésnél nézd meg, hány ponttal van az alsó határ alatt. A kutyát akkor kell kiírni, ha ez a különbség pontosan 1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // A maximumokra a feladatban nincs szükség, csak beolvassuk őket.
    for (int i = 0; i < m; i++) {
        int maxi;
        cin >> maxi;
    }

    vector<int> minPont(m);
    for (int &x : minPont) cin >> x;

    vector<int> kiesok;
    for (int j = 1; j <= n; j++) {
        int kiesesek = 0;  // kiesési szempontok száma
        int hiany = 0;     // az utolsó kiesési szempontban hiányzó pontok
        for (int i = 0; i < m; i++) {
            int p;
            cin >> p;
            if (p < minPont[i]) {
                kiesesek++;
                hiany = minPont[i] - p;
            }
        }
        if (kiesesek == 1 && hiany == 1) kiesok.push_back(j);
    }

    cout << kiesok.size();
    for (int j : kiesok) cout << ' ' << j;
    cout << '\n';
    return 0;
}
