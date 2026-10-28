/*
Megoldás lényege:
Egy i település akkor felel meg, ha van olyan j település, amelynél minden napon melegebbet jósolnak i-re. Egy napon a településeket hőmérséklet szerint csoportosítjuk, és a csoportokon sorban haladva bitsetben gyűjtjük a már bejárt, kisebb értékű településeket. Minden i-hez ezt a halmazt az eddigi napok halmazával metsszük (ÉS művelet). Végül a legkisebb sorszámú olyan i-t írjuk ki, amelyhez a metszet nem üres. Az idő O(M·(N log N + N²/64)), ez a naiv O(N²·M) helyett gyors.
*/
/*
Hint 1: || Az i. település akkor felel meg, ha létezik olyan j, amelyre *minden* napon h[i][nap] > h[j][nap]. Ez nem egy napra, hanem az összes napra egyszerre vonatkozik. ||
Hint 2: || Páronkénti, napról napra történő ellenőrzés N²·M ≈ 10⁹ műveletet jelent, ami 0,1 mp alatt nem fér bele. Gondold végig, hogy egy adott napon mely j-kre teljesül a feltétel, és ezeket a halmazokat tartsd nyilván. ||
Hint 3: || Egy napon csoportosítsd a településeket a hőmérséklet szerint (az értékek -50 és 50 közöttiek, így 101 csoport elég), és a csoportokon sorban haladva egy bitsetben gyűjtsd a már bejárt, kisebb értékű településeket. Egyenlő értékek esetén a csoport tagjait a csoport előtti halmazzal metszd, és csak utána tedd be őket a halmazba. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // h[j][i]: az i. település j. napi előrejelzése (napok szerint tárolva)
    vector<vector<int>> h(m, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> h[j][i];

    // legyoz[i]: azon települések halmaza, amelyekre i minden eddigi napon melegebb volt
    vector<bitset<1000>> legyoz(n);
    for (int i = 0; i < n; i++) legyoz[i].set();

    // csoport[v+50]: azok a települések, amelyeknek ezen a napon v a hőmérséklete
    // (a hőmérséklet -50 és 50 közötti, így 101 csoport elég; számláló rendezés)
    vector<vector<int>> csoport(101);
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) csoport[h[j][i] + 50].push_back(i);

        // kisebb: azok a települések, amelyek ezen a napon szigorúan kisebb hőmérsékletűek
        bitset<1000> kisebb;
        for (auto& cs : csoport) {
            // az egyenlő értékű csoport tagjai a csoport előtti halmazzal metszhetők
            for (int i : cs) legyoz[i] &= kisebb;
            for (int i : cs) kisebb.set(i);
            cs.clear();
        }
    }

    for (int i = 0; i < n; i++) {
        if (legyoz[i].any()) {
            cout << i + 1 << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';
    return 0;
}
