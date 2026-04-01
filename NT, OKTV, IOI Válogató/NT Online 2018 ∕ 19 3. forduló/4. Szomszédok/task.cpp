#include <bits/stdc++.h>
using namespace std;

/*
    Minden településnél két mutatóval kiválasztjuk a K legközelebbi másik
    települést. Ties esetén a baloldali települést részesítjük előnyben, ahogy a
    feladat kéri.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> t(n + 1);
    for (int i = 1; i <= n; ++i) cin >> t[i];

    for (int i = 1; i <= n; ++i) {
        int l = i - 1, r = i + 1;
        int cnt = 0;
        int bal = n + 1, jobb = 0;
        while (cnt < k) {
            bool chooseLeft;
            if (l < 1) chooseLeft = false;
            else if (r > n) chooseLeft = true;
            else {
                int dl = t[i] - t[l];
                int dr = t[r] - t[i];
                chooseLeft = (dl < dr) || (dl == dr);
            }
            if (chooseLeft) {
                bal = min(bal, l);
                jobb = max(jobb, l);
                --l;
            } else {
                bal = min(bal, r);
                jobb = max(jobb, r);
                ++r;
            }
            ++cnt;
        }
        cout << bal << ' ' << jobb << '\n';
    }
    return 0;
}
