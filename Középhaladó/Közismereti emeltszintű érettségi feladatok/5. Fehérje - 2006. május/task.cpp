/*
Megoldás lényege:
Az aminosavak tömegét az atomdarabszámok és a relatív atomtömegek szorzatainak összegeként kapjuk, a rendezést a (tömeg, rövidítés) páros szerint végezzük.
A fehérje összegképletében az aminosavak atomjait összegezzük, majd mivel n aminosav között n-1 kapcsolat jön létre és mindegyiknél egy H2O lép ki, a H-ból 2*(n-1), az O-ból (n-1) darabot levonunk.
A hasításoknál egy bejárással döntjük el a vágási helyeket: az első enzimnél az adott betűk után, a másodiknál csak akkor, ha a megelőző karakter az X, és a vágás után álló betű a megadott lista eleme.
A leghosszabb darabot az eredeti láncbeli kezdőindexével és a hosszával együtt egyetlen végigfutásban keressük meg, az első vágás előtti darabban pedig megszámoljuk a kért aminosavat.
Az időigény O(M log M + n), ami a korlátokon belül van.
*/
/*
Hint 1: || Az aminosav tömegét úgy kapod, hogy minden atomdarabszámot megszorzol a megfelelő relatív atomtömeggel, a rendezésnél pedig először a tömeg, azon belül a rövidítés szerint rendezz. ||
Hint 2: || A fehérje összegképletében az aminosavak atomjai összeadódnak, de n aminosav között n-1 kapcsolat van, ahol egy-egy vízmolekula távozik, ezért a H-ból 2*(n-1), az O-ból (n-1) darabot kell levonni. ||
Hint 3: || A hasítást karakterenként döntsd el: az első enzimnél a lista betűi után vágsz, a másodiknál a vágás csak akkor történik, ha a megelőző betű X és az aktuális betű a lista eleme; a vágás az aktuális betű után van. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long mass[5];
    for (int e = 0; e < 5; e++) cin >> mass[e];  // C, H, O, N, S

    int m;
    cin >> m;
    vector<string> abbr(m);
    vector<array<long long, 5>> cnt(m);
    map<char, int> idx;
    for (int i = 0; i < m; i++) {
        char letter;
        cin >> abbr[i] >> letter;
        for (int e = 0; e < 5; e++) cin >> cnt[i][e];
        idx[letter] = i;
    }

    string f;
    cin >> f;

    int kk;
    cin >> kk;
    set<char> cutA;
    for (int i = 0; i < kk; i++) {
        char c;
        cin >> c;
        cutA.insert(c);
    }

    int l;
    char y;
    cin >> l >> y;
    char x;
    cin >> x;
    set<char> cutB;
    for (int i = 0; i < l; i++) {
        char c;
        cin >> c;
        cutB.insert(c);
    }

    // 1. részfeladat: aminosavak relatív molekulatömege, tömeg, majd rövidítés szerint
    vector<long long> molMass(m, 0);
    for (int i = 0; i < m; i++)
        for (int e = 0; e < 5; e++) molMass[i] += cnt[i][e] * mass[e];

    vector<int> ord(m);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        if (molMass[a] != molMass[b]) return molMass[a] < molMass[b];
        return abbr[a] < abbr[b];
    });

    cout << "#\n";
    for (int i : ord) cout << abbr[i] << " " << molMass[i] << "\n";

    // 2. részfeladat: a fehérje összegképlete (vízkilépéssel csökkentve)
    long long tot[5] = {0, 0, 0, 0, 0};
    long long n = f.size();
    for (char c : f) {
        int i = idx[c];
        for (int e = 0; e < 5; e++) tot[e] += cnt[i][e];
    }
    tot[1] -= 2 * (n - 1);  // H
    tot[2] -= (n - 1);      // O

    const char *sym[5] = {"C", "H", "O", "N", "S"};
    cout << "#\n";
    bool firstAtom = true;
    for (int e = 0; e < 5; e++) {
        if (tot[e] <= 0) continue;
        if (!firstAtom) cout << " ";
        cout << sym[e] << " " << tot[e];
        firstAtom = false;
    }
    cout << "\n";

    // 3. részfeladat: a leghosszabb darab hossza és a előtte lévő aminosavak száma
    long long bestLen = -1, bestStart = 0, start = 0;
    for (long long i = 0; i < n; i++) {
        bool cutHere = (i == n - 1) || cutA.count(f[i]) > 0;
        if (cutHere) {
            long long len = i - start + 1;
            if (len > bestLen) {
                bestLen = len;
                bestStart = start;
            }
            start = i + 1;
        }
    }
    cout << "#\n" << bestLen << " " << bestStart << "\n";

    // 4. részfeladat: az első darabban a megadott aminosav előfordulásai
    long long firstEnd = n - 1;
    for (long long i = 1; i < n; i++) {
        if (f[i - 1] == x && cutB.count(f[i]) > 0) {
            firstEnd = i;
            break;
        }
    }
    long long occ = 0;
    for (long long i = 0; i <= firstEnd; i++)
        if (f[i] == y) occ++;
    cout << "#\n" << occ << "\n";
    return 0;
}
