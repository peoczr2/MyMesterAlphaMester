/*
   Nyúl: korosztályonkénti szimuláció. Minden évben a szaporodó korú
   nyulak utódainak számát összegyűjtjük, majd az életkorokat eltoljuk.
*/
#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1000000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, L, K;
    cin >> N >> L >> K;
    vector<int> cnt(L + 1, 0), birth(L + 1, 0);
    for (int i = 1; i <= L; ++i) {
        cin >> cnt[i];
        if (i >= K) cin >> birth[i];
    }

    for (int year = 0; year < N; ++year) {
        long long newborn = 0;
        for (int age = K; age <= L; ++age) {
            newborn = (newborn + 1LL * cnt[age] * birth[age]) % MOD;
        }
        for (int age = L; age >= 2; --age) cnt[age] = cnt[age - 1];
        cnt[1] = (int)newborn;
    }

    int ans = 0;
    for (int age = 1; age <= L; ++age) ans = (ans + cnt[age]) % MOD;
    cout << ans << '\n';
    return 0;
}