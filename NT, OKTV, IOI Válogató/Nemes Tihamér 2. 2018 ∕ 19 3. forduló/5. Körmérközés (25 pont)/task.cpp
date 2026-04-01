#include <bits/stdc++.h>
using namespace std;

/*
    A tournamentban egy Hamilton-út mindig felépíthető beszúrásos rendezéssel.
    Először olyan sorrendet építünk, amelyben mindenki legyőzi a közvetlenül
    utána állót, majd ezt megfordítva kapjuk meg a feladat szerinti felsorolást.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<char>> win(n + 1, vector<char>(n + 1, 0));
    for (int i = 0; i < n * (n - 1) / 2; ++i) {
        int a, b;
        cin >> a >> b;
        win[a][b] = 1;
    }

    vector<int> path;
    for (int v = 1; v <= n; ++v) {
        path.push_back(v);
        int pos = (int)path.size() - 1;
        while (pos > 0 && win[path[pos]][path[pos - 1]]) {
            swap(path[pos], path[pos - 1]);
            --pos;
        }
    }

    reverse(path.begin(), path.end());
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << '\n';
    return 0;
}