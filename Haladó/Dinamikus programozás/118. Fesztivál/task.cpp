/*
Megoldási ötlet:
Ez a súlyozott intervallum-kiválasztás klasszikus feladata. A fesztiválokat az utolsó napjuk szerint rendezzük,
és minden fesztiválhoz megkeressük az utolsó olyan előzőt, amely még nem ütközik vele, vagyis legkésőbb a kezdőnapja
előtt ér véget.

Legyen dp[i] az első i rendezett fesztiválból elérhető maximális bevétel. Ekkor vagy kihagyjuk az i-edik fesztivált,
vagy felvesszük, és hozzáadjuk dp[p(i)] értékét. A választást eltárolva a konkrét fesztivállista is visszafejthető.
*/
/*
Hint 1: || Rendezd a fesztiválokat a befejezési napjuk szerint. ||
Hint 2: || Minden fesztiválhoz keresd meg az utolsó kompatibilis előző fesztivált. ||
Hint 3: || A DP két lehetőséget hasonlít össze: kihagyás vagy kiválasztás. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Festival {
    int start;
    int finish;
    long long profit;
    int index;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Festival> festivals(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> festivals[i].start >> festivals[i].finish >> festivals[i].profit;
        festivals[i].index = i;
    }

    sort(festivals.begin() + 1, festivals.end(), [](const Festival& a, const Festival& b) {
        if (a.finish != b.finish) return a.finish < b.finish;
        return a.start < b.start;
    });

    vector<int> finishes(n + 1, 0);
    for (int i = 1; i <= n; ++i) finishes[i] = festivals[i].finish;

    vector<int> prevCompatible(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        prevCompatible[i] = static_cast<int>(upper_bound(finishes.begin() + 1, finishes.begin() + i, festivals[i].start - 1) - finishes.begin()) - 1;
    }

    vector<long long> dp(n + 1, 0);
    vector<char> take(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        long long skip = dp[i - 1];
        long long use = festivals[i].profit + dp[prevCompatible[i]];
        if (use > skip) {
            dp[i] = use;
            take[i] = 1;
        } else {
            dp[i] = skip;
        }
    }

    vector<int> chosen;
    for (int i = n; i >= 1;) {
        if (take[i] && festivals[i].profit + dp[prevCompatible[i]] == dp[i]) {
            chosen.push_back(festivals[i].index);
            i = prevCompatible[i];
        } else {
            --i;
        }
    }
    sort(chosen.begin(), chosen.end());

    cout << dp[n] << '\n';
    cout << chosen.size();
    for (int index : chosen) cout << ' ' << index;
    cout << '\n';
    return 0;
}