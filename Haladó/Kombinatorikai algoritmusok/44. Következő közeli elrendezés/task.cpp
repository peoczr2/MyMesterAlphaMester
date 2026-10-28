/*
   Következő közeli elrendezés: a közeli permutációk pontosan azok, amelyek egymást nem fedő, szomszédos
   cserékből állnak. Minden i-hez tartozzon egy bit: 1, ha az i-edik és (i+1)-edik elem fel van cserélve,
   különben 0; két szomszédos 1-es nem állhat. A bitsorozat lexikografikus sorrendje megegyezik a
   permutációk sorrendjével, így a következő közeli permutáció a következő ilyen bitsorozat. Ezt úgy
   kapjuk, hogy a jobbról első olyan 0-t 1-re állítjuk, amelynek bal szomszédja 0, a jobb oldalát pedig
   nullázzuk; ha ilyen nincs, az identitás (1 2 … N) következik. Az időigény O(N).
*/
/*
Hint 1: || Ne magukat a permutációkat vizsgáld, hanem azt, mely szomszédos párok vannak felcserélve. Ezek a cserék nem fedhetik egymást, így minden közeli permutáció egy 0/1 sorozattal írható le. ||
Hint 2: || Olvasd a 0/1 sorozatot bináris számnak (az első pozíció a legnagyobb helyiértékű). Ekkor a lexikografikus sorrend a számok sorrendje lesz, így a következő közeli permutáció a következő olyan szám, amelyben nincs két egymás melletti 1-es. ||
Hint 3: || Keresd meg a jobbról első olyan 0-t, amelynek bal szomszédja is 0: ezt 1-re állítva, a mögötte álló biteket nullázva megkapod a következő sorozatot. Ha nincs ilyen, az identitáshoz térsz vissza. ||
*/
#include <bits/stdc++.h>
using namespace std;

static vector<int> buildPermutation(int n, const vector<int>& bits) {
    vector<int> ans;
    for (int i = 0; i < n - 1; ) {
        if (bits[i]) {
            ans.push_back(i + 2);
            ans.push_back(i + 1);
            i += 2;
        } else {
            ans.push_back(i + 1);
            ++i;
        }
    }
    if ((int)ans.size() < n) ans.push_back(n);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i];

    vector<int> bits(max(0, n - 1), 0);
    for (int i = 0; i + 1 < n; ) {
        if (p[i] == i + 1) {
            bits[i] = 0;
            ++i;
        } else {
            bits[i] = 1;
            i += 2;
        }
    }

    if (n == 1) {
        cout << 1 << '\n';
        return 0;
    }

    bool found = false;
    for (int i = n - 2; i >= 0; --i) {
        if (bits[i] == 0 && (i == 0 || bits[i - 1] == 0)) {
            bits[i] = 1;
            for (int j = i + 1; j < n - 1; ++j) bits[j] = 0;
            found = true;
            break;
        }
    }
    if (!found) fill(bits.begin(), bits.end(), 0);

    auto ans = buildPermutation(n, bits);
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}