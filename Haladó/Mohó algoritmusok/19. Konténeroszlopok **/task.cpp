/*
Feladat: A beérkező konténereket minimális számú oszlopba kell tenni úgy, hogy egy oszlopban fentről lefelé nem nőhet a célhely-sorszám.
Ötlet: Klasszikus mohó láncfelbontás: az új x konténert arra az oszlopra tesszük, amelynek teteje a legkisebb, de még >= x. Ha nincs ilyen, új oszlop indul. Ez ad minimális oszlopszámot.
Hint 1: || Ha több megfelelő oszlop teteje is >= x, mindig a „legszűkebbet” (legkisebb tetejűt) érdemes választani. ||
Hint 2: || A felső elemeket rendezett adatszerkezetben tartsd, így gyorsan megtalálod a megfelelő oszlopot. ||
Hint 3: || Minden konténerhez mentsd el az oszlopazonosítót, ez lesz a második sor kimenete. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    (void)K;

    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    multiset<pair<int,int>> tops; // (top value, column id)
    vector<int> ans(N);
    int cols = 0;

    for (int i = 0; i < N; ++i) {
        int x = a[i];
        auto it = tops.lower_bound({x, -1});
        if (it == tops.end()) {
            ++cols;
            tops.insert({x, cols});
            ans[i] = cols;
        } else {
            int id = it->second;
            tops.erase(it);
            tops.insert({x, id});
            ans[i] = id;
        }
    }

    cout << cols << '\n';
    for (int i = 0; i < N; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
