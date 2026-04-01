/*
Feladat: Meg kell találni azt a H hosszú intervallumot, amelyben a legtöbb vírus volt megfigyelhető.
Ötlet: Minden vírushoz meghatározzuk, hogy a kezdőpontok mely tartományában ad hozzá egyet a fedett vírusok számához, majd különbségi tömbbel végigszámoljuk a 7000-ig tartó időtengelyt.
Hint 1: || Egy vírus pontosan azokra a kezdőidőkre számít bele, amelyekre a [T, T+H) intervallummal metszik egymást. ||
Hint 2: || Ez a kezdőidő-tartomány egy összefüggő szakasz. ||
Hint 3: || Ha minden vírushoz hozzáadod ezt a szakaszt egy diff tömbben, a maximum helye is kijön. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, h;
    cin >> n >> h;
    const int LIM = 7000;
    vector<int> diff(LIM + 3, 0);

    for (int i = 0; i < n; ++i) {
        int k, p;
        cin >> k >> p;
        int l = max(1, k - h + 1);
        int r = min(p - 1, LIM - h);
        if (l <= r) {
            ++diff[l];
            --diff[r + 1];
        }
    }

    int best = -1, bestT = 1, cur = 0;
    for (int t = 1; t <= LIM - h; ++t) {
        cur += diff[t];
        if (cur > best) {
            best = cur;
            bestT = t;
        }
    }

    cout << best << '\n' << bestT << '\n';
    return 0;
}