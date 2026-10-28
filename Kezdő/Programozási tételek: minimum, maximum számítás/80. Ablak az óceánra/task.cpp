/*
Megoldás lényege: Az ablak felső széle a tengerszint alatt 1 méterrel van, így egy oszlop fölött legfeljebb M_i - 1 méter magas ablak fér el. A feladat tehát a hisztogramban a legnagyobb téglalap keresése, ahol az oszlopok magassága M_i - 1, és az ablak folytonos oszlopszakaszon áll. Ezt egy monoton veremmel oldjuk meg: amikor egy oszlop kikerül a veremből, a bal és a jobb oldali első alacsonyabb oszlop adja a maximális szélességet az ő magasságához. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Minden oszlopra gondold végig, hogy az 1 méter mélységű felső élről legfeljebb mekkora magas ablak fér el: ez a tengerfenék mélysége mínusz egy. ||
Hint 2: || Minden oszlophoz keresd meg, meddig terjedhet az ablak úgy, hogy az oszlop magassága még ne csökkenjen: a bal és a jobb oldali első alacsonyabb oszlop adja a határt. Ezt egyetlen menetben egy verem segítségével kiszámolhatod. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> h(n + 1, 0);
    for (int i = 0; i < n; i++) {
        long long m;
        cin >> m;
        h[i] = m - 1;
    }
    h[n] = 0;

    vector<int> st;
    long long best = 0;
    for (int i = 0; i <= n; i++) {
        while (!st.empty() && h[st.back()] >= h[i]) {
            long long height = h[st.back()];
            st.pop_back();
            int left = st.empty() ? 0 : st.back() + 1;
            best = max(best, height * (i - left));
        }
        st.push_back(i);
    }
    cout << best << "\n";
    return 0;
}
