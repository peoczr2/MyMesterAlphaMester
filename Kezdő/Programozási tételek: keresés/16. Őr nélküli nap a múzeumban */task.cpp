/*
Megoldás lényege:
Az őrök szolgálatát különbségtömbbel jelöljük: egy őr szolgálatának első napjához +1-et, az utolsó nap utáni naphoz -1-et írunk. A prefixösszeg a napok szerinti sorrendben megadja, hány őr van éppen szolgálatban, így az első olyan napot keressük, amelyre ez az összeg nulla. Ha minden nap be van osztva, a válasz 0. Az időigény O(M + N), ami a korlátok mellett gyors.
*/
/*
Hint 1: || Nem kell minden napot minden őrrel összevetni: számold meg napról napra, hány őr van szolgálatban, és figyeld, mikor lesz ez a szám nulla. ||
Hint 2: || Egy őr szolgálatának kezdő napjához adj +1-et, a végét követő naphoz -1-et (különbségtömb), majd a napok szerinti prefixösszeg megmutatja, melyik nap volt üres. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;

    // kulonbseg[d]: a d. napon kezdődő szolgálatok száma, a d. napot követően véget érő szolgálatok (negatív) száma
    vector<int> kulonbseg(m + 2, 0);
    for (int i = 0; i < n; ++i) {
        int e, u;
        cin >> e >> u;
        kulonbseg[e]++;
        kulonbseg[u + 1]--;
    }

    int szolgalatban = 0;
    for (int nap = 1; nap <= m; ++nap) {
        szolgalatban += kulonbseg[nap];
        if (szolgalatban == 0) {
            cout << nap << '\n';
            return 0;
        }
    }
    cout << 0 << '\n';
}
