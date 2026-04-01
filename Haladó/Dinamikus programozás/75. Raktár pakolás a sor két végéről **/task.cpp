/*
Megoldási ötlet:
Balról és jobbról mindig csak a még bent maradt sor két széléről vehetünk el egy konténert, ezért az állapotot elég azzal leírni,
hogy eddig hányat vittünk el balról és hányat jobbról. Az aktuális kamionnál az számít, hány kamiont indítottunk már el, és mennyi
az éppen pakolt utolsó kamion terhelése.

Legyen dp[i][j] a legjobb állapot az után, hogy i konténert vittünk el balról és j-t jobbról. Innen a következő bal vagy jobb szélső
konténerrel lépünk tovább: ha még ráfér az aktuális kamionra, ugyanazt folytatjuk, különben új kamion indul. A jobb állapot az, ahol
kevesebb kamiont kellett elindítani, holtversenyben pedig kisebb az utolsó kamion terhelése.
*/
/*
Hint 1: || Az állapotot nem a maradék intervallummal, hanem az elvitt bal és jobb oldali elemek számával érdemes leírni. ||
Hint 2: || Nem kell tudni a teljes korábbi pakolási sorrendet: elég a már elindított kamionok száma és az utolsó kamion aktuális terhelése. ||
Hint 3: || Ugyanabból az állapotból a következő lépés mindig csak a bal vagy a jobb szélső konténer lehet. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct State {
    int trucks;
    int load;
    bool valid;
};

static bool better(const State& a, const State& b) {
    if (!a.valid) return false;
    if (!b.valid) return true;
    if (a.trucks != b.trucks) return a.trucks < b.trucks;
    return a.load < b.load;
}

static State advanceState(const State& cur, int weight, int cap) {
    if (!cur.valid) return {-1, -1, false};
    if (cur.load == 0) return {cur.trucks + 1, weight, true};
    if (cur.load + weight <= cap) return {cur.trucks, cur.load + weight, true};
    return {cur.trucks + 1, weight, true};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, cap;
    cin >> n >> cap;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    vector<vector<State>> dp(n + 1, vector<State>(n + 1, {-1, -1, false}));
    dp[0][0] = {0, 0, true};

    for (int removed = 0; removed < n; ++removed) {
        for (int leftCnt = 0; leftCnt <= removed; ++leftCnt) {
            int rightCnt = removed - leftCnt;
            if (leftCnt + rightCnt > n || !dp[leftCnt][rightCnt].valid) continue;

            int leftIndex = leftCnt + 1;
            int rightIndex = n - rightCnt;
            if (leftIndex > rightIndex) continue;

            State nextLeft = advanceState(dp[leftCnt][rightCnt], a[leftIndex], cap);
            if (better(nextLeft, dp[leftCnt + 1][rightCnt])) {
                dp[leftCnt + 1][rightCnt] = nextLeft;
            }

            if (leftIndex != rightIndex) {
                State nextRight = advanceState(dp[leftCnt][rightCnt], a[rightIndex], cap);
                if (better(nextRight, dp[leftCnt][rightCnt + 1])) {
                    dp[leftCnt][rightCnt + 1] = nextRight;
                }
            }
        }
    }

    State ans = {-1, -1, false};
    for (int leftCnt = 0; leftCnt <= n; ++leftCnt) {
        int rightCnt = n - leftCnt;
        if (rightCnt < 0 || rightCnt > n) continue;
        if (better(dp[leftCnt][rightCnt], ans)) ans = dp[leftCnt][rightCnt];
    }

    cout << ans.trucks << '\n';
    return 0;
}