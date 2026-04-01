/*
Egy pont tavolsaganak maximuma Manhattan-metrikaban eleg a ket ismert transzformalt
koordinataval leirhato: legyen A = x + y es B = x - y. Ekkor egy p pont legtavolabbi
tavolsaga a halmaztol a negy szelso ertekhez mért maximum: max(maxA-Ap, Ap-minA,
maxB-Bp, Bp-minB). Ezert eleg egyszer vegigmenni a pontokon, meghatarozni A es B minimumat
es maximumat, majd ujra vegigmenni, es kivalasztani azt a kijelolt pontot, amelynel ez a
maximum a legkisebb. A ket legtavolabbi pont Manhattan-tavolsaga pedig
max(maxA-minA, maxB-minB).
*/
/*
Hint 1: || Manhattan-tavolsagnal hasznos az x+y es x-y atalakitas. ||
Hint 2: || Egy adott pont legtavolabbi partnere valamelyik szelso transzformalt ertekhez kotodik. ||
Hint 3: || A diameter ugyanebben az atalakitasban egyszeruen a ket tartomanyhossz maximuma. ||
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> sum_xy(n + 1);
    vector<long long> diff_xy(n + 1);
    long long min_sum = numeric_limits<long long>::max();
    long long max_sum = numeric_limits<long long>::min();
    long long min_diff = numeric_limits<long long>::max();
    long long max_diff = numeric_limits<long long>::min();

    for (int index = 1; index <= n; ++index) {
        long long x, y;
        cin >> x >> y;
        sum_xy[index] = x + y;
        diff_xy[index] = x - y;
        min_sum = min(min_sum, sum_xy[index]);
        max_sum = max(max_sum, sum_xy[index]);
        min_diff = min(min_diff, diff_xy[index]);
        max_diff = max(max_diff, diff_xy[index]);
    }

    int best_index = 1;
    long long best_radius = numeric_limits<long long>::max();
    for (int index = 1; index <= n; ++index) {
        long long radius = max(
            max(max_sum - sum_xy[index], sum_xy[index] - min_sum),
            max(max_diff - diff_xy[index], diff_xy[index] - min_diff)
        );
        if (radius < best_radius) {
            best_radius = radius;
            best_index = index;
        }
    }

    long long diameter = max(max_sum - min_sum, max_diff - min_diff);
    cout << best_index << '\n' << diameter << '\n';
    return 0;
}