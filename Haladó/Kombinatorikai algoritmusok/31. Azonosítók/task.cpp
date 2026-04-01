/*
Megoldás lényege:
Az N betűből álló, M hosszú, szigorúan növekvő azonosítók lexikografikus
sorrendje megegyezik a kombinációk megszokott sorrendjével.

Először megszámoljuk az adott azonosító sorszámát, majd ehhez hozzáadjuk K-t,
és a kapott sorszámból visszaépítjük a célazonosítót.
*/

#include <bits/stdc++.h>
using namespace std;

static const long long INF = (1LL << 60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    long long K;
    if (!(cin >> N >> M >> K)) return 0;

    string s;
    cin >> s;

    vector<vector<long long>> C(27, vector<long long>(27, 0));
    for (int n = 0; n <= 26; ++n) {
        C[n][0] = C[n][n] = 1;
        for (int k = 1; k < n; ++k) {
            C[n][k] = min(INF, C[n - 1][k - 1] + C[n - 1][k]);
        }
    }

    vector<int> a(M);
    for (int i = 0; i < M; ++i) a[i] = s[i] - 'a';

    long long rank = 0;
    int prev = -1;
    for (int i = 0; i < M; ++i) {
        for (int c = prev + 1; c < a[i]; ++c) {
            rank += C[N - c - 1][M - i - 1];
        }
        prev = a[i];
    }

    long long target = rank + K;
    string ans;
    ans.reserve(M);
    prev = -1;
    for (int i = 0; i < M; ++i) {
        int rem = M - i - 1;
        for (int c = prev + 1; c <= N - rem - 1; ++c) {
            long long cnt = C[N - c - 1][rem];
            if (cnt <= target) {
                target -= cnt;
            } else {
                ans.push_back(char('a' + c));
                prev = c;
                break;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}