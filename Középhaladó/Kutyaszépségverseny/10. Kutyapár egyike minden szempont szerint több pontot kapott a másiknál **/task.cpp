/*
Megoldás lényege:
A kérdés minden kutyapárra vonatkozik, a kiesettség nem számít. Az A kutya akkor kapott minden szempont szerint több pontot, mint B, ha minden szempontban szigorúan nagyobb a pontszáma.
Ezért minden (A, B) párra végigmegyünk a szempontokon, és ha valahol A pontszáma nem nagyobb B-énél, a pár nem jó. Ha van jó pár, a válasz VAN, különben NINCS.
Az idő O(N² · M), a memóriaigény O(N · M).
*/
/*
Hint 1: || Az (A, B) párt akkor kell elfogadni, ha A minden szempontban szigorúan több pontot kapott B-nél. Az alsó és felső határokra ehhez nincs szükség. ||
Hint 2: || Két egymásba ágyazott ciklussal bejárhatod az összes (A, B) párt, a belső ciklusban pedig a szempontokat. Ha valahol A pontszáma nem nagyobb B-énél, a belső ciklust félbeszakíthatod és a következő párra léphetsz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> maxPont(m), minPont(m);
    for (int &x : maxPont) cin >> x;
    for (int &x : minPont) cin >> x;

    vector<vector<int>> p(n, vector<int>(m));
    for (auto &sor : p)
        for (int &x : sor) cin >> x;

    bool van = false;
    for (int a = 0; a < n && !van; a++) {
        for (int b = 0; b < n && !van; b++) {
            if (a == b) continue;
            bool minden = true;
            for (int i = 0; i < m; i++)
                if (p[a][i] <= p[b][i]) {
                    minden = false;
                    break;
                }
            if (minden) van = true;
        }
    }

    cout << (van ? "VAN" : "NINCS") << '\n';
    return 0;
}
