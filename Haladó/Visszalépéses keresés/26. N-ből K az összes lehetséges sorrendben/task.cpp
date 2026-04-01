/*
Hungarian megoldás: az első K elemű sorrendek előállításához visszalépéssel
építjük a sorozatot, és a még nem használt számok közül választunk.

Hint 1: || A sorozat elemei különbözők, tehát egy használt jelölőtömb elég. ||
Hint 2: || Lexikografikus sorrendhez mindig a legkisebb még szabad számot próbáljuk először. ||
*/

#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> valasztott;
vector<char> hasznalt;

void dfs(int melyseg) {
    if (melyseg == k) {
        for (int i = 0; i < k; ++i) {
            if (i) cout << ' ';
            cout << valasztott[i];
        }
        cout << '\n';
        return;
    }
    for (int x = 1; x <= n; ++x) {
        if (hasznalt[x]) continue;
        hasznalt[x] = 1;
        valasztott.push_back(x);
        dfs(melyseg + 1);
        valasztott.pop_back();
        hasznalt[x] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    hasznalt.assign(n + 1, 0);
    dfs(0);
    return 0;
}