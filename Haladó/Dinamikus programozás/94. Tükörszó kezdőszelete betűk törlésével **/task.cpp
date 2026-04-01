/*
Megoldás lényege:
Egy T szó legkevesebb törléssel akkor és csak akkor tehető tükörszóvá, ha T és a
fordítottja közötti, csak beszúrás/törlés műveletekkel mért szerkesztési távolság
legfeljebb 2K. Ennek oka, hogy egy leghosszabb palindrom részszekvencia mindkét
szóban közös részszekvencia, ezért:

  insdel(T, reverse(T)) = 2 * (|T| - LPS(T)).

Tehát elég eldönteni egy prefixre, hogy ez az érték <= 2K-e. Ezt nem naiv O(n^2)
DP-vel, hanem a Myers-féle O(nD) algoritmussal számoljuk, ahol D a szerkesztési
távolság. Itt csak arra van szükség, hogy D legfeljebb 2K-e, ezért az eldöntés
O(prefix_hossz * K).

Mivel ha egy prefix jó, minden rövidebb prefix is jó, binárisan kereshetjük a
leghosszabb megfelelő kezdőszeletet.

Idő: O(n * K * log n)
*/
/*
Hint 1: || A törléssel palindrommá tétel összeköthető a szó és a fordítottja közös részszekvenciájával. ||
Hint 2: || A legfeljebb K törlés ugyanaz, mint legfeljebb 2K beszúrás/törlés a fordított szóhoz képest. ||
Hint 3: || A prefixhosszra monotónia van, ezért a végső választ binárisan is keresheted. ||
*/

#include <bits/stdc++.h>

using namespace std;

static bool can_make_pal_prefix(const string& s, int len, int k) {
    if (len <= 1 || k >= len - 1) {
        return true;
    }

    string a = s.substr(0, len);
    string b = a;
    reverse(b.begin(), b.end());

    int max_d = 2 * k;
    int offset = max_d + 2;
    vector<int> v(2 * offset + 1, -1);
    v[offset + 1] = 0;

    for (int d = 0; d <= max_d; ++d) {
        for (int diag = -d; diag <= d; diag += 2) {
            int idx = offset + diag;
            int x;
            if (diag == -d || (diag != d && v[idx - 1] < v[idx + 1])) {
                x = v[idx + 1];
            } else {
                x = v[idx - 1] + 1;
            }
            int y = x - diag;
            while (x < len && y < len && a[x] == b[y]) {
                ++x;
                ++y;
            }
            v[idx] = x;
            if (x >= len && y >= len) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    string s;
    cin >> k >> s;

    int lo = 0, hi = (int)s.size(), ans = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (can_make_pal_prefix(s, mid, k)) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    cout << ans << '\n';
    return 0;
}