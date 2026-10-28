/*
Megoldás lényege:
A szigetek a 0-tól különböző mérések összefüggő szakaszai; az első és az utolsó szakasz a kontinenshez tartozik, ezeket kihagyjuk. Csúcs az a mérés, amelynek mindkét szomszédja pozitív, a bal oldali szomszédja kisebb nála, a jobb oldali szomszédja pedig szigorúan kisebb nála. Szigetenként megkeressük a legnagyobb magasságot, és ellenőrizzük, hogy az ilyen értékű mérések mindegyike csúcs-e; ha valamelyik nem az, a válasz 0. Ha több azonos legmagasabb pont van, mindegyiknek csúcsnak kell lennie. Ha nincs sziget, a feltétel üresen teljesül, így a válasz 1. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Csúcs az a mérés, amelynek mindkét szomszédja pozitív, a bal oldali szomszédja kisebb nála, a jobb oldali szomszédja pedig szigorúan kisebb nála. A kontinenshez érő szakaszok most sem számítanak. ||
Hint 2: || Szigetenként keresd meg a legnagyobb mérést, és nézd meg a sziget minden olyan pontját, ahol ez az érték áll. Ha közülük bármelyik nem csúcs, a válasz 0. ||
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

    // csúcs: mindkét szomszédja pozitív, a bal szomszédja kisebb, a jobb szomszédja szigorúan kisebb
    auto csucs = [&](int j) {
        return j > 0 && j + 1 < n && m[j - 1] > 0 && m[j - 1] < m[j] && m[j + 1] > 0 && m[j] > m[j + 1];
    };

    bool minden = true;  // marad igaz, ha minden sziget legmagasabb pontjai csúcsok

    int i = 0;
    while (i < n) {
        if (m[i] == 0) {
            i++;
            continue;
        }
        int l = i;
        while (i < n && m[i] > 0) i++;
        int r = i - 1;  // a sziget [l..r] indexei (0-tól számozva)

        if (l == 0 || r == n - 1) continue;  // a kontinenshez érő szakasz nem sziget

        int legmagasabb = *max_element(m.begin() + l, m.begin() + r + 1);
        for (int j = l; j <= r; j++) {
            if (m[j] == legmagasabb && !csucs(j)) minden = false;
        }
    }

    cout << (minden ? 1 : 0) << "\n";
    return 0;
}
