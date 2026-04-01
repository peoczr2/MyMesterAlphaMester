/*
Legyen dp[x] az a legkevesebb belyegszam, amellyel pontosan x ertek kialakithato. Kezdetben csak
a 0 osszeg erheto el 0 belyeggel. Mivel egy cimletbol tetszoleges sok lehet, korlatlan penzvalto
jellegu DP-t futtatunk: egy cimlet C mellett dp[x] frissitheto dp[x-C] + 1-bol. Azok az ertekek
nem allithatok elo legfeljebb K belyeggel, amelyekre dp[x] > K marad.
*/
/*
Hint 1: || Nem csak azt kell tudni, hogy egy osszeg elerheto-e, hanem azt is, minimum hany belyeg kell hozza. ||
Hint 2: || Korlatlan cimletszam miatt egy cimlettel novekvo osszegsorrendben frissits. ||
Hint 3: || A vegso valaszban azok maradnak, amelyekhez tobb mint K belyeg kellene, vagy egyaltalan nem elerhetok. ||
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, limit;
    cin >> n >> k >> limit;

    const int inf = numeric_limits<int>::max() / 4;
    vector<int> dp(limit + 1, inf);
    dp[0] = 0;

    for (int i = 0; i < n; ++i) {
        int stamp;
        cin >> stamp;
        for (int value = stamp; value <= limit; ++value) {
            dp[value] = min(dp[value], dp[value - stamp] + 1);
        }
    }

    vector<int> answer;
    for (int value = 1; value <= limit; ++value) {
        if (dp[value] > k) {
            answer.push_back(value);
        }
    }

    cout << answer.size() << '\n';
    for (int i = 0; i < static_cast<int>(answer.size()); ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << answer[i];
    }
    cout << '\n';
    return 0;
}