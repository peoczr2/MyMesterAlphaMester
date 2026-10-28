/*
Megoldás lényege:
A B mérés csúcs, ha 0<A<B és B>C>0, ahol A a bal, C a jobb szomszéd. Azt kell eldönteni, van-e az első felben lévő csúcs, amelynél utána csak alacsonyabb csúcsok következnek. Az első felet a sorszámból határozzuk meg: a p-edik mérés (1-től számozva) akkor van benne, ha 2p ≤ N. A csúcsokat a végüktől az elejük felé járjuk be, és nyilvántartjuk az eddig látott csúcsok legnagyobb magasságát. Ha egy első felben lévő csúcs magasabb ennél, a válasz 1. Ha utána nincs csúcs, a feltétel automatikusan teljesül. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || A csúcs feltétele a két szomszédjától függ. A válaszhoz csak a csúcsokat kell figyelembe venni, a többi mérés nem számít. ||
Hint 2: || Járd be a csúcsokat a végéről az elejéig, és tartsd nyilván az eddig látott csúcsok legnagyobb magasságát. Egy csúcs akkor jó, ha az első felben van, és magasabb a nyilvántartott maximumnál. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> m(n);
    for (auto &x : m) cin >> x;

    // A csúcsok indexei (0-tól számozva), balról jobbra.
    vector<int> csucsok;
    for (int i = 1; i + 1 < n; i++) {
        int a = m[i - 1], b = m[i], c = m[i + 1];
        if (0 < a && a < b && b > c && c > 0) csucsok.push_back(i);
    }

    int utana = -1;  // a később következő csúcsok legnagyobb magassága (-1: még nincs)
    bool van = false;
    for (int j = (int)csucsok.size() - 1; j >= 0; j--) {
        int i = csucsok[j];
        int magassag = m[i];
        int sorszam = i + 1;  // 1-től számozva
        if (2 * sorszam <= n && magassag > utana) van = true;
        utana = max(utana, magassag);
    }

    cout << (van ? 1 : 0) << "\n";
    return 0;
}
