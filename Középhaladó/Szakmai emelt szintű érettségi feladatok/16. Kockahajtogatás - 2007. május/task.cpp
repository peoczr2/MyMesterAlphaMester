/*
Megoldás lényege:
A két papírlap-oldal sorrendje nem számít, ezért először rendezzük őket: a kisebb legyen A, a nagyobb B. A kocka akkor hajtogatható, ha a hosszabb oldal legalább 4E, a rövidebb oldal legalább 3E, ahol E a kocka élhossza. Mindkét feltételt ellenőrizzük, mert a feladat mindkettőt előírja. Minden tesztesetre O(1) munka kell, így az összes eset O(N) időben feldolgozható.
*/
/*
Hint 1: || A két oldal sorrendje nem számít, ezért érdemes a rövidebb és a hosszabb oldalt külön azonosítani: például két számot rendezz sorrendbe. ||
Hint 2: || A hosszabb oldalt az E négyszeresével, a rövidebb oldalt az E háromszorosával kell összevetni. Ha valamelyik feltétel nem teljesül, a válasz NEM. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        long long e, a, b;
        cin >> e >> a >> b;
        if (a > b) swap(a, b);
        if (b >= 4 * e && a >= 3 * e) cout << "IGEN\n";
        else cout << "NEM\n";
    }
    return 0;
}
