#include <bits/stdc++.h>
using namespace std;

/*
    A napokra érkező jelentkezők számát megszámoljuk. Ezután a pozitív
    számlálók leghosszabb összefüggő szakaszát keressük, és azon belül a
    legnagyobb értéket.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> db(m + 1);
    for (int i = 0; i < n; ++i) {
        int s;
        cin >> s;
        ++db[s];
    }

    int legjobb_hossz = 0;
    int legjobb_max = 0;
    int i = 1;
    while (i <= m) {
        while (i <= m && db[i] == 0) ++i;
        if (i > m) break;
        int j = i;
        int mx = 0;
        while (j <= m && db[j] > 0) {
            mx = max(mx, db[j]);
            ++j;
        }
        int h = j - i;
        if (h > legjobb_hossz) {
            legjobb_hossz = h;
            legjobb_max = mx;
        }
        i = j;
    }

    cout << legjobb_hossz << '\n' << legjobb_max << '\n';
    return 0;
}
