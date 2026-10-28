/*
Megoldás lényege:
Balról jobbra haladva egy veremben tároljuk azokat a pontokat, amelyek magasabbak minden utánuk eddig látott pontnál; a veremben alulról felfelé a magasságok szigorúan csökkennek.
Új r-edik pont érkezésekor a verem tetejéről kivesszük azokat, amelyek nem magasabbak nála. Egy ilyen l pont és r völgyet alkot, ha r - l >= 2, mert a közöttük lévő legmagasabb pont (a verem következő eleme) szigorúan alacsonyabb mindkettőjüknél.
A kivétel után a verem tetején maradt pont akkor is völgy-párja r-nek, ha az utoljára kivett pont szigorúan alacsonyabb az r-ediknél.
A válasz a talált legnagyobb r - l, vagy -1, ha nincs völgy. Az időigény O(N), mert minden pont legfeljebb egyszer kerül be és ki a veremből.
*/
/*
Hint 1: || Egy (bal, jobb) pár csak akkor lehet völgy két szélső pontja, ha közöttük minden pont szigorúan alacsonyabb mindkettőjüknél. Balról jobbra haladva tehát csak azokat a bal oldali pontokat kell megőrizned, amelyek magasabbak minden utánuk eddig látott pontnál. ||
Hint 2: || Ezeket a pontokat veremben tárold: a verem alulról felfelé szigorúan csökkenő magasságú pontokat tartalmaz. Új pont érkezésekor a verem tetejéről vedd ki azokat, amelyek nem magasabbak nála. ||
Hint 3: || Egy kivett l pont és az új r pont völgyet alkot, ha r - l legalább 2. A kivett pontok közötti legmagasabb pont a verem következő eleme, ezért ez mindig alacsonyabb l-nél. Ha az utoljára kivett pont szigorúan alacsonyabb az r-ediknél, a kivétel után a verem tetején maradt pont is alkot vele völgyet. A válasz a legnagyobb ilyen r - l, vagy -1, ha nincs. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> t(n);
    for (int &x : t) cin >> x;

    vector<int> st; // indexek, a magasságok alulról felfelé szigorúan csökkenek
    int best = -1;
    for (int r = 0; r < n; r++) {
        int last = -1; // az utoljára kivett index (a verem tetején maradt pont közvetlen gyereke)
        while (!st.empty() && t[st.back()] <= t[r]) {
            int l = st.back();
            st.pop_back();
            if (r - l >= 2) best = max(best, r - l);
            last = l;
        }
        if (!st.empty() && last != -1 && t[last] < t[r]) {
            best = max(best, r - st.back());
        }
        st.push_back(r);
    }
    cout << best << '\n';
    return 0;
}
