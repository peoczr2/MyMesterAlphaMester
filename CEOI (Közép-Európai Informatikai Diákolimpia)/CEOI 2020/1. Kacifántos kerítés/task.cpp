/*
Megoldás lényege:
A kerítés minden i. elemét w_i darab, egységnyi széles oszlopnak tekintjük, így egy téglalap x-irányban
egy folytonos oszloptartomány, y-irányban pedig egy 0 ≤ y1 < y2 ≤ m egész pár, ahol m a tartomány legalacsonyabb
magassága. Egy m magasságú oszlopon m(m+1)/2 ilyen párt választhatunk. Minden oszloptartományt pontosan egy elem
viszi el: a legalacsonyabb elem (ha több is van, a balról első). Az i. elem tartományát monoton veremmel kapjuk meg:
balra a nála magasabb elemek, jobbra a nála magasabb-egyenlő elemek tartoznak hozzá. Ha ez a tartomány L + w_i + R
széles, akkor az ebben lévő, az i. elemet átfedő oszloptartományok száma
Len(Len+1)/2 - L(L+1)/2 - R(R+1)/2, és ezt szorozva h_i(h_i+1)/2-vel, összegezve kapjuk a választ.
Az időigény O(N), a számok kezelése 128 bites egészekkel történik.
*/
/*
Hint 1: || Ne a téglalapokat egyenként számold, hanem azt nézd, hány magassági pár tartozik egy adott vízszintes oszloptartományhoz: ez mindig a tartomány legalacsonyabb elemének magasságától függ. ||
Hint 2: || Minden oszloptartományt pontosan egyszer rendelj egy elemhez: a benne lévő legalacsonyabb elemhez (egyenlőség esetén a balról első). Ehhez minden elemre keresd meg a bal és a jobb oldali „határoló” elemet monoton veremmel. ||
Hint 3: || Az i. elemhez tartozó tartomány hossza L + w_i + R egységnyi. Ebben az összes oszloptartományból vond ki azokat, amelyek csak a bal, illetve csak a jobb oldalon vannak, így marad az i. elemet átfedő intervallumok száma. Ezt szorozd h_i(h_i+1)/2-vel és a végén moduláris összegezd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const long long MOD = 1000000007LL;

    int n;
    cin >> n;
    vector<long long> h(n), w(n);
    for (auto &x : h) cin >> x;
    for (auto &x : w) cin >> x;

    // pref[i] = w_0 + ... + w_{i-1}
    vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + w[i];

    // lft[i]: legközelebbi j < i, amelyre h_j <= h_i (különben -1)
    // rgt[i]: legközelebbi k > i, amelyre h_k < h_i (különben n)
    vector<int> lft(n), rgt(n);
    {
        vector<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && h[st.back()] > h[i]) st.pop_back();
            lft[i] = st.empty() ? -1 : st.back();
            st.push_back(i);
        }
    }
    {
        vector<int> st;
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && h[st.back()] >= h[i]) st.pop_back();
            rgt[i] = st.empty() ? n : st.back();
            st.push_back(i);
        }
    }

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        long long L = pref[i] - pref[lft[i] + 1];   // bal oldali tartomány szélessége
        long long R = pref[rgt[i]] - pref[i + 1];   // jobb oldali tartomány szélessége
        long long len = L + w[i] + R;

        __int128 Len = len, Lb = L, Rb = R;
        __int128 cnt = Len * (Len + 1) / 2 - Lb * (Lb + 1) / 2 - Rb * (Rb + 1) / 2;

        long long t = h[i] * (h[i] + 1) / 2 % MOD;     // magassági párok száma
        long long c = (long long)(cnt % MOD);
        ans = (ans + t * c) % MOD;
    }

    cout << ans << "\n";
    return 0;
}
