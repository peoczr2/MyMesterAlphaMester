/*
Megoldás lényege:
Egy őr szolgálata a kezdőnapon a napi létszámot +1-gyel, a végét követő napon -1-gyel változtatja meg.
Ezt egy különbségtömbbel rögzítjük: minden őrre a kezdőnap mezőjéhez 1-et, a végnap utáni mező értékéhez -1-et adunk.
Ezután a tömb prefixösszege adja meg az egyes napok létszámát. A határokat a [1, M] tartományra vágjuk.
Az időigény O(M + N), a memóriaigény O(M).
*/
/*
Hint 1: || Gondold végig, mi történik a napi létszámmal, amikor egy őr szolgálata elkezdődik, illetve véget ér: csak a határnapoknál változik. ||
Hint 2: || Tárolj egy különbségtömböt: a kezdőnap mezőjéhez adj 1-et, a végét követő nap mezőjéből vonj le 1-et. Ezután a tömb prefixösszege adja a napi létszámot. ||
Hint 3: || Részletesen: a napokat 1-től M-ig nézed, a futó összeget minden napnál hozzáadod a tömb aktuális elemével, és kiírod. A tömb M+2 méretű legyen, a tartományon kívüli határokat pedig vágd le. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    vector<int> kul(m + 2, 0);
    for (int i = 0; i < n; i++) {
        int e, u;
        cin >> e >> u;
        e = max(e, 1);
        u = min(u, m);
        if (e <= u) {
            kul[e]++;
            kul[u + 1]--;
        }
    }
    int aktualis = 0;
    for (int d = 1; d <= m; d++) {
        aktualis += kul[d];
        cout << aktualis << (d < m ? ' ' : '\n');
    }
    return 0;
}
