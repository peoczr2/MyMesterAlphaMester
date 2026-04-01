/*
   Birtokfelosztás: az N birtokot K pozitív, csökkenően rendezett részre
   bontjuk. Az I-edik felosztást lexikografikusan csökkenő sorrendben
   unrankeléssel állítjuk elő.
*/
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
static ull C[35][35];

ull countComp(int sum, int parts) {
    if (parts == 1) return 1;
    return C[sum - 1][parts - 1];
}

vector<int> unrankComp(int sum, int parts, ull rank) {
    if (parts == 1) return {sum};
    for (int first = sum - parts + 1; first >= 1; --first) {
        ull cnt = countComp(sum - first, parts - 1);
        if (rank > cnt) rank -= cnt;
        else {
            vector<int> tail = unrankComp(sum - first, parts - 1, rank);
            tail.insert(tail.begin(), first);
            return tail;
        }
    }
    return {};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int n = 0; n <= 30; ++n) {
        C[n][0] = C[n][n] = 1;
        for (int k = 1; k < n; ++k) C[n][k] = C[n - 1][k - 1] + C[n - 1][k];
    }

    int N, K;
    ull I;
    cin >> N >> K >> I;
    ull total = countComp(N, K);
    vector<int> ans = unrankComp(N, K, I);

    cout << total << '\n';
    for (int i = 0; i < K; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}