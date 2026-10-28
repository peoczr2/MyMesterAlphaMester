/*
Megoldás lényege:
A számokat csökkenő sorrendbe rendezzük, így a legnagyobb lesz az első, a második legnagyobb a következő, és így tovább.
A kimeneti tömb középső indexe m = N / 2 (egész osztással), ide kerül a legnagyobb elem.
A k-adik (0-tól számozott) elem helye: k = 0 esetén m; páratlan k esetén m - (k+1)/2 (balra); páros, nullától különböző k esetén m + k/2 (jobbra).
Így minden elem pontosan egy pozícióba kerül, és a sorrend pontosan az orgonasíp-elrendezés szerinti lesz.
A rendezés miatt az időigény O(N log N), ami N <= 100 mellett bőven belefér az időlimitbe.
*/
/*
Hint 1: || Rendezd a számokat csökkenő sorrendbe, és gondold végig, hogy a legnagyobb elem a kimeneti sor melyik indexére kerül, ha a sor N hosszú és 0-tól számozzuk az indexeket. ||
Hint 2: || A következő elemek felváltva kerülnek a középtől balra és jobbra, mindig eggyel távolabb a középtől; számold ki egy ciklusban minden sorszámhoz a célindexet, és tedd az elemet egy üres tömbbe. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (int &v : x) cin >> v;

    sort(x.rbegin(), x.rend());  // csökkenő sorrend

    vector<int> out(n);
    int m = n / 2;  // a középső index
    for (int k = 0; k < n; k++) {
        int pos;
        if (k == 0) pos = m;
        else if (k % 2 == 1) pos = m - (k + 1) / 2;
        else pos = m + k / 2;
        out[pos] = x[k];
    }

    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << out[i];
    }
    cout << '\n';
    return 0;
}
