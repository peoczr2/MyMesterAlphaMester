/*
Megoldás lényege:
Egy állapotot az határoz meg, hogy eddig hány tárgyat vittünk el balról, és ehhez
legfeljebb hány tárgy vihető már el jobbról ugyanennyi kamion felhasználásával.

Legyen dp[x] = a legnagyobb olyan y, amely elérhető, ha x tárgyat már elvittünk a
bal oldalról, y tárgyat pedig a jobb oldalról az aktuális számú kamionnal. Ekkor a
megmaradt sor egy összefüggő [x+1 .. N-y] intervallum.

Egy új kamionra a megmaradt intervallum bal végéről veszünk a darab tárgyat és a jobb
végéről b darabot úgy, hogy a kiválasztott súlyok összege legfeljebb S legyen. Pozitív
súlyok miatt az összes lehetséges (a,b) pár végigpróbálható két növekvő részösszeggel.

K darab kamionon végiglépkedve mindig megtartjuk minden baloldali darabszámra a lehető
legtöbb jobbról elvihető tárgyat. A végén a max(x + dp[x]) érték a válasz.

Idő: a megoldás a ténylegesen elérhető állapotokból dolgozik; minden állapotból csak az
egy kamionra még beférő prefix/suffix kombinációkat vizsgálja.
*/
/*
Hint 1: || Ha tudod, hány tárgy fogyott el balról és jobbról, a megmaradt rész mindig egyetlen intervallum. ||
Hint 2: || Egy fix állapotból a következő kamion csak a bal oldali prefixből és a jobb oldali suffixből válogathat. ||
Hint 3: || Ugyanahhoz a balról elvitt darabszámhoz csak a legnagyobb jobboldali értéket érdemes megtartani. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, s;
    cin >> n >> k >> s;

    vector<int> w(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }

    vector<int> dp(n + 1, -1), next_dp(n + 1, -1);
    vector<int> active, next_active;
    vector<char> in_next(n + 1, 0);

    dp[0] = 0;
    active.push_back(0);

    int best = 0;

    for (int truck = 0; truck < k; ++truck) {
        fill(next_dp.begin(), next_dp.end(), -1);
        fill(in_next.begin(), in_next.end(), 0);
        next_active.clear();

        auto relax = [&](int x, int y) {
            if (x < 0 || x > n) {
                return;
            }
            if (next_dp[x] < y) {
                next_dp[x] = y;
                if (!in_next[x]) {
                    in_next[x] = 1;
                    next_active.push_back(x);
                }
            }
        };

        for (int x : active) {
            int y = dp[x];
            if (y < 0 || x + y > n) {
                continue;
            }

            relax(x, y);
            best = max(best, x + y);

            int l = x + 1;
            int r = n - y;
            if (l > r) {
                continue;
            }

            vector<int> left_sum(1, 0), right_sum(1, 0);
            while (l + (int)left_sum.size() - 1 <= r) {
                int idx = l + (int)left_sum.size() - 1;
                if (left_sum.back() + w[idx] > s) {
                    break;
                }
                left_sum.push_back(left_sum.back() + w[idx]);
            }
            while (r - ((int)right_sum.size() - 1) >= l) {
                int idx = r - ((int)right_sum.size() - 1);
                if (right_sum.back() + w[idx] > s) {
                    break;
                }
                right_sum.push_back(right_sum.back() + w[idx]);
            }

            int max_right = (int)right_sum.size() - 1;
            for (int take_left = 0; take_left < (int)left_sum.size(); ++take_left) {
                while (max_right > 0 && take_left + max_right > r - l + 1) {
                    --max_right;
                }
                while (max_right > 0 && left_sum[take_left] + right_sum[max_right] > s) {
                    --max_right;
                }
                if (take_left == 0 && max_right == 0) {
                    continue;
                }
                relax(x + take_left, y + max_right);
                best = max(best, x + take_left + y + max_right);
            }
        }

        for (int x : next_active) {
            dp[x] = next_dp[x];
        }
        active.swap(next_active);
    }

    for (int x : active) {
        best = max(best, x + dp[x]);
    }

    cout << best << '\n';
    return 0;
}