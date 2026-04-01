/*
Megoldási ötlet:
A rajz szélességét a levelek sorrendje határozza meg. Ha a leveleket balról jobbra
egymás után helyezzük el, akkor minden belső csomópont pozíciója automatikusan a
bal és jobb gyerek pozíciójának közepe lesz, tehát a feltételek teljesülnek.

Ezért elég megszámolni a leveleket. Ha L a levelek száma, akkor a legkisebb
lehetséges legnagyobb pozíció az L érték, mert a leveleknek legalább ennyi
különböző helyre kell kerülniük, és ez a konstrukció el is éri ezt.

Hint 1: || A zárójelezett fa minden belső csúcsán pontosan két gyerek van, tehát a fa teljes bináris fa. ||
Hint 2: || Egy ilyen fa balról jobbra rajzolva a levelek száma adja a szükséges oszlopok számát. ||
Hint 3: || A keresett maximum pozíció ezért egyszerűen a levelek száma mínusz egy. ||
*/

#include <bits/stdc++.h>
using namespace std;

string s;
int pos;

int parse() {
    if (pos >= (int)s.size()) return 0;
    ++pos; // a csomópont betűjele
    if (pos < (int)s.size() && s[pos] == '(') {
        ++pos; // (
        int leftLeaves = parse();
        ++pos; // ,
        int rightLeaves = parse();
        ++pos; // )
        return leftLeaves + rightLeaves;
    }
    return 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    pos = 0;
    int leaves = parse();
    cout << leaves << '\n';
    return 0;
}