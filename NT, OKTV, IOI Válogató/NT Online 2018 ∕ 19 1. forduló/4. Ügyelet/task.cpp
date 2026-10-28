/*
    Először minden napra megszámoljuk, hány diák jelentkezett rá. Ezután balról jobbra haladva a
    pozitív darabszámú napok összefüggő szakaszait keressük; minden szakasz hosszát és rajta a
    legnagyobb darabszámot határozzuk meg. A leghosszabb szakasz hosszát és a hozzá tartozó
    maximumot írjuk ki. Időigény O(N + M), memória O(M).
*/
/*
Hint 1: || Először számold meg minden napra, hány diák jelentkezett rá. Ezután a kérdés már csak az, hogy a pozitív darabszámú napok mely szakaszai a leghosszabbak. ||
Hint 2: || Egy szakasz a pozitív darabszámú napok egymás utáni csoportja. Balról jobbra haladva addig növeled az aktuális szakaszt, amíg a darabszám pozitív, közben nyilvántartod a szakasz hosszát és a napok legnagyobb darabszámát. ||
Hint 3: || Ha egy lezárt szakasz hossza nagyobb a mostanáig legjobbnál, frissítsd a legjobb hosszt és a hozzá tartozó maximumot. Az utolsó szakaszt se felejtsd el, ha a napok tömbje pozitív értékkel ér véget. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> db(m + 1);
    for (int i = 0; i < n; ++i) {
        int s;
        cin >> s;
        ++db[s];
    }

    int legjobb_hossz = 0;
    int legjobb_max = 0;
    int i = 1;
    while (i <= m) {
        while (i <= m && db[i] == 0) ++i;
        if (i > m) break;
        int j = i;
        int mx = 0;
        while (j <= m && db[j] > 0) {
            mx = max(mx, db[j]);
            ++j;
        }
        int h = j - i;
        if (h > legjobb_hossz) {
            legjobb_hossz = h;
            legjobb_max = mx;
        }
        i = j;
    }

    cout << legjobb_hossz << '\n' << legjobb_max << '\n';
    return 0;
}
