/*
Megoldás lényege:
Mivel egy földrengés legfeljebb egy percig tart, minden földrengés egyetlen percnek tekinthető. Az összes szigetről származó időpontot egy listába gyűjtjük, és növekvő sorrendbe rendezzük. Két egymást követő időpont r1 < r2 között r2 - r1 - 1 szabad perc van; az első időpontot megelőző szakaszt a 0. perctől, az utolsó utáni szakaszt pedig M-ig számoljuk. A válasz ezek maximuma. A rendezés miatt az időigény O(R log R), ahol R legfeljebb 100 000 földrengés.
*/
/*
Hint 1: || Egy földrengés egyetlen percet foglal el, így nem kell intervallumokkal dolgozni: minden szigetről az időpontokat egy közös listába gyűjtheted. ||
Hint 2: || Rendezés után két egymást követő időpont között a szabad percek száma a két időpont különbsége - 1. Ne felejtsd el a kezdő határt (0) és a végső határt (M) sem. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    long long m;
    cin >> k >> m;

    vector<long long> moments;
    for (int i = 0; i < k; i++) {
        int f;
        cin >> f;
        for (int j = 0; j < f; j++) {
            long long r;
            cin >> r;
            moments.push_back(r);
        }
    }

    sort(moments.begin(), moments.end());

    long long best = 0;
    long long last = 0;
    for (long long r : moments) {
        best = max(best, r - last - 1);
        last = max(last, r);
    }
    best = max(best, m - last);

    cout << best << "\n";
    return 0;
}
