/*
Megoldás lényege:
Egy szakasz sebessége a távolság (T[i]) és a menetidő hányadosa. A menetidő az előző állomásról való indulástól a következő állomásra érkezésig tart: arr[i] - dep[i-1], az induló állomásról a villamos 0. percben indul. Két sebesség összehasonlítását tört helyett kereszt-szorzással végezzük (egész számokkal, lebegőpontos pontatlanság nélkül). Egyenlőség esetén a korábbi szakasz marad. Az időigény O(N).
*/
/*
Hint 1: || Egy szakasz sebessége a megtett távolság osztva a menetidővel; nem kell tényleges osztást végezni, elég két szakasz sebességét egymáshoz arányosítani. ||
Hint 2: || Ha a/b és c/d pozitív nevezőjű törtek, akkor a/b > c/d pontosan akkor, ha a·d > c·b. Tartsd nyilván az eddigi legjobb szakasz távolságát és menetidejét, és csak a szigorúan nagyobb sebesség írja felül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> dist(n + 1, 0), arr(n + 1, 0), dep(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> dist[i] >> arr[i] >> dep[i];
    }

    int best = 1;
    long long bestDist = dist[1], bestTime = arr[1] - dep[0];
    for (int i = 2; i <= n; i++) {
        long long d = dist[i];
        long long t = arr[i] - dep[i - 1];
        // d / t > bestDist / bestTime  <=>  d * bestTime > bestDist * t
        if (d * bestTime > bestDist * t) {
            best = i;
            bestDist = d;
            bestTime = t;
        }
    }

    cout << best - 1 << ' ' << best << '\n';
    return 0;
}
