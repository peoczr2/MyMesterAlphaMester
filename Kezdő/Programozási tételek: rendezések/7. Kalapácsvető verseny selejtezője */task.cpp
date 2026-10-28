/*
Megoldás lényege:
A döntőbe mindenki bekerül, aki legalább H métert dobott; számukat jelölje cntH.
Ha ez kevesebb, mint K, a hiányzó helyeket a legjobb többi dobóval töltjük fel, így a döntősök száma max(K, cntH).
A versenyzőket dobásuk szerint csökkenő sorrendbe rendezzük (egyenlő dobásnál a kisebb sorszám kerül előre), majd kiírjuk az első max(K, cntH) sorszámot ebben a sorrendben.
A H-t elérők a rendezés után az elejére kerülnek, így a kiválasztás és a sorrend is egyszerre adódik. Az időigény O(N log N).
*/
/*
Hint 1: || Először számold meg, hányan érték el legalább H métert: ők mindenképp bekerülnek, és a döntő létszáma legalább K lesz. ||
Hint 2: || Rendezd a versenyzőket dobásuk szerint csökkenő sorrendbe (egyenlőnél a sorszám szerint), és az első max(K, cntH) versenyzőt írd ki ebben a sorrendben, elöl a létszámmal. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, h, k;
    cin >> n >> h >> k;
    vector<int> d(n);
    for (int &x : d) cin >> x;

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    stable_sort(ord.begin(), ord.end(), [&](int x, int y) { return d[x] > d[y]; });

    int cntH = 0;
    for (int x : d) if (x >= h) cntH++;
    int cnt = max(k, cntH);  // H fölött mindenki bekerül, de legalább K fő legyen

    cout << cnt;
    for (int i = 0; i < cnt; i++) cout << ' ' << ord[i] + 1;
    cout << '\n';
    return 0;
}
