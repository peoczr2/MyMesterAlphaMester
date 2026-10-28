/*
Megoldás lényege:
Csak azok a napok számítanak, amelyeken a szélsebesség a [lo, hi] intervallumba esik; legyenek ezek p_1 < p_2 < ... < p_T.
Ha a verseny a p_j napon kezdődik, akkor az első K megfelelő nap a p_j, ..., p_{j+K-1}, és a közben kimaradt szünnapok
száma (p_{j+K-1} - p_j + 1) - K. Ezért a minimális szünnapszámot a K hosszú "megfelelő napokból" álló ablakok közül
a legrövidebb p_{j+K-1} - p_j adja. Szünnapról kezdeni sosem jobb, mert ugyanazt a versenyt a következő megfelelő naptól
kezdve kevesebb szünnappal is el lehet indítani. A megoldás O(N): egy menetben kiszámoljuk a legkisebb ablakot,
a második menetben kiírjuk az összes olyan kezdőnapot, amely ezt az értéket adja.
*/
/*
Hint 1: || Először csak azokat a napokat gyűjtsd össze, amelyeken a szélsebesség a megengedett tartományba esik. ||
Hint 2: || Ha egy adott megfelelő napon kezded a versenyt, a következő K megfelelő nap adja a versenynapokat; a szünnapok száma a két szélső nap távolságából számolható. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, lo, hi;
    cin >> n >> k >> lo >> hi;

    vector<int> good;
    for (int day = 1; day <= n; ++day) {
        int speed;
        cin >> speed;
        if (lo <= speed && speed <= hi) {
            good.push_back(day);
        }
    }

    int t = good.size();
    if (t < k) {
        cout << 0 << "\n";
        return 0;
    }

    int best = INT_MAX;
    for (int j = 0; j + k - 1 < t; ++j) {
        best = min(best, good[j + k - 1] - good[j]);
    }

    vector<int> starts;
    for (int j = 0; j + k - 1 < t; ++j) {
        if (good[j + k - 1] - good[j] == best) {
            starts.push_back(good[j]);
        }
    }

    cout << starts.size() << "\n";
    for (size_t i = 0; i < starts.size(); ++i) {
        if (i) cout << ' ';
        cout << starts[i];
    }
    cout << "\n";
    return 0;
}
