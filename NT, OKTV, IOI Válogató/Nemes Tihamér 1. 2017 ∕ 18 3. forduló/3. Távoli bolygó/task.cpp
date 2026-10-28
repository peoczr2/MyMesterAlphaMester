/*
Megoldás lényege:
Mivel K legfeljebb 3, minden genetikai kód egyértelműen alakítható át a 0 és 26^K - 1 közötti egész számmá, a 26-os számrendszer szerint.
Mindkét leírást a 0., K., 2K., ... indextől kezdődő, K hosszú blokkokra bontjuk, és minden kódértékhez gyakoriságot számolunk egy tömbben.
A két élőlény pontosan akkor tartozik azonos fajba, ha a két gyakoriságtömb minden eleme megegyezik, ezt a vektorok egyenlőségével ellenőrizzük.
Egy párra az időigény O(L + 26^K), ahol L a leírás hossza, és 26^K legfeljebb 17 576.
*/
/*
Hint 1: || Hány különböző K hosszúságú kód létezhet összesen? Ha ezt tudod, már van egy olyan tömb mérete, amelyben a kódok gyakoriságát tárolhatod. ||
Hint 2: || Egy kódot úgy számolj át számmá, hogy minden betűből a karakter és az 'a' különbségét veszed, és v = v · 26 + érték módon haladsz végig a K betűn. A leírást K-val lépegetve számold a blokkokat, majd a két tömböt vesd össze. ||
*/
#include <bits/stdc++.h>
using namespace std;

static int kod(const string& s, int kezd, int k) {
    int ertek = 0;
    for (int i = 0; i < k; ++i) ertek = ertek * 26 + (s[kezd + i] - 'a');
    return ertek;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, k;
    cin >> m >> k;
    int maxkod = 1;
    for (int i = 0; i < k; ++i) maxkod *= 26;

    while (m--) {
        string a, b;
        cin >> a >> b;
        vector<int> cnta(maxkod), cntb(maxkod);
        for (int i = 0; i < (int)a.size(); i += k) ++cnta[kod(a, i, k)];
        for (int i = 0; i < (int)b.size(); i += k) ++cntb[kod(b, i, k)];
        cout << (cnta == cntb ? "IGEN" : "NEM") << '\n';
    }
    return 0;
}