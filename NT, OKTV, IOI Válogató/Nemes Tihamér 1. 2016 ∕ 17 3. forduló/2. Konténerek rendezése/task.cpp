#include <bits/stdc++.h>
using namespace std;

/*
    A kisebb konténerek mindig rátehetők a nagyobbakra, ezért egy konténer
    útjában álló kisebb blokkolókat ugyanabba az irányba toljuk tovább, amíg a
    mozgatni kívánt konténer el nem jut a célhelyére. A feldolgozást csökkenő
    méret szerint végezzük, így a már a helyükre került nagyobb konténereket a
    kisebbek nem tudják megzavarni.
*/

int n;
vector<vector<int>> rakas;
vector<pair<int, char>> muveletek;

int keres(int k) {
    for (int i = 1; i <= n + 1; ++i) {
        for (int x : rakas[i]) {
            if (x == k) return i;
        }
    }
    return -1;
}

void csucs_mozgat(int honnan, int irany) {
    int hova = honnan + irany;
    int mozgo = rakas[honnan].back();
    while (!rakas[hova].empty() && rakas[hova].back() < mozgo) {
        if ((hova == 1 && irany == -1) || (hova == n + 1 && irany == 1)) {
            csucs_mozgat(hova, -irany);
        } else {
            csucs_mozgat(hova, irany);
        }
    }
    rakas[honnan].pop_back();
    rakas[hova].push_back(mozgo);
    muveletek.push_back({honnan, irany == -1 ? 'B' : 'J'});
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    vector<int> kezdo(n + 1);
    for (int i = 1; i <= n; ++i) cin >> kezdo[i];

    rakas.assign(n + 2, {});
    for (int i = 1; i <= n; ++i) rakas[i].push_back(kezdo[i]);

    for (int k = n; k >= 1; --k) {
        int pos = keres(k);
        while (pos != k) {
            int irany = (pos < k ? 1 : -1);
            while (rakas[pos].back() != k) {
                csucs_mozgat(pos, irany);
            }
            csucs_mozgat(pos, irany);
            pos += irany;
        }
    }

    for (auto [p, c] : muveletek) {
        cout << p << ' ' << c << '\n';
    }
    return 0;
}