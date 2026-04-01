/*
Megoldas lenyege:
Harom utat kell valasztani ugy, hogy az osszeg legfeljebb F legyen, es minel kozelebb essen F-hez.
Mivel az arak nemcsokkenok, egy fix elso ut mellett a maradek ket ut legjobb parja ket mutatoval
megtalalhato.

Vegigprobaljuk az elso indexet i, majd a maradek tartomanyon bal/jobb mutatoval keressuk a
leheto legnagyobb, de F-et nem tullepo osszeget. Ha uj legjobb osszeget kapunk, elmentjuk a
harom indexet. Holtversenyben barmelyik jo.
*/
/*
Hint 1: || A bemenet rendezett, ezert a maradek ket elemre ket mutato hasznalhato. ||
Hint 2: || Ha a harom elem osszege belefer, probald novelni; ha nem fer bele, csokkenteni kell. ||
Hint 3: || A maximum megengedett osszeghez legkozelebbi, de nem nagyobb harmast keresed. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long budget;
    cin >> n >> budget;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    long long bestSum = -1;
    array<int, 3> best = {-1, -1, -1};

    for (int i = 1; i <= n - 2; ++i) {
        int left = i + 1, right = n;
        while (left < right) {
            long long sum = a[i] + a[left] + a[right];
            if (sum <= budget) {
                if (sum > bestSum) {
                    bestSum = sum;
                    best = {i, left, right};
                }
                ++left;
            } else {
                --right;
            }
        }
    }

    if (bestSum == -1) cout << -1 << '\n';
    else cout << best[0] << ' ' << best[1] << ' ' << best[2] << '\n';
    return 0;
}