/*
A vizitúra értéke a szakaszok időtartamaiból áll össze, ezért a különbségeket és a várakozással megtoldott indulási időket kell követni. A teljes eredmény egy idővonalon végigszimulált menetből adódik.
*/
/*
Hint 1: || A túra eredménye a szakaszok időtartamának összege, ezért a sorozat különbségeit kell figyelni. ||
Hint 2: || Ha több szakasz is várakozást okoz, a következő indulási idő a legkésőbbi érkezésből adódik. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, h;
    cin >> n >> h;
    vector<int> food(n - 1), need(n - 1);
    for (int i = 0; i < n - 1; ++i) cin >> food[i] >> need[i];

    vector<int> required(n, 0);
    for (int i = n - 2; i >= 0; --i) {
        required[i] = max(0, need[i] + required[i + 1] - food[i]);
    }

    vector<int> take(n - 1, 0);
    int carry = 0;
    int reach = n;
    for (int i = 0; i < n - 1; ++i) {
        int target = need[i] + required[i + 1];
        int add = max(0, target - carry);
        if (carry + add > h || add > food[i]) {
            reach = i + 1;
            break;
        }
        take[i] = add;
        carry += add - need[i];
    }

    if (reach == n) {
        for (int i = 0; i < n - 1; ++i) {
            if (i) cout << ' ';
            cout << take[i];
        }
        cout << '\n';
    } else {
        cout << reach << '\n';
    }
    return 0;
}