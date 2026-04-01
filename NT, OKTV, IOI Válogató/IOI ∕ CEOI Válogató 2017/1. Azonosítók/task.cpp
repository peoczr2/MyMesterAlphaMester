/*
Megoldás lényege:
A feladatban csak olyan azonosítók vannak, amelyek az első N kisbetűből állnak,
M hosszúak, és a karakterek szigorúan növekvő sorrendben szerepelnek bennük.
Ezek lexikografikus sorrendje megegyezik a kombinációk szokásos sorrendjével.

Először kiszámítjuk az input azonosító sorszámát: minden pozíción megnézzük, hány
olyan azonosító van, amely ugyanott kisebb karaktert használ, és a maradék helyeket
a lehető legkisebben tölti ki. Ezután ehhez hozzáadjuk K-t, végül a kapott sorszám
alapján visszaépítjük a célazonosítót.

Mivel N legfeljebb 26, a binomiális együtthatókat előre ki lehet számolni.
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