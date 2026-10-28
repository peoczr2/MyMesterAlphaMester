/*
Megoldás lényege:
Egy láda csak nála nagyobb szomszédjába pakolható be, ezért az a láda, amely minden szomszédjánál nagyobb (a széleken az egyetlen szomszédjánál), nem kerülhet máshova: ezek a helyi maximumok, és mindegyik külön ládában marad. Minden más láda beleférhet egy nála nagyobb szomszédjába, így a végső ládák száma pontosan a helyi maximumok száma. A minták (például 3 4 7 2 1 5 8 6, ahol a 7 és a 8 a helyi maximum, a válasz 2) is ezt mutatják. A megoldás egyetlen bejárással, O(N) időben számolja a helyi maximumokat.
*/
/*
Hint 1: || Próbáld ki kézzel a 3 4 7 2 1 5 8 6 sorozaton: mely ládák azok, amelyek minden szomszédjuknál nagyobbak? Ezek nem pakolhatók be sehová, a többi igen. ||
Hint 2: || Minden ládára elég a bal és a jobb szomszédját megnézni: ha mindkettőnél nagyobb, növeld a számlálót eggyel. A szélső ládáknál a hiányzó szomszédot hagyd figyelmen kívül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    int maxima = 0;
    for (int i = 0; i < n; i++) {
        bool greaterThanLeft = (i == 0) || a[i] > a[i - 1];
        bool greaterThanRight = (i == n - 1) || a[i] > a[i + 1];
        if (greaterThanLeft && greaterThanRight) {
            maxima++;
        }
    }

    cout << maxima << '\n';
    return 0;
}
