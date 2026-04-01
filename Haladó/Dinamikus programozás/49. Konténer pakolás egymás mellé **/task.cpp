/*
Megoldás lényege:
Jelölje a konténerek eredeti helyét növekvő sorrendben p[1], p[2], ..., p[M].
Ha a végén az első foglalt hely s, akkor a konténerek csak az
s, s+1, ..., s+M-1 helyekre kerülhetnek, és az egymás melletti áttolások miatt
az eredeti sorrendjük nem változik meg. Így az összköltség:

sum |p[i] - (s + i - 1)|.

Átrendezve q[i] = p[i] - i, ezért a költség:

sum |q[i] - (s - 1)|.

Ezt az abszolút eltérések összege miatt a q sorozat mediánja minimalizálja.
Ezért elég a konténerek pozícióit összegyűjteni, a mediánt meghatározni, majd
ebből kiszámítani a minimális költséget és a legbaloldalibb végső helyet.

Idő: O(N)
*/
/*
Hint 1: || Ha a végén a konténerek egymás mellett állnak, akkor a célhelyek egy összefüggő blokkot alkotnak. ||
Hint 2: || A konténerek sorrendje nem cserélődik fel, ezért az i-edik eredeti konténert az i-edik célhelyhez érdemes párosítani. ||
Hint 3: || A p[i] - i sorozatra vezetve egy abszolútérték-összeg minimumát kapod, amit a medián ad meg. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> pos;
    pos.reserve(n);
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        if (x == 1) {
            pos.push_back(i);
        }
    }

    int m = static_cast<int>(pos.size());
    vector<long long> shifted(m);
    for (int i = 0; i < m; ++i) {
        shifted[i] = pos[i] - (i + 1);
    }

    long long base = shifted[(m - 1) / 2];
    long long answer = 0;
    for (long long value : shifted) {
        answer += llabs(value - base);
    }

    cout << answer << '\n';
    cout << base + 1 << '\n';
    return 0;
}