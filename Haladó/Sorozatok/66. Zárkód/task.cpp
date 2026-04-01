/*
Megoldas lenyege:
A legrövidebb nyitó sorozat pontosan egy K elemű abc feletti N-edrendu de Bruijn-sorozat,
majd az induló allapot visszazarasa miatt N-1 darab nullaval kiegeszitve. Ekkor minden N hosszu
kodszo pontosan egyszer szerepel az utolso N karakteres ablakok kozott.

Az osszes (N-1) hosszu szo egy csucs, es minden csucsbol K elet vezetunk a hozzafuzott uj
szamjegyekkel. Az eredmeny az Euler-kor karakterei. Hierholzer-algoritmussal linearis idoben
eloallithato, mert az elek szama K^N.
*/
/*
Hint 1: || Minden N hosszu kod pontosan egyszer kell, hogy ablakent szerepeljen. ||
Hint 2: || A csucsok az (N-1) hosszu suffixek, az elek az uj karakter hozzaadasat jelentik. ||
Hint 3: || Euler-korbol kapod a de Bruijn-sorozatot, majd a vegere N-1 darab 0 kell. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n;
    cin >> k >> n;

    vector<int> a(k * n + 1, 0);
    string cycle;

    function<void(int, int)> build = [&](int t, int p) {
        if (t > n) {
            if (n % p == 0) {
                for (int i = 1; i <= p; ++i) cycle.push_back(char('0' + a[i]));
            }
            return;
        }

        a[t] = a[t - p];
        build(t + 1, p);
        for (int digit = a[t - p] + 1; digit < k; ++digit) {
            a[t] = digit;
            build(t + 1, t);
        }
    };

    build(1, 1);

    string answer = cycle;
    answer.append(cycle.begin(), cycle.begin() + (n - 1));
    cout << answer << '\n';
    return 0;
}