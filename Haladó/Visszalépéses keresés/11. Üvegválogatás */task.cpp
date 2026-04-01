/*
Hungarian megoldás: minden üvegtípushoz külön kiválasztjuk azt a ládát, ahol a
legtöbb azonos típusú üveg már eleve benne van.

Hint 1: || Egy üvegtípus átrakási költsége csak attól függ, melyik ládát jelöljük ki neki. ||
Hint 2: || A típusok egymástól függetlenül optimalizálhatók. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<vector<int>> a(n, vector<int>(k));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) cin >> a[i][j];
    }
    vector<long long> ossz(k);
    for (int j = 0; j < k; ++j) for (int i = 0; i < n; ++i) ossz[j] += a[i][j];
    long long moves = 0;
    vector<int> valaszt(k);
    for (int j = 0; j < k; ++j) {
        int best = 0;
        for (int i = 1; i < n; ++i) if (a[i][j] > a[best][j]) best = i;
        valaszt[j] = best + 1;
        moves += ossz[j] - a[best][j];
    }
    cout << moves << '\n';
    for (int j = 0; j < k; ++j) {
        if (j) cout << ' ';
        cout << valaszt[j];
    }
    cout << '\n';
    return 0;
}