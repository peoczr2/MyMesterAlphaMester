/*
Feladat: A ládákat a lehető legkevesebb egymásba pakolt sorozatba kell rendezni a balról jobbra történő mozgatási szabállyal.
Ötlet: Balról jobbra haladva mindig a leginkább korlátozott nyitott sorozatba érdemes tenni az aktuális ládát. Ezzel a feladat egy rövid állapotú mohó chain-bontássá egyszerűsödik.
Hint 1: || Egy A még B-be vagy C-be is mehet, egy B pedig C-be, ezért előbb a szűkebb lehetőségeket kell kihasználni. ||
Hint 2: || Balról jobbra haladva tartsd nyilván, hány olyan nyitott sorozatod van, amely csak A-t, csak B-t, illetve már A-B-t tartalmaz. ||
Hint 3: || A C először a kész A-B sorozatokat használja, aztán a B-ket, végül az A-kat. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    int a = 0, b = 0, ab = 0, ans = 0;
    for (char c : s) {
        if (c == 'A') {
            ++a;
            ++ans;
        } else if (c == 'B') {
            if (a > 0) {
                --a;
                ++ab;
            } else {
                ++b;
                ++ans;
            }
        } else {
            if (ab > 0) {
                --ab;
            } else if (b > 0) {
                --b;
            } else if (a > 0) {
                --a;
            } else {
                ++ans;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}