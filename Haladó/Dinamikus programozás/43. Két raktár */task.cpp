/*
Az összköltség felírható úgy, hogy minden áruháznak először a B raktárból szállítunk, majd pontosan M áruházat
átváltunk az A raktárra. Egy áruház A-ra váltásának többlete Ai-Bi, ezért az optimális megoldás az, hogy ezt a különbséget
tekintve a M legkisebb értékű áruházat választjuk A-hoz. Így nincs szükség bonyolult DP-re, egy rendezés elég.
*/
/*
Hint 1: || Gondold végig, mennyivel változik az összköltség, ha egy áruházat B helyett A-ból szolgálsz ki. ||
Hint 2: || Pontosan M darab A-ból szállítás kell, ezért a legkedvezőbb M különbséget kell kiválasztani. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    int total = m + n;
    vector<int> A(total + 1), B(total + 1);
    for (int i = 1; i <= total; ++i) {
        cin >> A[i];
    }
    for (int i = 1; i <= total; ++i) {
        cin >> B[i];
    }

    vector<pair<int, int>> diff;
    long long cost = 0;
    for (int i = 1; i <= total; ++i) {
        cost += B[i];
        diff.push_back({A[i] - B[i], i});
    }
    sort(diff.begin(), diff.end());

    string answer(total, 'B');
    for (int i = 0; i < m; ++i) {
        cost += diff[i].first;
        answer[diff[i].second - 1] = 'A';
    }

    cout << cost << '\n';
    cout << answer << '\n';
    return 0;
}
