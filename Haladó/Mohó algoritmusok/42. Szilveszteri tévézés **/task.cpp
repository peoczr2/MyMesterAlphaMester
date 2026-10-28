/*
Megoldás lényege:
Mivel csak teljes filmeket nézünk, két film akkor fér össze, ha az egyik befejezése nem későbbi, mint a másik kezdése (az azonos időpont megengedett). A filmeket befejezési idő szerint rendezzük, és mindig azt a filmet vesszük, amely a már kiválasztott utolsó film után még elkezdhető, és a legkorábban ér véget. Ez optimális, mert a korábban befejeződő film legalább annyi későbbi filmnek hagy helyet, mint bármely más választás. A kezdő és befejező időpontokat percre váltjuk, az időigény O(N log N).
*/
/*
Hint 1: || Csak teljes filmet nézünk, ezért két átfedő film nem választható ki egyszerre. ||
Hint 2: || A korábban befejező filmek több később kezdődő filmnek hagynak helyet. ||
Hint 3: || A kiválasztott filmek összideje csak a hosszok összege. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Movie { int s, e, id; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Movie> a(n);
    for (int i = 0; i < n; ++i) {
        int channel, ch1, cm1, ch2, cm2;
        cin >> channel >> ch1 >> cm1 >> ch2 >> cm2;
        a[i].s = ch1 * 60 + cm1;
        a[i].e = ch2 * 60 + cm2;
        a[i].id = i + 1;
    }
    sort(a.begin(), a.end(), [](const Movie &x, const Movie &y) {
        if (x.e != y.e) return x.e < y.e;
        if (x.s != y.s) return x.s < y.s;
        return x.id < y.id;
    });

    vector<int> ans;
    int last = -1;
    int total = 0;
    for (auto &m : a) {
        if (m.s >= last) {
            ans.push_back(m.id);
            total += m.e - m.s;
            last = m.e;
        }
    }

    cout << ans.size() << ' ' << total << '\n';
    for (int x : ans) cout << x << '\n';
    return 0;
}