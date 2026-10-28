/*
Megoldás lényege:
A fal oszlopainak magassága D_i, a legnagyobb használható tégla pedig a falba beférő, legnagyobb területű téglalap, vagyis a legnagyobb téglalap a hisztogramban. Egy téglalap magassága mindig a rajta átmenő oszlopok közül a legalacsonyabbé, ezért minden oszlophoz azt a legszélesebb szakaszt keressük, ahol az oszlop magassága a legkisebb. Ezt egy monoton verem segítségével egy bejárásban megkapjuk: amikor alacsonyabb oszlop jön, a veremből kivett oszlop téglalapját lezárjuk, a szélességet pedig a verem alatti elem és az aktuális hely távolsága adja. Az időigény O(N), a terület akár 4·10^10 is lehet, ezért long long típust használunk.
*/
/*
Hint 1: || Egy téglalap magassága a rajta átmenő oszlopok közül a legalacsonyabbé. Rögzíts egy oszlopot magasságként, és nézd meg, meddig terjeszkedhet balra és jobbra. ||
Hint 2: || Minden oszlophoz keresd meg a bal és a jobb oldalán az első nála alacsonyabb oszlopot. A köztük lévő távolság adja a legnagyobb szélességet, amelyen az oszlop magassága teljesen kitölthető. ||
Hint 3: || Ezt egyetlen bejárásban egy verem segítségével számold: a verem növekvő magasságú oszlopokat tartalmaz, és a kivétel pillanatában a bal határt a verem alatti elem adja. A végén egy 0 magasságú őrszemmel üresítsd ki a vermet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long m;
    cin >> n >> m;
    vector<long long> h(n + 1, 0);
    for (int i = 0; i < n; i++) cin >> h[i];
    h[n] = 0;  // őrszem: minden oszlopot kiürít

    long long best = 0;
    vector<int> st;
    for (int i = 0; i <= n; i++) {
        while (!st.empty() && h[st.back()] >= h[i]) {
            int top = st.back();
            st.pop_back();
            long long left = st.empty() ? 0 : st.back() + 1;
            long long width = i - left;
            best = max(best, h[top] * width);
        }
        st.push_back(i);
    }

    cout << best << '\n';
    return 0;
}
