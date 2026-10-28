/*
Megoldás lényege:
Tanulónként számoljuk, hány versenyen teljesítette a feltételt, vagyis hány versenyen indult és érte el az adott verseny minimumát. Az összetett versenyben pontosan azok értékelhetők, akiknek ez a szám az M versenyek száma; a többiek nem értékelhetők. A nem értékelhetők sorszámát növekvő sorrendben, a darabszámukkal együtt írjuk ki. Az időigény O(N·M), ami gyors.
*/
/*
Hint 1: || Egy tanuló nem értékelhető, ha valamelyik versenyen nem szerepel, vagy szerepel, de a pontszáma kisebb a verseny minimumánál. Elég egyetlen ilyen eset is. ||
Hint 2: || Tanulónként számold meg, hány versenyen indult úgy, hogy elérte a verseny minimumát. Ha ez a szám kisebb M-nél, a tanuló nem értékelhető. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> minimum(m);
    for (int i = 0; i < m; i++) {
        cin >> minimum[i];
    }

    vector<int> jo(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int ind;
        cin >> ind;
        for (int j = 0; j < ind; j++) {
            int s, p;
            cin >> s >> p;
            if (p >= minimum[i]) {
                jo[s]++;
            }
        }
    }

    vector<int> nemErtekelheto;
    for (int x = 1; x <= n; x++) {
        if (jo[x] != m) {
            nemErtekelheto.push_back(x);
        }
    }

    cout << nemErtekelheto.size();
    for (int x : nemErtekelheto) {
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
