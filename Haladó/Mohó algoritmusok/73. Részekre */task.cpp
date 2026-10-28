/*
Megoldás lényege:
Dilworth-tétel szerint a legkisebb számú szigorúan növekvő részsorozatra bontás darabszáma megegyezik a leghosszabb nemnövekvő részsorozat hosszával.
A mohó eljárás sorban halad a számokon: minden x-et arra a láncra fűz, amelynek utolsó eleme a lehető legnagyobb, de még x-nél kisebb.
Ha ilyen lánc nincs, új láncot nyit. A láncok utolsó elemeit multiset tárolja, így minden lépés logaritmikus.
Időigény: O(N log N), memória: O(N).
*/
/*
Hint 1: || Egy láncban az utolsó elem < új elem feltétel kell. ||
Hint 2: || A „legszorosabb illesztés” (largest tail < x) tartja minimálisan a láncok számát. ||
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
