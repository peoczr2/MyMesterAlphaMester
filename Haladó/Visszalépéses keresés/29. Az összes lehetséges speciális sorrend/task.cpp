/*
Hungarian megoldás: az olyan permutációk, ahol minden elem legfeljebb egyet
mozdulhat el, pontosan úgy állíthatók elő, hogy vagy az i. elem önállóan áll,
vagy az i és i+1 elemet felcseréljük.

Hint 1: || Az 1..N permutációi helyett itt csak egymást nem fedő szomszédos
felcseréléseket kell választani. ||
Hint 2: || Ha az i. elemet önmagában tesszük le, i+1-től folytatjuk; ha cserélünk,
akkor i+2-től. ||
*/

#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> megoldasok;
vector<int> akt;

void dfs(int i) {
    if (i > n) {
        megoldasok.push_back(akt);
        return;
    }
    akt.push_back(i);
    dfs(i + 1);
    akt.pop_back();
    if (i + 1 <= n) {
        akt.push_back(i + 1);
        akt.push_back(i);
        dfs(i + 2);
        akt.pop_back();
        akt.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    dfs(1);
    cout << megoldasok.size() << '\n';
    for (const auto &v : megoldasok) {
        for (int i = 0; i < (int)v.size(); ++i) {
            if (i) cout << ' ';
            cout << v[i];
        }
        cout << '\n';
    }
    return 0;
}