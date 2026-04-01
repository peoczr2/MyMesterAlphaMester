/*
Feladat: A házakra a lehető legkevesebb WiFi eszközt kell tenni úgy, hogy minden ház lefedett legyen.
Ötlet: Balról jobbra haladva az első még nem fedett ház környezetében mindig a legjobbra tehető házra telepítünk, majd onnan fedjük le a következő házakat. Ez a klasszikus intervallumfedési mohó.
Hint 1: || Az első lefedetlen házhoz a hatótávolságon belüli legjobbra eső ház a legjobb telepítési pont. ||
Hint 2: || Onnan minden legfeljebb H távolságra lévő ház lefedődik. ||
Hint 3: || Ezután az első már nem fedett házzal folytasd. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, h;
    cin >> n >> h;
    vector<long long> r(n + 1);
    for (int i = 1; i <= n; ++i) cin >> r[i];

    vector<int> ans;
    int i = 1;
    while (i <= n) {
        int j = i;
        while (j + 1 <= n && r[j + 1] - r[i] <= h) ++j;
        int pos = j;
        while (pos + 1 <= n && r[pos + 1] - r[j] <= h) ++pos;
        ans.push_back(j);
        i = pos + 1;
    }

    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}