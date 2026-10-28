/*
Megoldás lényege:
Csúszó ablakot (kétmutatós módszert) használunk: a jobb szélt egyesével előrébb visszük, és az ablakban legfeljebb két különböző érték maradhat. Ha a bal szél és a jobb szél közötti részben már három különböző érték lenne, a bal szélt addig toljuk jobbra, amíg ismét csak két érték marad. Az ablakban az értékek darabszámát tömbben tartjuk, így a különböző értékek száma könnyen frissíthető. A válasz a legnagyobb ablakhossz. Minden elemet legfeljebb egyszer veszünk be és legfeljebb egyszer veszünk ki, így az idő O(N).
*/
/*
Hint 1: || Keress olyan folytonos szakaszt, amely legfeljebb két különböző értéket tartalmaz, és a szakasz jobb végét egyesével léptesd előre. ||
Hint 2: || Ha az ablakban három különböző érték lenne, a bal végét léptesd jobbra addig, amíg ismét csak két különböző érték marad; közben az értékek darabszámát tömbben vezesd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> s(n);
    for (int &x : s) cin >> x;

    vector<int> cnt(100001, 0);  // az ablakban lévő egyes értékek darabszáma
    int distinct = 0, l = 0, best = 0;
    for (int r = 0; r < n; r++) {
        if (cnt[s[r]]++ == 0) distinct++;
        while (distinct > 2) {
            if (--cnt[s[l]] == 0) distinct--;
            l++;
        }
        best = max(best, r - l + 1);
    }
    cout << best << "\n";
    return 0;
}
