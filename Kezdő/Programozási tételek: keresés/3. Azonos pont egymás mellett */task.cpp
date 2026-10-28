/*
Megoldás lényege:
A pontszámokat egyszer végigjárjuk, és minden i-re megnézzük, hogy a P[i] egyenlő-e a következő elemmel P[i+1]. Az első ilyen i sorszámát (1-től számozva) kell kiírni, ha nincs egyezés, akkor 0 a válasz. Mivel N legfeljebb 100, az időigény O(N).
*/
/*
Hint 1: || Elég minden elemet összevetni a közvetlenül utána következő elemmel, egyetlen lineáris bejárásban. ||
Hint 2: || Az első találatnál azonnal írd ki az elem sorszámát, és ha a végéig nincs egyezés, a kiírandó érték 0. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int &x : p) cin >> x;

    for (int i = 0; i + 1 < n; i++) {
        if (p[i] == p[i + 1]) {
            cout << i + 1 << '\n';
            return 0;
        }
    }
    cout << 0 << '\n';
    return 0;
}
