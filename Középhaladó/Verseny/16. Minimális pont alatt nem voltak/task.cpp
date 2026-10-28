/*
Megoldás lényege:
Egy tanuló akkor kerül a kimenetbe, ha legalább egy versenyen elindult, és minden olyan versenyen, ahol indult, elérte a versenyhez tartozó minimumot. Ezért két jelzőt tartunk nyilván tanulónként: az egyik azt, hogy indult-e valahol, a másik azt, hogy volt-e olyan versenye, ahol a minimum alatt maradt. A versenyeken nem induló tanulók egyik versenyen sem kapnak eredményt, ezért a kimenetbe csak az kerül, aki indult, és sosem maradt a minimum alatt. A végén ezek sorszámát írjuk ki növekvő sorrendben, a darabszámukkal együtt. Az időigény O(N·M), ami a korlátok mellett gyors.
*/
/*
Hint 1: || Egy tanuló csak akkor felel meg, ha van olyan verseny, ahol indult. Azokat a versenyeket, ahol nem szerepel, egyáltalán nem szabad figyelembe venni. ||
Hint 2: || Versenyenként, ha egy tanuló szerepel, de a pontszáma kisebb a versenyhez tartozó minimumnál, jegyezd fel, hogy ő kiesett. A kiírás előtt azokat válogasd ki, akik szerepeltek, és sehol sem estek ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> mins(m);
    for (int i = 0; i < m; i++) {
        cin >> mins[i];
    }

    vector<bool> played(n + 1, false), failed(n + 1, false);
    for (int i = 0; i < m; i++) {
        int ind;
        cin >> ind;
        for (int j = 0; j < ind; j++) {
            int s, p;
            cin >> s >> p;
            played[s] = true;
            if (p < mins[i]) {
                failed[s] = true;
            }
        }
    }

    vector<int> ans;
    for (int s = 1; s <= n; s++) {
        if (played[s] && !failed[s]) {
            ans.push_back(s);
        }
    }

    cout << ans.size();
    for (int x : ans) {
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
