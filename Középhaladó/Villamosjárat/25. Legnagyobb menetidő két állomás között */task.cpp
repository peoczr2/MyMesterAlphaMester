/*
Megoldás lényege:
Két szomszédos állomás közötti menetidő az előző állomásról való indulás és a következő állomásra való érkezés közti idő: arr[i] - dep[i-1], ahol az induló állomásról a villamos 0. percben indul (dep[0] = 0). Egyetlen végigolvasással megkeressük a legnagyobb menetidőt; egyenlőség esetén az első, vagyis a legkisebb sorszámú pár marad. Az időigény O(N).
*/
/*
Hint 1: || A kérdés két szomszédos állomásra vonatkozik: egy szakasz menetideje az előző állomásról való indulás és a következő állomásra való érkezés közti idő. ||
Hint 2: || Tartsd nyilván az eddigi legnagyobb menetidőt és a hozzá tartozó állomás sorszámát; csak a szigorúan nagyobb érték írja felül. Az induló állomás indulási ideje 0. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> arr(n + 1, 0), dep(n + 1, 0);  // dep[0] = 0: a villamos a 0. percben indul
    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t >> arr[i] >> dep[i];
    }

    int bestIdx = 1, bestTime = -1;
    for (int i = 1; i <= n; i++) {
        int time = arr[i] - dep[i - 1];
        if (time > bestTime) {
            bestTime = time;
            bestIdx = i;
        }
    }

    cout << bestIdx - 1 << ' ' << bestIdx << '\n';
    return 0;
}
