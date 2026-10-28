/*
Megoldás lényege:
Mivel mindenkinek csak egy apja van, a szülő-gyerek kapcsolatok fát alkotnak, és egy ember unokái a gyermekei gyermekei. Ezért minden emberhez megszámoljuk a gyermekeit, majd az unokáinak számát úgy kapjuk, hogy a gyermekeinek gyermekszámait összeadjuk. Mivel minden unokának egy szülője van, ugyanazt az unokát nem számoljuk kétszer. A legnagyobb értéket keresve csak szigorú növekedésnél frissítünk, így döntetlennél a kisebb sorszám marad. Ha senkinek nincs unokája, a legnagyobb érték 0, és ekkor -1-et írunk ki. Az időigény O(N + M).
*/
/*
Hint 1: || Egy ember unokáinak száma egyenlő a gyermekei gyermekeinek számának összegével. Mivel mindenkinek csak egy apja van, nem számolhatsz kétszer ugyanazt az unokát. ||
Hint 2: || Tarts egy vektort a gyermekekről minden emberhez, majd minden v-re járd végig a gyermekeit, és add össze a gyermekeik számát. A maximumot szigorú nagyobbságnál frissítsd, és ha a maximum 0, akkor -1-et írj ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> children(n + 1);
    for (int i = 0; i < m; i++) {
        int a, c;
        cin >> a >> c;
        children[a].push_back(c);
    }

    int bestPerson = -1;
    int bestCount = 0;
    for (int v = 1; v <= n; v++) {
        int grandchildren = 0;
        for (int c : children[v]) grandchildren += (int)children[c].size();
        if (grandchildren > bestCount) {
            bestCount = grandchildren;
            bestPerson = v;
        }
    }

    if (bestPerson == -1) cout << -1 << "\n";
    else cout << bestPerson << " " << bestCount << "\n";
    return 0;
}
