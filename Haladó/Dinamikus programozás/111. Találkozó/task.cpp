/*
Megoldási ötlet:
Ez a klasszikus „két ember egy rácson” feladat. Négy DP-t számolunk: bal felsőből az adott mezőig,
bal alsóból az adott mezőig, illetve az adott mezőtől jobb alsóba és jobb felsőbe. Így minden belső mezőre
meg tudjuk mondani, mekkora összérték érhető el, ha ott találkoznak, miközben előtte és utána nem érintenek
közös mezőt.

Egy találkozási mező körül két topológia lehetséges: az egyikben Ádám balról érkezik és lefelé megy tovább,
Éva pedig alulról érkezik és felfelé megy tovább; a másikban Ádám felülről érkezik és lefelé távozik, Éva pedig
balról érkezik és jobbra távozik. A legjobb konfiguráció kiválasztása után az eltárolt szülő- és követőmutatókból
mindkét teljes útvonal visszaépíthető.
*/
/*
Hint 1: || Négy irányból érdemes DP-t számolni: bal felső, bal alsó, jobb alsó és jobb felső felől. ||
Hint 2: || A találkozási cellát ne add hozzá a pontszámhoz; helyette a négy szomszédos részút összegét kombináld. ||
Hint 3: || Két különböző keresztezési minta van, és mindkettőt végig kell próbálni minden belső mezőre. ||
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct NextStep {
    int r = -1;
    int c = -1;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<long long>> value(n + 2, vector<long long>(m + 2, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cin >> value[i][j];
    }

    const long long negInf = -(1LL << 60);

    vector<vector<long long>> fromTL(n + 2, vector<long long>(m + 2, negInf));
    vector<vector<NextStep>> parentTL(n + 2, vector<NextStep>(m + 2));
    fromTL[1][1] = value[1][1];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i == 1 && j == 1) continue;
            if (fromTL[i - 1][j] >= fromTL[i][j - 1]) {
                fromTL[i][j] = fromTL[i - 1][j] + value[i][j];
                parentTL[i][j] = {i - 1, j};
            } else {
                fromTL[i][j] = fromTL[i][j - 1] + value[i][j];
                parentTL[i][j] = {i, j - 1};
            }
        }
    }

    vector<vector<long long>> fromBL(n + 2, vector<long long>(m + 2, negInf));
    vector<vector<NextStep>> parentBL(n + 2, vector<NextStep>(m + 2));
    fromBL[n][1] = value[n][1];
    for (int i = n; i >= 1; --i) {
        for (int j = 1; j <= m; ++j) {
            if (i == n && j == 1) continue;
            if (fromBL[i + 1][j] >= fromBL[i][j - 1]) {
                fromBL[i][j] = fromBL[i + 1][j] + value[i][j];
                parentBL[i][j] = {i + 1, j};
            } else {
                fromBL[i][j] = fromBL[i][j - 1] + value[i][j];
                parentBL[i][j] = {i, j - 1};
            }
        }
    }

    vector<vector<long long>> toBR(n + 2, vector<long long>(m + 2, negInf));
    vector<vector<NextStep>> nextBR(n + 2, vector<NextStep>(m + 2));
    toBR[n][m] = value[n][m];
    for (int i = n; i >= 1; --i) {
        for (int j = m; j >= 1; --j) {
            if (i == n && j == m) continue;
            if (toBR[i + 1][j] >= toBR[i][j + 1]) {
                toBR[i][j] = toBR[i + 1][j] + value[i][j];
                nextBR[i][j] = {i + 1, j};
            } else {
                toBR[i][j] = toBR[i][j + 1] + value[i][j];
                nextBR[i][j] = {i, j + 1};
            }
        }
    }

    vector<vector<long long>> toTR(n + 2, vector<long long>(m + 2, negInf));
    vector<vector<NextStep>> nextTR(n + 2, vector<NextStep>(m + 2));
    toTR[1][m] = value[1][m];
    for (int i = 1; i <= n; ++i) {
        for (int j = m; j >= 1; --j) {
            if (i == 1 && j == m) continue;
            if (toTR[i - 1][j] >= toTR[i][j + 1]) {
                toTR[i][j] = toTR[i - 1][j] + value[i][j];
                nextTR[i][j] = {i - 1, j};
            } else {
                toTR[i][j] = toTR[i][j + 1] + value[i][j];
                nextTR[i][j] = {i, j + 1};
            }
        }
    }

    auto buildPrefixTL = [&](int r, int c) {
        string path;
        while (!(r == 1 && c == 1)) {
            NextStep prev = parentTL[r][c];
            path.push_back(prev.r == r - 1 ? 'L' : 'J');
            r = prev.r;
            c = prev.c;
        }
        reverse(path.begin(), path.end());
        return path;
    };

    auto buildPrefixBL = [&](int r, int c) {
        string path;
        while (!(r == n && c == 1)) {
            NextStep prev = parentBL[r][c];
            path.push_back(prev.r == r + 1 ? 'F' : 'J');
            r = prev.r;
            c = prev.c;
        }
        reverse(path.begin(), path.end());
        return path;
    };

    auto buildSuffixBR = [&](int r, int c) {
        string path;
        while (!(r == n && c == m)) {
            NextStep nxt = nextBR[r][c];
            path.push_back(nxt.r == r + 1 ? 'L' : 'J');
            r = nxt.r;
            c = nxt.c;
        }
        return path;
    };

    auto buildSuffixTR = [&](int r, int c) {
        string path;
        while (!(r == 1 && c == m)) {
            NextStep nxt = nextTR[r][c];
            path.push_back(nxt.r == r - 1 ? 'F' : 'J');
            r = nxt.r;
            c = nxt.c;
        }
        return path;
    };

    long long bestValue = negInf;
    int meetR = -1;
    int meetC = -1;
    int pattern = -1;

    for (int i = 2; i <= n - 1; ++i) {
        for (int j = 2; j <= m - 1; ++j) {
            long long option1 = fromTL[i][j - 1] + toBR[i][j + 1] + fromBL[i + 1][j] + toTR[i - 1][j];
            if (option1 > bestValue) {
                bestValue = option1;
                meetR = i;
                meetC = j;
                pattern = 1;
            }

            long long option2 = fromTL[i - 1][j] + toBR[i + 1][j] + fromBL[i][j - 1] + toTR[i][j + 1];
            if (option2 > bestValue) {
                bestValue = option2;
                meetR = i;
                meetC = j;
                pattern = 2;
            }
        }
    }

    string adamPath;
    string evaPath;
    if (pattern == 1) {
        adamPath = buildPrefixTL(meetR, meetC - 1) + 'J' + 'J' + buildSuffixBR(meetR, meetC + 1);
        evaPath = buildPrefixBL(meetR + 1, meetC) + 'F' + 'F' + buildSuffixTR(meetR - 1, meetC);
    } else {
        adamPath = buildPrefixTL(meetR - 1, meetC) + 'L' + 'L' + buildSuffixBR(meetR + 1, meetC);
        evaPath = buildPrefixBL(meetR, meetC - 1) + 'J' + 'J' + buildSuffixTR(meetR, meetC + 1);
    }

    cout << bestValue << '\n';
    cout << meetR << ' ' << meetC << '\n';
    cout << adamPath << '\n';
    cout << evaPath << '\n';
    return 0;
}