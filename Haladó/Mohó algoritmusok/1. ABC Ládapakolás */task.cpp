/*
Feladat: A ládákat a lehető legkevesebb egymásba pakolt sorozatba kell rendezni a balról jobbra történő mozgatási szabállyal.
Ötlet: Egy láda csak nála nagyobb, tőle jobbra lévő ládába kerülhet, ezért egy egymásba pakolt lánc balról jobbra szigorúan növekvő méretű (C, B, A sorrendben). A láncok minimális száma (Dilworth-tétel) megegyezik a páronként egymásba nem pakolható ládák maximális számával, vagyis a leghosszabb olyan részsorozat hosszával, amelyben balról jobbra a méret nem nő (A…A B…B C…C alak). Ezt O(N) időben három állapotú DP-vel számoljuk.
*/
/*
Hint 1: || Két láda akkor nem pakolható egymásba, ha a bal oldali nem kisebb, mint a jobb oldali. ||
Hint 2: || Keress olyan ládákat, amelyek közül egyik sem pakolható a másikba: ezek száma alsó korlátot ad a láncok számára (Dilworth-tétel). ||
Hint 3: || Balról jobbra haladva három értéket tarts nyilván: a leghosszabb A-sorozat, az A*B* és az A*B*C* részsorozat hosszát. Minden láda csak ezeket frissíti. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    int a = 0, ab = 0, abc = 0;
    for (char c : s) {
        if (c == 'A') {
            ++a;
            ab = max(ab, a);
            abc = max(abc, ab);
        } else if (c == 'B') {
            ++ab;
            abc = max(abc, ab);
        } else {
            ++abc;
        }
    }

    cout << abc << '\n';
    return 0;
}
