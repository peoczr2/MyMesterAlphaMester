/*
Ez is sulyozott intervallum-kivalasztas, csak itt a palyazatok nincsenek rendezve, es a meretek
nagyobbak. Eloszor a palyazatokat jobb vegpont szerint rendezzuk, es minden ajanlathoz megkeressuk
az utolso kompatibilis elodot, amelynek a jobb vege kisebb a mostani bal vegebenel. Legyen dp[i]
az elso i rendezett ajanlatbol kinyerheto legnagyobb bevetel; ekkor dp[i] = max(dp[i-1],
dp[p[i]] + ertek_i). A szulo-informacio alapjan a nyertes palyazok eredeti sorszamai visszaepithetok.
*/
/*
Hint 1: || A palyazatokat jobb vegpont szerint rendezd, kulonben nem lehet gyorsan kompatibilis elodot keresni. ||
Hint 2: || Az i-edik ajanlatnal ugyanaz a ket eset van: kimarad, vagy osszefuzodik a legutolso jo eloddal. ||
Hint 3: || A visszaepiteshez az eredeti sorszamot is el kell menteni a rendezett lista elemeihez. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Bid {
    int left;
    int right;
    int fee;
    int index;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Bid> bids(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> bids[i].left >> bids[i].right >> bids[i].fee;
        if (bids[i].left > bids[i].right) {
            swap(bids[i].left, bids[i].right);
        }
        bids[i].index = i;
    }

    sort(bids.begin() + 1, bids.end(), [](const Bid& left, const Bid& right) {
        if (left.right != right.right) {
            return left.right < right.right;
        }
        if (left.left != right.left) {
            return left.left < right.left;
        }
        return left.index < right.index;
    });

    vector<int> ends(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        ends[i] = bids[i].right;
    }

    vector<int> previous(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        previous[i] = static_cast<int>(lower_bound(ends.begin() + 1, ends.begin() + i, bids[i].left) - ends.begin()) - 1;
    }

    vector<long long> dp(n + 1, 0);
    vector<char> take(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        long long with_current = dp[previous[i]] + bids[i].fee;
        long long without_current = dp[i - 1];
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
            answer.push_back(bids[i].index);
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