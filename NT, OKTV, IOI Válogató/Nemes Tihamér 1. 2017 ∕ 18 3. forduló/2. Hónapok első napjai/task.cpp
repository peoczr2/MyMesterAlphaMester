#include <bits/stdc++.h>
using namespace std;

/*
    Az év első napjából kiindulva végiglépünk a hónapokon, és minden hónap első
    napjának hét napos maradékát megszámoljuk. A szökőévi február 29 napos.
*/

static bool szokoev(int ev) {
    if (ev % 400 == 0) return true;
    if (ev % 100 == 0) return false;
    return ev % 4 == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int ev, s;
    cin >> ev >> s;

    vector<int> honapok = {31, 28 + (szokoev(ev) ? 1 : 0), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    array<int, 7> db{};
    int kezdo = s - 1;
    for (int napok : honapok) {
        ++db[kezdo];
        kezdo = (kezdo + napok) % 7;
    }

    for (int i = 0; i < 7; ++i) {
        if (i) cout << ' ';
        cout << db[i];
    }
    cout << '\n';
    return 0;
}