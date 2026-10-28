/*
Megoldás lényege:
A szótár ábécé szerinti sorrendje a betűkből épített prefixfa bejárásának felel meg: egy szó közvetlenül megelőzi a belőle hosszabbítással kapott szavakat, és a szavak az első eltérő betű szerint rendeződnek. Ezért a K-adik szót betűnként építjük fel. Dinamikus programozással kiszámoljuk, hányféle kígyózó szó kezdődik egy adott betűvel és legfeljebb adott hosszú (ways[hossz][betű]), és ezekkel a számokkal választjuk ki a következő betűt: a betűk blokkjait sorban átugorjuk, amíg a K-adik szó blokkja meg nem található. A prefix maga is szó, ezért ha a hátralévő k éppen 1, a prefix a válasz. A számlálókat 10^9 fölött levágjuk, mert K legfeljebb 10^9, így ez nem változtatja meg az eredményt. Egy kérdés O(H · 26) időben megválaszolható.
*/
/*
Hint 1: || A szótár ábécé szerinti sorrendje olyan, mint egy prefixfa bejárása: minden szó közvetlenül megelőzi a belőle hosszabbítással kapott szavakat. ||
Hint 2: || Számold meg dinamikus programozással, hány kígyózó szó kezdődik adott betűvel és legfeljebb adott hosszú (a következő betű csak az előző betű szomszédja lehet). A számlálókat 10^9 fölött levághatod, mert K legfeljebb 10^9. ||
Hint 3: || Egy kérdésnél az aktuális prefix után a betűket ábécé szerint végigvéve a k-ból kivonod az egyes betűk blokkjainak méretét, amíg a k abba a blokkba nem esik, amelyben a keresett szó van. Ha a k éppen 1, a prefix maga a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

static const long long LIM = 1000000001LL;

static bool allowed(int a, int b) {
    return abs(a - b) == 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, Q;
    cin >> H >> Q;
    vector<long long> ask(Q);
    for (int i = 0; i < Q; ++i) cin >> ask[i];

    vector<vector<long long>> ways(H + 1, vector<long long>(26, 0));
    for (int c = 0; c < 26; ++c) ways[1][c] = 1;
    for (int len = 2; len <= H; ++len) {
        for (int c = 0; c < 26; ++c) {
            long long val = 1;
            if (c > 0) val += ways[len - 1][c - 1];
            if (c + 1 < 26) val += ways[len - 1][c + 1];
            ways[len][c] = min(LIM, val);
        }
    }

    auto unrank = [&](long long k) {
        string ans;
        int rem = H;
        int last = -1;
        while (true) {
            if (!ans.empty()) {
                if (k == 1) return ans;
                --k;
            }
            bool chosen = false;
            for (int c = 0; c < 26; ++c) {
                if (last != -1 && !allowed(last, c)) continue;
                long long cnt = ways[rem][c];
                if (k > cnt) {
                    k -= cnt;
                    continue;
                }
                ans.push_back(char('a' + c));
                last = c;
                --rem;
                chosen = true;
                break;
            }
            if (!chosen) return ans;
        }
    };

    for (long long k : ask) {
        cout << unrank(k) << '\n';
    }
    return 0;
}