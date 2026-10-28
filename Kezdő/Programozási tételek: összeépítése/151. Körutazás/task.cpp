/*
Megoldás lényege:
Ha egy szakasz megfelel (minden városban legfeljebb K látogatás), akkor bármely részszakasza is megfelel. Ezért
kétmutatós bejárást használunk: a jobb szélt egyesével léptetjük, és városonként számoljuk a látogatásokat az
ablakban. Ha az új nap városának száma K fölé nőne, a bal szélt addig léptetjük előre, amíg ez a város ismét
legfeljebb K-szor nem szerepel. Minden lépésben az ablak hosszát összevetjük a maximummal. Minden nap legfeljebb
kétszer kerül be és ki az ablakból, így az időigény O(N), ahol N a napok száma.
*/
/*
Hint 1: || Ha egy szakasz jó, akkor bármely részszakasza is jó. Emiatt a bal szél csak előre léphet, ahogy a jobb szél nő. ||
Hint 2: || Városonként tarts számlálót az ablakban. Amikor az új nap városa K+1-re nőne, a bal szélt léptesd előre, amíg ez a város ismét K-ra nem csökken. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k; // a napok száma, városonként a megengedett legnagyobb látogatásszám
    cin >> n >> k;

    vector<int> city(n);
    for (int i = 0; i < n; i++)
        cin >> city[i];

    vector<int> cnt(n + 1, 0); // városonként az ablakban lévő látogatások száma
    int best = 0;
    int left = 0;
    for (int right = 0; right < n; right++) {
        cnt[city[right]]++;

        while (cnt[city[right]] > k) {
            cnt[city[left]]--;
            left++;
        }

        best = max(best, right - left + 1);
    }

    cout << best << '\n';
    return 0;
}
