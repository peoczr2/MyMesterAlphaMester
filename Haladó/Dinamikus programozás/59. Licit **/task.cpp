/*
Ez klasszikus sulyozott intervallum-kivalasztas. Egy ajanlat az [A,B] parcella-intervallumot
foglalja le, es csak olyan elozo ajanlatokkal egyutt valaszthato, amelyek B < A. Mivel a bemenet
mar B szerint nemcsokkeno, minden i-re megkeresheto az utolso p[i] index, amely meg elfer az
i-edik elott. Ezutan dp[i] az elso i ajanlatbol kinyerheto legnagyobb bevetel: vagy nem valasztjuk
az i-ediket, vagy felvesszuk, es akkor dp[p[i]] + F_i jon hozza. A dontesek visszafejtesebol a
nyertes palyazok listaja is kiirhato.
*/
/*
Hint 1: || Ha egy ajanlat vegete ismert, csak az elotte teljesen befejezodo ajanlatok lehetnek mellette. ||
Hint 2: || Az i-edik ajanlatnal a klasszikus ket lehetoseg marad: kihagyjuk vagy felvesszuk. ||
Hint 3: || A p[i] index azt mondja meg, honnan lehet folytatni, ha az i-edik ajanlatot elfogadjuk. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Bid {
    int left;
    int right;
    int fee;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Bid> bids(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> bids[i].left >> bids[i].right >> bids[i].fee;
    }

    vector<int> previous(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int j = i - 1;
        while (j > 0 && bids[j].right >= bids[i].left) {
            --j;
        }
        previous[i] = j;
    }

    vector<int> dp(n + 1, 0);
    vector<char> take(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        int with_current = dp[previous[i]] + bids[i].fee;
        int without_current = dp[i - 1];
        if (with_current > without_current) {
            dp[i] = with_current;
            take[i] = true;
        } else {
            dp[i] = without_current;
        }
    }

    vector<int> answer;
    for (int i = n; i >= 1;) {
        if (take[i] && dp[i] == dp[previous[i]] + bids[i].fee) {
            answer.push_back(i);
            i = previous[i];
        } else {
            --i;
        }
    }
    reverse(answer.begin(), answer.end());

    cout << dp[n] << '\n';
    for (int i = 0; i < static_cast<int>(answer.size()); ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << answer[i];
    }
    cout << '\n';
    return 0;
}