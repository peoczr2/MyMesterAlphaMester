/*
Tetszoleges sok darab hasznalhato minden cimletbol, ezert eleg a klasszikus korlatlan
penzosszeg-elerhetoseget kiszamolni 0..M-ig. Jelolje reachable[x], hogy az x osszeg pontosan
kifizetheto-e. Kezdetben csak a 0 erheto el, majd minden cimletnel novekvo sorrendben frissitunk,
igy ugyanaz a cimlet tobbszor is felhasznalhato. A valasz azoknak az 1..M koze eso ertekeknek a
listaja, amelyekre reachable hamis marad.
*/
/*
Hint 1: || Ez korlatlan penzvalto feladat, mert minden cimletbol tetszoleges sok lehet. ||
Hint 2: || A reachable[x] allapot azt jelenti, hogy x pontosan kifizetheto. ||
Hint 3: || A frissites sorrendje fontos: korlatlan hasznalatnal novekvo osszeg szerint kell menni. ||
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, limit;
    cin >> n >> limit;

    vector<char> reachable(limit + 1, false);
    reachable[0] = true;

    for (int i = 0; i < n; ++i) {
        int coin;
        cin >> coin;
        for (int value = coin; value <= limit; ++value) {
            if (reachable[value - coin]) {
                reachable[value] = true;
            }
        }
    }

    vector<int> answer;
    for (int value = 1; value <= limit; ++value) {
        if (!reachable[value]) {
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