/*
Megoldás lényege:
Egy versenyző akkor szerez pontot egy versenyen, ha a helyezése 1 és K közé esik, mert csak az első K helyezett kap pontot; a 0 azt jelenti, hogy nem indult, ezért ott nincs pontja. A kiosztott pontok értéke és az olimpiai holtverseny-szabály a kérdéshez nem kell. Minden versenyzőnél az öt helyezést egyenként ellenőrizzük: ha valamelyik nem esik az 1..K tartományba, a versenyző kiesik. Az indexek növekvő sorrendben érkeznek, így a megmaradó versenyzők sorszámai is rendezve kerülnek a listába. A futásidő N·5 lépés.
*/
/*
Hint 1: || Egy versenyen akkor szerez pontot a versenyző, ha a helyezése legalább 1 és legfeljebb K; a 0 azt jelenti, hogy nem indult. Csak azt kell eldönteni, hogy minden helyezés a megfelelő tartományba esik-e. ||
Hint 2: || Versenyzőnként olvasd be az öt helyezést, és egy logikai jelzőben tartsd nyilván, volt-e köztük a tartományon kívüli érték; ha nem volt, a versenyző sorszámát vedd fel a listába. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> minden_versenyen;
    for (int i = 1; i <= n; ++i) {
        bool pontot_szerzett_mindenhol = true;
        for (int j = 0; j < 5; ++j) {
            int h;
            cin >> h;
            if (h < 1 || h > k) {
                pontot_szerzett_mindenhol = false;
            }
        }
        if (pontot_szerzett_mindenhol) {
            minden_versenyen.push_back(i);
        }
    }

    cout << minden_versenyen.size() << '\n';
    for (size_t t = 0; t < minden_versenyen.size(); ++t) {
        if (t > 0) {
            cout << ' ';
        }
        cout << minden_versenyen[t];
    }
    cout << '\n';
    return 0;
}
