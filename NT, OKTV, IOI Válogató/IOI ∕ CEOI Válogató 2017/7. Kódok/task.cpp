/*
Megoldás lényege:
A kód súlya a különböző szomszédos bitpárok száma + 1, vagyis lényegében a runok
száma. A hossza 3N, ezért célszerű 3 bites blokkokra bontani a sztringet.

Egy blokkra legfeljebb egy műveletet használunk: vagy a blokk első két bitjét,
vagy a blokk utolsó két bitjét fordítjuk meg. Ez a teljes stringre legfeljebb N
műveletet jelent. Balról jobbra haladva egy kételemű DP-ben tároljuk, hogy az előző
blokk utolsó bitje 0 vagy 1 volt, és minden blokkra kiválasztjuk a legjobb helyi
átalakítást. A DP a különböző szomszédos bitpárok számát maximalizálja, így a
végső súly legalább 2N lesz.
*/

#include <bits/stdc++.h>
using namespace std;

struct Prev {
    long long value = -(1LL << 60);
    int prevState = -1;
    int op = -1;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    if (!(cin >> m)) return 0;

    while (m--) {
        string s;
        cin >> s;
        int n = (int)s.size() / 3;

        array<long long, 2> dp{0, -(1LL << 60)};
        vector<array<Prev, 2>> parent(n);

        for (int i = 0; i < n; ++i) {
            int a = s[3 * i] - '0';
            int b = s[3 * i + 1] - '0';
            int c = s[3 * i + 2] - '0';

            array<long long, 2> ndp{-(1LL << 60), -(1LL << 60)};
            array<Prev, 2> best0, best1;

            auto relax = [&](int prevState, int op, int na, int nb, int nc, long long add) {
                long long cand[2] = {dp[prevState] + add, dp[prevState] + add};
                int ns = nc;
                if (cand[ns] > ndp[ns]) {
                    ndp[ns] = cand[ns];
                    parent[i][ns].value = cand[ns];
                    parent[i][ns].prevState = prevState;
                    parent[i][ns].op = op;
                }
            };

            for (int prevState = 0; prevState < 2; ++prevState) {
                if (dp[prevState] <= -(1LL << 50)) continue;

                // 0. nincs művelet
                {
                    int na = a, nb = b, nc = c;
                    long long add = (i == 0 ? (nb != nc) : (prevState != na) + (nb != nc));
                    relax(prevState, 0, na, nb, nc, add);
                }

                // 1. az első két bit fordítása
                {
                    int na = a ^ 1, nb = b ^ 1, nc = c;
                    long long add = (i == 0 ? (nb != nc) : (prevState != na) + (nb != nc));
                    relax(prevState, 3 * i + 1, na, nb, nc, add);
                }

                // 2. az utolsó két bit fordítása
                {
                    int na = a, nb = b ^ 1, nc = c ^ 1;
                    long long add = (i == 0 ? (nb != nc) : (prevState != na) + (nb != nc));
                    relax(prevState, 3 * i + 2, na, nb, nc, add);
                }
            }

            dp = ndp;
        }

        int finalState = (dp[0] >= dp[1] ? 0 : 1);
        vector<int> ops;
        for (int i = n - 1; i >= 0; --i) {
            int op = parent[i][finalState].op;
            int prevState = parent[i][finalState].prevState;
            if (op > 0) ops.push_back(op);
            finalState = prevState;
        }

        reverse(ops.begin(), ops.end());

        cout << ops.size() << '\n';
        if (!ops.empty()) {
            for (int i = 0; i < (int)ops.size(); ++i) {
                if (i) cout << ' ';
                cout << ops[i];
            }
            cout << '\n';
        }
    }

    return 0;
}