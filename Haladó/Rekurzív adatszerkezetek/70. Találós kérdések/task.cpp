/*
Megoldási ötlet:
A kérdések egy bináris fát alkotnak, ahol az IGEN válasz +1-et, a NEM válasz -1-et jelent a címkében.
Minden kitalálandó levél címkéje tehát a gyökértől oda vezető úton kapott +1 és -1 lépések különbsége.

Elég végigjárni a fát, közben karbantartani az aktuális címkét. A leveleknél megszámoljuk, hogy melyik címke
hányszor fordul elő, majd a leggyakoribb, holtversenyben a legkisebb címkét írjuk ki.
*/
/*
Hint 1: || Egy IGEN válasz +1, egy NEM válasz -1 a címkében. ||
Hint 2: || A levelekhez érve már csak a gyakoriságot kell számolni. ||
Hint 3: || A leggyakoribb címke, egyezés esetén a legkisebb címke a válasz. ||
*/

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> yes(2 * n + 2, 0), no(2 * n + 2, 0);
    for (int i = 1; i <= n; ++i) cin >> yes[i] >> no[i];

    vector<int> count(2 * n + 3, 0);
    vector<pair<int, int>> st = {{1, 0}};
    while (!st.empty()) {
        auto [node, score] = st.back();
        st.pop_back();
        if (node > n) {
            ++count[score + n];
            continue;
        }
        st.push_back({no[node], score - 1});
        st.push_back({yes[node], score + 1});
    }

    int bestScore = 0;
    int bestCount = -1;
    for (int s = -n; s <= n; ++s) {
        int c = count[s + n];
        if (c > bestCount || (c == bestCount && s < bestScore)) {
            bestCount = c;
            bestScore = s;
        }
    }

    cout << bestScore << ' ' << bestCount << '\n';
    return 0;
}
