/*
Megoldas: ha van negativ szam, a minimum biztosan negativ, tehat a legtobb abszolut
erteket osszegyujtjuk, es ha kell, a legkisebb abszolut erteku negativat elhagyjuk,
hogy a paritas odd legyen. Ha nincs negativ, de van nulla, akkor a 0 a legkisebb
szorzat. Kulonben minden szam pozitiv, ekkor a legkisebb egyetlen elem a jo valasz.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> neg, pos, zero;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] < 0) neg.push_back(a[i]);
        else if (a[i] == 0) zero.push_back(a[i]);
        else pos.push_back(a[i]);
    }

    vector<int> ans;
    if (!neg.empty()) {
        int skip = -1;
        if ((int)neg.size() % 2 == 0) {
            skip = 0;
            for (int i = 1; i < (int)neg.size(); ++i) {
                if (abs(neg[i]) < abs(neg[skip])) skip = i;
            }
        }

        bool skipped = false;
        for (int x : a) {
            if (x < 0) {
                if (skip != -1 && !skipped && x == neg[skip]) {
                    skipped = true;
                    continue;
                }
                ans.push_back(x);
            } else if (x > 0) {
                ans.push_back(x);
            }
        }
    } else if (!zero.empty()) {
        ans.push_back(0);
    } else {
        int best = 0;
        for (int i = 1; i < n; ++i) {
            if (a[i] < a[best]) best = i;
        }
        ans.push_back(a[best]);
    }

    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
