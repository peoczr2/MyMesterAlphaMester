/*
Megoldás lényege:
Mivel a genetikai kódok K hosszúak és egymás utáni, át nem fedő darabok, a sorozatot K karakterenként daraboljuk (0, K, 2K, … pozíciótól), és minden darab előfordulásait egy map<string, int>-ben számoljuk. Két élőlény pontosan akkor tartozik azonos fajba, ha a két gyakorisági tábla megegyezik, vagyis minden kódból ugyanannyi van mindkét leírásban. Eltérő hosszúság esetén a válasz rögtön NEM. Egy sorozat feldolgozása O(hossz · log(26^K)), ami 100 000 karakterre és M ≤ 10 párra bőven belefér az időkorlátba.
*/
/*
Hint 1: || Két élőlény akkor azonos fajba tartozik, ha minden K hosszú kódból ugyanannyi van mindkét leírásban. A kódok nem átfedőek, ezért K karakterenként haladj a sorozaton. ||
Hint 2: || Számold meg a kódok előfordulását egy map<string, int>-tel, majd a két map egyenlőségét ellenőrizd, mert a C++ map összehasonlítása a kulcsokat és az értékeket is nézi. Ha a két sorozat hossza eltér, a válasz NEM. ||
*/
#include <bits/stdc++.h>
using namespace std;

map<string, int> gyakorisag(const string &s, int k) {
    map<string, int> m;
    for (size_t i = 0; i + k <= s.size(); i += k) {
        m[s.substr(i, k)]++;
    }
    return m;
}

int main() {
    int m, k;
    cin >> m >> k;
    for (int i = 0; i < m; i++) {
        string a, b;
        cin >> a >> b;
        bool azonos = a.size() == b.size() && gyakorisag(a, k) == gyakorisag(b, k);
        cout << (azonos ? "IGEN" : "NEM") << '\n';
    }
    return 0;
}
