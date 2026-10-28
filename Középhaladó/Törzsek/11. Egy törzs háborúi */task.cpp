/*
Megoldás lényege:
Egy adott törzs háborúinak számát kérdezzük, évszázad nélkül. Minden háborúnál megnézzük, hogy a keresett törzs a háborúzó vagy az ellenséges fél-e, és ha igen, növeljük a számlálót. A számlálás egyetlen végigmenéssel történik, így az időigény O(K), ami K ≤ 2000 mellett azonnali.
*/
/*
Hint 1: || Minden háború két törzs között zajlik: a háborúzó és az ellenséges törzs sorszáma van a sorban. Egy háború akkor érinti a keresett törzset, ha valamelyik mezőben ez a sorszám áll. ||
Hint 2: || Egyetlen végigmenéssel számláld meg azokat a sorokat, ahol a keresett törzs a két sorszám valamelyike: ehhez elég egy számláló és egy feltétel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<array<int, 4>> haboru(k);
    for (auto &h : haboru)
        cin >> h[0] >> h[1] >> h[2] >> h[3];
    int s;
    cin >> s;

    int db = 0;
    for (const auto &h : haboru)
        if (h[0] == s || h[1] == s) db++;
    cout << db << "\n";
    return 0;
}
