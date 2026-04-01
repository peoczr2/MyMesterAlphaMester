/*
Megoldas lenyege:
Azonos E darab dijazottat valasztunk minden versenybol. Egy adott E-re a
kirandulok azok a tanulok, akik legalabb egy versenyben az elso E helyezett
kozott vannak. Vegigprobaljuk az E erteket a lehetseges maximumig, es azt
a legnagyobb E-t tartjuk meg, amelynel a kirandulok szama nem haladja meg K-t.
*/
/*
Hint 1: || Egy E ertekhez a kirandulok halmaza a versenyek elso E helyezettjenek unioja. ||
Hint 2: || E-t kis terjedelmu, ezert vegig lehet probalni. ||
Hint 3: || A legnagyobb jo E adja a legtobb dijazottat, de meg bele kell ferjen K-ba. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, N, K;
    cin >> T >> N >> K;

    vector<vector<int>> contests(T);
    int maxAward = N;
    for (int t = 0; t < T; ++t) {
        int m;
        cin >> m;
        maxAward = min(maxAward, m);
        contests[t].resize(m);
        for (int i = 0; i < m; ++i) cin >> contests[t][i];
    }

    int bestE = 0;
    vector<int> bestSet;

    vector<int> seen(N + 1, 0);
    for (int E = 1; E <= maxAward; ++E) {
        vector<int> cur;
        for (int t = 0; t < T; ++t) {
            for (int i = 0; i < E; ++i) {
                int student = contests[t][i];
                if (seen[student] != E) {
                    seen[student] = E;
                    cur.push_back(student);
                }
            }
        }
        if ((int)cur.size() <= K) {
            bestE = E;
            bestSet = cur;
        }
    }

    sort(bestSet.begin(), bestSet.end());
    cout << bestSet.size() << '\n';
    for (int i = 0; i < (int)bestSet.size(); ++i) {
        if (i) cout << ' ';
        cout << bestSet[i];
    }
    cout << '\n';
    return 0;
}
