/*
A hegymászó mozgását az aktuális állapot és a hátralévő út együtt határozza meg, ezért a választás minden lépésben a pillanatnyi környezetből adódik. A cél az, hogy mindig a következő legkedvezőbb állapotot érjük el.
*/
/*
Hint 1: || A hegymászó mindig a következő legkedvezőbb állapot felé mozdul, ezért a döntést az aktuális magasság és a hátralévő út alapján hozd meg. ||
Hint 2: || A lépések száma és a megtett távolság külön változóban érdemes, mert a cél elérését mindkettő befolyásolja. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, cap;
    cin >> n >> cap;
    vector<int> food(n - 1), need(n - 1);
    for (int i = 0; i < n - 1; ++i) cin >> food[i] >> need[i];

    vector<int> revFood = food, revNeed = need;
    reverse(revFood.begin(), revFood.end());
    reverse(revNeed.begin(), revNeed.end());

    vector<int> takeRev(n - 1, 0);
    int carry = 0;
    int reach = n;
    for (int i = 0; i < n - 1; ++i) {
        if (carry + revFood[i] < revNeed[i]) {
            reach = n - i;
            break;
        }
        int takeNow = min(revFood[i], cap - carry);
        takeRev[i] = takeNow;
        carry = carry + takeNow - revNeed[i];
    }

    if (reach == n) {
        cout << n << '\n';
        for (int i = 0; i < n - 1; ++i) {
            if (i) cout << ' ';
            cout << revFood[n - 2 - i] - takeRev[n - 2 - i];
        }
        cout << '\n';
    } else {
        cout << reach << '\n';
        for (int i = 0; i < reach - 1; ++i) {
            if (i) cout << ' ';
            cout << revFood[n - 2 - i] - takeRev[n - 2 - i];
        }
        cout << '\n';
    }
    return 0;
}