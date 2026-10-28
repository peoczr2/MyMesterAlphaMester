/*
Megoldás lényege:
A sziget a 0-tól különböző mérések maximális összefüggő szakasza, amelynek előtte és utána is 0 áll. Az első és az utolsó mérés a kontinens fölött van, ezért az ezekhez érő szakasz nem sziget. Egy sziget szélességét a bal és a jobb part indexének különbsége adja. Egy bejárással megkeressük a szigeteket, és a szélességeiket egy halmazba tesszük; ha egy már benne lévő szélességet találunk, van két egyforma szélességű sziget, és a válasz 1. Az időigény O(N log N), a memóriaigény O(N).
*/
/*
Hint 1: || Egy sziget a pozitív mérések egy összefüggő szakasza. A két partja az a kezdő és záró mérés, amelynek a szomszédja 0, és az első vagy utolsó mérésen kezdődő szakasz nem sziget. ||
Hint 2: || Szigetenként a szélesség a két part indexének különbsége. Ezeket egy halmazba téve a duplikált szélesség a beszúrás közben kiderül, így nem kell a párokat külön párosítani. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> m(n);
    for (auto &x : m) cin >> x;

    set<int> szelessegek;  // a már talált szigetek szélességei
    bool van_egyforma = false;

    int i = 0;
    while (i < n) {
        if (m[i] == 0) {
            i++;
            continue;
        }
        int l = i;
        while (i < n && m[i] > 0) i++;
        int r = i - 1;  // a sziget [l..r] indexeken van

        if (l == 0 || r == n - 1) continue;  // a kontinenshez érő szakasz nem sziget

        int szelesseg = r - l;
        if (szelessegek.count(szelesseg)) van_egyforma = true;
        szelessegek.insert(szelesseg);
    }

    cout << (van_egyforma ? 1 : 0) << "\n";
    return 0;
}
