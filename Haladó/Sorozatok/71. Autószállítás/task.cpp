/*
Megoldas lenyege:
A hajonak egy olyan osszefuggo idoszakban kell allnia, amely alatt az osszeg legalabb H.
Az elozo napok termelese nem viheto fel, es minden napi darabszam pozitiv, ezert a legrövidebb
jo szakasz ket mutatoval linearis idoben megkeresheto.

Noveljuk a jobb veget, az aktualis osszeget pedig addig csokkentjuk balrol, ameddig az meg
legalabb H marad. Igy minden jobb veghez a legbaloldalibb jo szakaszt kapjuk, es ezek kozul
valasztjuk a legrövidebbet, holtversenyben a korabban kezdodot.
*/
/*
Hint 1: || Pozitiv napi darabszamok mellett a bal veg csak jobbra mozoghat. ||
Hint 2: || Egy fix jobb veghez addig huzd jobbra a bal oldalt, amig az osszeg meg eleg nagy. ||
Hint 3: || Holtversenyben a kisebb kezdoindexet kell megtartani. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, need;
    cin >> n >> need;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    long long sum = 0;
    int left = 1;
    int bestL = -1, bestR = -1;
    for (int right = 1; right <= n; ++right) {
        sum += a[right];
        while (left <= right && sum - a[left] >= need) {
            sum -= a[left];
            ++left;
        }
        if (sum >= need) {
            if (bestL == -1 || right - left < bestR - bestL ||
                (right - left == bestR - bestL && left < bestL)) {
                bestL = left;
                bestR = right;
            }
        }
    }

    if (bestL == -1) cout << -1 << '\n';
    else cout << bestL << ' ' << bestR << '\n';
    return 0;
}