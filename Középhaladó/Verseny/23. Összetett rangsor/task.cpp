/*
Megoldás lényege:
Csak azok értékelhetők az összetett versenyben, akik minden versenyen indultak és elérték az adott verseny minimumát; ezek összpontszámát az egyes versenyeken elért pontok összegeként kapjuk. Az értékelhető tanulókat rendezzük: elsődlegesen az összpontszám szerint csökkenő, azonos pontszám esetén a sorszám szerint növekvő sorrendben. A kimenetbe az értékelhetők darabszáma kerül, utána a sorszámaik a rendezett sorrendben. Az időigény O(N·M + N log N), ami gyors.
*/
/*
Hint 1: || Először állapítsd meg, kik értékelhetők: minden versenyen szerepeljenek, és a pontszámuk a verseny minimumát érje el. Az összpontszámot csak ezeknél kell használni. ||
Hint 2: || Tanulónként tárolj egy összpontszámot és egy számlálót arról, hány versenyen teljesítette a feltételt. Rendezésnél a komparátor először az összpontszám szerint csökkenő, majd a sorszám szerint növekvő legyen. ||
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

    vector<int> jo(n + 1, 0), ossz(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int ind;
        cin >> ind;
        for (int j = 0; j < ind; j++) {
            int s, p;
            cin >> s >> p;
            ossz[s] += p;
            if (p >= minimum[i]) {
                jo[s]++;
            }
        }
    }

    vector<int> ert;
    for (int x = 1; x <= n; x++) {
        if (jo[x] == m) {
            ert.push_back(x);
        }
    }

    sort(ert.begin(), ert.end(), [&](int a, int b) {
        if (ossz[a] != ossz[b]) {
            return ossz[a] > ossz[b];
        }
        return a < b;
    });

    cout << ert.size();
    for (int x : ert) {
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
