#include <bits/stdc++.h>
using namespace std;

/*
    Minden ponthatár egy osztályzatot jelöl. Egyetlen bejárással eltároljuk
    osztályzatonként a legnagyobb pontszámot.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    int kh, hh, nh, oh;
    cin >> kh >> hh >> nh >> oh;

    array<int, 6> legjobb;
    legjobb.fill(-1);

    for (int i = 0; i < n; ++i) {
        int pont;
        cin >> pont;
        int osztalyzat;
        if (pont < kh) osztalyzat = 1;
        else if (pont < hh) osztalyzat = 2;
        else if (pont < nh) osztalyzat = 3;
        else if (pont < oh) osztalyzat = 4;
        else osztalyzat = 5;
        legjobb[osztalyzat] = max(legjobb[osztalyzat], pont);
    }

    for (int osztalyzat = 1; osztalyzat <= 5; ++osztalyzat) {
        cout << legjobb[osztalyzat] << '\n';
    }
    return 0;
}