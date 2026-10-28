/*
Megoldás lényege:
Adott D legnagyobb megengedett kötélhosszra balról jobbra haladva ugyanúgy veremmel dolgozunk, mint
a 107. feladatban, de két zászlót csak akkor kötünk össze, ha színük eltér és a távolságuk legfeljebb D.
Ha a verem tetején álló zászló már D-nél messzebb van, akkor soha nem kerülhet párba, tehát D nem jó.
Ha az aktuális zászló párosítható a verem tetejével, az összekötés nem ront, mert egy esetleges más
megoldás is átalakítható úgy, hogy ugyanezt a párt használja. Mivel a nagyobb D sosem rontja a
helyzetet, a legkisebb jó D-t bináris kereséssel keressük meg.
*/
/*
Hint 1: || Ugyanaz a veremes párosítás működik, mint a 107. feladatban, csak a kötélhossz felső korlátja (D) is szerepet kap. ||
Hint 2: || Egy adott D-re elég egyetlen balról jobbra haladó bejárás: ha az aktuális zászló és a verem teteje eltérő színű és D-n belül vannak, összekötjük, különben a verembe tesszük. ||
Hint 3: || Az igen/nem válasz D-ben monoton, ezért a legkisebb igen-hoz tartozó D-t bináris kereséssel kapjuk. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    string s;
    cin >> N >> s;

    auto ok = [&](int lim) {
        vector<pair<char,int>> st;
        st.reserve(2 * N);
        for (int i = 0; i < 2 * N; ++i) {
            char c = s[i];
            if (!st.empty() && st.back().first != c && i + 1 - st.back().second <= lim) {
                st.pop_back();
            } else {
                st.push_back({c, i + 1});
            }
        }
        return st.empty();
    };

    int lo = 0, hi = 2 * N;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (ok(mid)) hi = mid;
        else lo = mid + 1;
    }

    cout << lo << '\n';
    return 0;
}