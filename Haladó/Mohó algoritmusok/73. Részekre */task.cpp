/*
Feladat: Egy sorozatot minimális számú növekvő részsorozatra kell bontani (nem feltétlen folytonos részekre).
Ötlet: Ez a láncfelbontás dualitása: a minimális növekvő részsorozatszám megegyezik a leghosszabb nemnövekvő részsorozat hosszával. Gyakorlatban mohó láncépítés: minden új elemet arra a láncra teszünk, amelynek utolsó eleme a lehető legnagyobb, de még kisebb nála; ha nincs ilyen, új lánc indul.
Hint 1: || Egy láncban az utolsó elem < új elem feltétel kell. ||
Hint 2: || A „legszorosabb” illesztés (largest tail < x) tartja minimálisan a láncok számát. ||
Hint 3: || A válasz a végén kialakult láncok száma. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    multiset<int> tails;
    for (int i = 0; i < N; ++i) {
        int x;
        cin >> x;
        auto it = tails.lower_bound(x);
        if (it == tails.begin()) {
            tails.insert(x);
        } else {
            --it;
            tails.erase(it);
            tails.insert(x);
        }
    }

    cout << tails.size() << '\n';
    return 0;
}
