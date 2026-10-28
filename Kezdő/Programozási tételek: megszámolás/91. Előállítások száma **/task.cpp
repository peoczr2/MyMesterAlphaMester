/*
Megoldás lényege:
Mivel az elemek 1 és K közé esnek, elég minden értékből megszámolni, hány darab van belőle (gyakorisági tömb). Egy a < b értékpár akkor ad K-t, ha b = K - a, és ilyen párból cnt[a] * cnt[b] darab van, hiszen különböző indexű elemeket párosítunk. Ha K páros, az a = K / 2 értéknél az azonos értékű elemek közül C(cnt, 2) pár választható. Minden értékpárt pontosan egyszer számolunk, így a futásidő O(N + K), a válasz pedig 64 bites egész.
*/
/*
Hint 1: || Nem kell minden párt végigpróbálni: számold meg, hány olyan elem van, amelynek az értéke adott. Mivel az értékek 1 és K közé esnek, erre egy K + 1 hosszú tömb elég. ||
Hint 2: || Egy a < b érték párt akkor kell számolni, ha a + b = K, vagyis b = K - a. Ha K páros, az a = K / 2 esetben az azonos értékű elemek közül C(db, 2) párt lehet választani. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<long long> cnt(k + 1, 0);
    for (int i = 0; i < n; i++) {
        int s;
        cin >> s;
        cnt[s]++;
    }
    long long ans = 0;
    for (int a = 1; 2 * a < k; a++) {
        ans += cnt[a] * cnt[k - a];
    }
    if (k % 2 == 0) {
        long long c = cnt[k / 2];
        ans += c * (c - 1) / 2;
    }
    cout << ans << "\n";
    return 0;
}
