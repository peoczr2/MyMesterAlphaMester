/*
Megoldás lényege:
Az elemeket csökkenő sorrendbe rendezzük, majd ebben a sorrendben töltjük ki a kimeneti sorozatot kívülről befelé.
A rendezett lista 1., 3., 5. … elemei a sorozat elejéről indulva balról jobbra, a 2., 4., 6. … elemei a végéről indulva jobbról balra kerülnek a helyükre.
Így a legnagyobb az első helyre kerül, a második legnagyobb az utolsóra, a harmadik a második helyre, és így tovább.
A rendezés miatt az időigény O(N log N).
*/
/*
Hint 1: || A kimenet első eleme a legnagyobb, az utolsó a második legnagyobb, a második hely a harmadik legnagyobb: tehát először rendezd az elemeket csökkenő sorrendbe. ||
Hint 2: || Tarts két mutatót: a bal kezdetben 0, a jobb N-1. A rendezett lista 1., 3., 5. … elemét a bal mutatóhoz írd és növeld, a 2., 4., 6. … elemét a jobb mutatóhoz írd és csökkentsd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    sort(a.begin(), a.end(), greater<int>());

    vector<int> res(n);
    int l = 0, r = n - 1;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) res[l++] = a[i]; // a sorozat eleje
        else            res[r--] = a[i]; // a sorozat vége
    }

    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << res[i];
    }
    cout << '\n';
    return 0;
}
