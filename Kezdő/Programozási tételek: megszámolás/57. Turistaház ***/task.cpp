/*
Megoldás lényege:
Az utazások nem fedhetik egymást, ezért a turistaház szabad napjait összefüggő, csak 'S' betűkből álló szakaszokra bontjuk, és minden szakaszt külön vizsgálunk. Egy L hosszú szakaszba L / K (egész osztás) darab K napos utazás fér el, az összes utazás száma ezek összege. Egy utazás pontosan akkor hosszabbítható meg egy nappal, ha mellette van még szabad, más utazáshoz nem foglalt nap. A szakasz L mod K darab maradék napja adhat ilyen napot, ezért egy szakaszban min(L / K, L mod K) utazás hosszabbítható meg. A mintán (15 nap, K = 3) az [1..3] szakasz 1 utazást ad, de nem hosszabbítható, a [8..15] szakasz 2 utazást ad, és mindkettő hosszabbítható, így a válasz 3 és 2. Az időigény O(N), N legfeljebb 1000.
*/
/*
Hint 1: || Az utazások nem fedhetik egymást, ezért a turistaház szabad napjait érdemes külön-külön, összefüggő szabad szakaszokra bontani. Egy szakasz határát az első vagy az utolsó 'F' jelzi. ||
Hint 2: || Egy szakaszban hány K napos utazás fér el, és hány szabad nap marad mellettük? Ha a szakasz hossza L, akkor az utazások száma L / K egész része, a maradék napok száma pedig L mod K. A maradék napok száma korlátot ad arra, hány utazás hosszabbítható meg. ||
Hint 3: || Szakaszonként a meghosszabbítható utazások száma min(L / K, L mod K). Az összes szakaszra összegezve kapod a két kért számot: az utazások számát és a meghosszabbíthatók számát. A szakaszokat egyetlen balról jobbra haladó bejárással lehet végigvenni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    int utazasok = 0;
    int meghosszabbithato = 0;
    int i = 0;
    while (i < n) {
        if (s[i] != 'S') {
            i++;
            continue;
        }
        int j = i;
        while (j < n && s[j] == 'S') {
            j++;
        }
        int hossz = j - i;
        int db = hossz / k;
        int maradek = hossz % k;
        utazasok += db;
        meghosszabbithato += min(db, maradek);
        i = j;
    }
    cout << utazasok << "\n" << meghosszabbithato << "\n";
    return 0;
}
