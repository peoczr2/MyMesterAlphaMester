/*
Megoldás lényege:
Minden állomás helyzetét az induló állomástól mért távolsággal írjuk le: ez az előzőtől mért távolságok összege. Megállónak tekintjük az induló állomást, a végállomást, valamint azokat az állomásokat, ahol az érkezési és az indulási idő különbözik. Minden állomásra végigmegyünk a megállókon (saját magát kihagyva), és a helyzetek különbségének abszolút értéke szerint kiválasztjuk a legközelebbit. Az időigény O(N^2), ami N ≤ 100 mellett bőven elfér.
*/
/*
Hint 1: || Az állomások távolságát a helyzetükből kapod: az induló állomástól mért távolság az előzőtől mért távolságok folyamatos összege. ||
Hint 2: || Egy állomás akkor megálló, ha az érkezési és indulási ideje eltér. Az induló állomást és a végállomást is számold megállónak. Minden állomásra próbáld ki az összes megállót, és tartsd meg azt, amelynek a helyzetkülönbsége a legkisebb. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> pos(n + 1, 0);
    vector<int> arr(n + 1, 0), dep(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        long long t;
        cin >> t >> arr[i] >> dep[i];
        pos[i] = pos[i - 1] + t;
    }

    vector<bool> stop(n + 1, false);
    stop[0] = true;  // az induló állomás
    for (int i = 1; i <= n; i++) {
        stop[i] = (arr[i] != dep[i]);
    }
    stop[n] = true;  // a végállomás

    for (int i = 1; i <= n; i++) {
        int best = -1;
        long long bestDist = LLONG_MAX;
        for (int j = 0; j <= n; j++) {
            if (j == i || !stop[j]) continue;
            long long d = llabs(pos[i] - pos[j]);
            if (d < bestDist) {
                bestDist = d;
                best = j;
            }
        }
        cout << best << (i == n ? '\n' : ' ');
    }
    return 0;
}
