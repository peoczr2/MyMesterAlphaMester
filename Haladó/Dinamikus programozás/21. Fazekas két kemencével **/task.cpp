/*
Egy menet költsége a két kemence égetési idejének összege, mert mindkét kemence maximumát külön kell számolni.
A menet a sorban egymást követő L darab tárgyból áll (2 és 2K közötti L), és a menet legnagyobb tárgya biztosan
valamelyik kemencébe kerül. A másik kemencébe legalább max(1, L-K) tárgy kell, és ezek legyenek a lehető
legkisebbek: így a menet ára a legnagyobb tárgy plusz a többi tárgy közül a s-edik legkisebb, ahol s = max(1, L-K).
Az egész sorozat optimuma egy DP: dp[i] az első i tárgy minimális költsége, és dp[i] = min dp[i-L] + menet ára
minden 2 és 2K közötti L-re. Az időigény O(N*K^2), a memóriaigény O(N).
*/
/*
Hint 1: || Egy menet ára a két kemence maximumának összege, ezért a menet legnagyobb tárgya az egyik kemencébe kerül, a másik kemence maximumát kell minimalizálni. ||
Hint 2: || Ha a menetben L tárgy van, a másik kemencébe legalább L-K (és legalább egy) tárgy kerül, ezeket a legkisebb értékűek közül érdemes kiválasztani. ||
Hint 3: || A menetek mindig egymást követő szakaszok, ezért minden 2 és 2K közötti hosszú szakasz árát kiszámolhatod, és egy egydimenziós DP-vel összegezheted őket. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    // A [l..r] menet ára: a legnagyobb tárgy plusz a többi közül az s-edik legkisebb (s = max(1, L-K)).
    auto menet_ar = [&](int l, int r) {
        int len = r - l + 1;
        int s = max(1, len - k);
        int mpos = l;
        for (int i = l; i <= r; ++i) {
            if (a[i] > a[mpos]) {
                mpos = i;
            }
        }
        vector<int> maradek;
        for (int i = l; i <= r; ++i) {
            if (i != mpos) {
                maradek.push_back(a[i]);
            }
        }
        nth_element(maradek.begin(), maradek.begin() + (s - 1), maradek.end());
        return (long long)a[mpos] + maradek[s - 1];
    };

    const long long INF = (1LL << 60);
    vector<long long> dp(n + 1, INF);
    vector<int> prev_start(n + 1, -1);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int len = 2; len <= 2 * k && len <= i; ++len) {
            int l = i - len + 1;
            if (dp[l - 1] < INF) {
                long long cand = dp[l - 1] + menet_ar(l, i);
                if (cand < dp[i]) {
                    dp[i] = cand;
                    prev_start[i] = l;
                }
            }
        }
    }

    vector<pair<int, int>> rounds;
    for (int i = n; i > 0;) {
        int s = prev_start[i];
        rounds.push_back({s, i});
        i = s - 1;
    }
    reverse(rounds.begin(), rounds.end());

    vector<pair<int, int>> answer(n + 1);
    for (int r = 0; r < (int)rounds.size(); ++r) {
        int l = rounds[r].first, rr = rounds[r].second;
        int len = rr - l + 1;
        int s = max(1, len - k);
        int mpos = l;
        for (int i = l; i <= rr; ++i) {
            if (a[i] > a[mpos]) {
                mpos = i;
            }
        }
        vector<int> maradek;
        for (int i = l; i <= rr; ++i) {
            if (i != mpos) {
                maradek.push_back(i);
            }
        }
        sort(maradek.begin(), maradek.end(), [&](int x, int y) { return a[x] < a[y]; });
        for (int i = l; i <= rr; ++i) {
            answer[i] = {r + 1, 1};
        }
        for (int t = 0; t < s; ++t) {
            answer[maradek[t]] = {r + 1, 2};
        }
    }

    cout << dp[n] << '\n';
    for (int i = 1; i <= n; ++i) {
        cout << answer[i].first << ' ' << answer[i].second << '\n';
    }
    return 0;
}
