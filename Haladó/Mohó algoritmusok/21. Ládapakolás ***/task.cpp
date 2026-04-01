/*
Feladat: Egy ládasor elemeiből a lehető legkevesebb tornyot kell létrehozni úgy, hogy a tornyokban a ládák egymásba pakolási szabály szerint összevonhatók legyenek.
Ötlet: A prefixek packolhatósága a ládák egymásba pakolásának rekurzív modellje szerint vizsgálható: egy blokk akkor jó, ha a benne lévő sorozatot a szélekről egyre kisebb jó blokkokra bontva végül egyetlen elemre jutunk. Ez prefix-closed, ezért a teljes sorozatot mindig a leghosszabb még jó prefixekre vágjuk; a toronyszám ezeknek a blokkoknak a száma.
Hint 1: || A jó blokk definíciója rekurzív, és a végén egyetlen ládára kell visszavezethetőnek lennie. ||
Hint 2: || Prefix-closed tulajdonság esetén elég a leghosszabb jó prefixet keresni. ||
Hint 3: || A válasz a kivágott jó blokkok száma. ||
*/

#include <bits/stdc++.h>
using namespace std;

static bool packable(const vector<int>& a, int l, int r) {
    if (l >= r) return true;
    int mn = a[l], mx = a[l];
    for (int i = l; i <= r; ++i) {
        mn = min(mn, a[i]);
        mx = max(mx, a[i]);
    }
    return (a[l] == mn || a[l] == mx || a[r] == mn || a[r] == mx);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    int towers = 0;
    int i = 0;
    while (i < N) {
        int j = i;
        while (j + 1 < N && packable(a, i, j + 1)) ++j;
        ++towers;
        i = j + 1;
    }

    cout << towers << '\n';
    return 0;
}

