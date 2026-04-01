/*
Megoldás lényege:
Először ellenőrizzük, hogy egyáltalán létezhet-e váltakozó átrendezés: ehhez egyik betű előfordulása
sem lehet nagyobb, mint a teljes hossz felső fele. Ezután balról jobbra építjük a lexikografikusan
legkisebb megoldást.

Minden pozícióra sorban kipróbáljuk a legkisebb lehetséges betűt, amely különbözik az előzőtől, és
amelynek lerakása után a maradék multihalmazból még felépíthető valamilyen váltakozó folytatás.
*/
/*
Hint 1: || Először csak a létezést vizsgáld: a leggyakoribb betű nem lehet túl sok. ||
Hint 2: || A lexikografikusan minimális megoldás miatt mindig a legkisebb még vállalható betűt érdemes megpróbálni. ||
Hint 3: || A folytathatóság egy egyszerű gyakorisági feltételből eldönthető. ||
*/

#include <bits/stdc++.h>
using namespace std;

static bool feasible(const array<int, 26>& cnt, int prev) {
    int rem = 0;
    int maxCnt = 0;
    for (int value : cnt) {
        rem += value;
        maxCnt = max(maxCnt, value);
    }
    if (rem == 0) return true;
    if (cnt[prev] == maxCnt) {
        return maxCnt <= rem / 2;
    }
    return maxCnt <= (rem + 1) / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    array<int, 26> cnt{};
    for (char ch : s) ++cnt[ch - 'a'];

    int n = (int)s.size();
    int maxCnt = *max_element(cnt.begin(), cnt.end());
    if (maxCnt > (n + 1) / 2) {
        cout << -1 << '\n';
        return 0;
    }

    string answer;
    answer.reserve(n);
    int prev = 26;

    for (int pos = 0; pos < n; ++pos) {
        for (int c = 0; c < 26; ++c) {
            if (cnt[c] == 0 || c == prev) continue;
            --cnt[c];
            if (feasible(cnt, c)) {
                answer.push_back(char('a' + c));
                prev = c;
                break;
            }
            ++cnt[c];
        }
    }

    if ((int)answer.size() != n) {
        cout << -1 << '\n';
    } else {
        cout << answer << '\n';
    }
    return 0;
}