#include <bits/stdc++.h>
using namespace std;

/*
    Ha egy bázis hiányzik egy K hosszú szakaszból, akkor a szakasz hossza legfeljebb
    az adott bázis két szomszédos előfordulása közti lyuk. Ezért elég minden bázisra
    megkeresni a leghosszabb hiányzó részt.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int ans = 0;
    string b = "ACGT";
    for (char c : b) {
        int last = -1, best = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            if (s[i] == c) {
                best = max(best, i - last - 1);
                last = i;
            }
        }
        best = max(best, (int)s.size() - last - 1);
        ans = max(ans, best + 1);
    }

    cout << ans << '\n';
    return 0;
}