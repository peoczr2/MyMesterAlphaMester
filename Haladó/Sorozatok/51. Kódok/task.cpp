/*
Megoldas lenyege:
A kod sulya a kulonbozo szomszedos bitparok szama + 1, vagyis eleg az atmenetek
szamat maximalizalni. A hossza 3N, ezert 3 bites blokkokra bontjuk a stringet.

Egy blokkban legfeljebb egy muveletet hasznalunk: vagy semmit nem csinalunk,
vagy az elso ket bitet, vagy az utolso ket bitet forditjuk meg. Igy osszesen legfeljebb
N muvelet lesz. Dinamikus programmal vegigprobaljuk, hogy az elozo blokk utolso bitje
0 vagy 1 volt-e, es minden blokkra kivalsztjuk a harom lehetoseg kozul azt, ami a blokk
belseji ket atmenettel es a blokkok kozti atmenettel egyutt a legtobb kulonbozo szomszedot adja.
Ha az atmenetek szama legalabb 2N-1, akkor a suly legalabb 2N.
*/
/*
Hint 1: || A suly helyett a szomszedos kulonbozo bitparok szamat maximalizald; a vegere csak +1 kerul. ||
Hint 2: || Egy 3 bites blokkban eleg 3 lehetoseget nezni: nincs lepes, bal par csereje, jobb par csereje. ||
Hint 3: || Allapotnak eleg az elozo blokk utolso bitjet tarolni, mert csak ez hat a kovetkezo blokk elejere. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct ParentState {
    int previousLastBit = -1;
    int operationPosition = 0;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> m;

    const int NEG = -1e9;

    while (m--) {
        string s;
        cin >> s;
        int n = (int)s.size() / 3;

        array<int, 2> dp = {0, NEG};
        vector<array<ParentState, 2>> parent(n);

        for (int block = 0; block < n; ++block) {
            int a = s[3 * block] - '0';
            int b = s[3 * block + 1] - '0';
            int c = s[3 * block + 2] - '0';

            array<int, 2> nextDp = {NEG, NEG};

            auto relax = [&](int previousLastBit, int operationPosition, int na, int nb, int nc) {
                int gain = (na != nb) + (nb != nc);
                if (block > 0) gain += (previousLastBit != na);

                int candidate = dp[previousLastBit] + gain;
                int nextLastBit = nc;
                if (candidate > nextDp[nextLastBit]) {
                    nextDp[nextLastBit] = candidate;
                    parent[block][nextLastBit] = {previousLastBit, operationPosition};
                }
            };

            for (int previousLastBit = 0; previousLastBit <= 1; ++previousLastBit) {
                if (dp[previousLastBit] <= NEG / 2) continue;

                relax(previousLastBit, 0, a, b, c);
                relax(previousLastBit, 3 * block + 1, a ^ 1, b ^ 1, c);
                relax(previousLastBit, 3 * block + 2, a, b ^ 1, c ^ 1);
            }

            dp = nextDp;
        }

        int lastBit = (dp[0] >= dp[1] ? 0 : 1);
        vector<int> operations;
        for (int block = n - 1; block >= 0; --block) {
            ParentState state = parent[block][lastBit];
            if (state.operationPosition != 0) operations.push_back(state.operationPosition);
            lastBit = state.previousLastBit;
        }
        reverse(operations.begin(), operations.end());

        cout << operations.size() << '\n';
        if (!operations.empty()) {
            for (int i = 0; i < (int)operations.size(); ++i) {
                if (i) cout << ' ';
                cout << operations[i];
            }
            cout << '\n';
        }
    }

    return 0;
}