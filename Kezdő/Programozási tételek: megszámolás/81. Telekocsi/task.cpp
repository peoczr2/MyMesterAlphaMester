/*
Megoldás lényege:
Az autósok csak ugyanabba a városba tudnak utasokat vinni, ezért a városokat külön vizsgálhatjuk. Egy városban egy autó legfeljebb 3 utast visz, így az autók összes befogadóképessége 3 * (az autók száma). Az ott szállítható utasok száma ennek és az oda igyekvő utasok számának a minimuma. A teljes válasz a városonkénti minimumok összege. Az egész O(N + M) időben kiszámolható, mert csak a betűk gyakoriságát számoljuk.
*/
/*
Hint 1: || Az autósok és az utasok csak ugyanazon városba tudnak eljutni, ezért városonként külön számolhatsz. ||
Hint 2: || Egy városban az autók férőhelye 3-szorosa az autók számának. Az oda szállítható utasok száma ennek és az utasok számának a minimuma. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    long long cars[26] = {0};
    for (int i = 0; i < n; ++i) {
        char ch;
        cin >> ch;
        cars[ch - 'a']++;
    }

    int m;
    cin >> m;
    long long people[26] = {0};
    for (int i = 0; i < m; ++i) {
        char ch;
        cin >> ch;
        people[ch - 'a']++;
    }

    long long ans = 0;
    for (int c = 0; c < 26; ++c)
        ans += min(people[c], 3 * cars[c]);

    cout << ans << "\n";
    return 0;
}
