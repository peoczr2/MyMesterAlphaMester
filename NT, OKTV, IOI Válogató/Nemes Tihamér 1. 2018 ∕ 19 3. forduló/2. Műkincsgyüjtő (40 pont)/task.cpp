#include <bits/stdc++.h>
using namespace std;

/*
    Két képet keresünk, amelyek ára pontosan P. Az árakhoz eltároljuk az első
    előforduló indexet, majd egyetlen passzal megkeressük a komplementert.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p;
    cin >> n >> p;
    vector<int> first(p + 1, -1);
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        if (x <= p && first[x] != -1 && first[x] != i && x * 2 == p) {
            cout << first[x] << ' ' << i << '\n';
            return 0;
        }
        int need = p - x;
        if (need >= 1 && need <= p && first[need] != -1) {
            cout << first[need] << ' ' << i << '\n';
            return 0;
        }
        if (x <= p && first[x] == -1) first[x] = i;
    }
    cout << -1 << '\n';
    return 0;
}