/*
Megoldás lényege:
A magánhangzók az a, e, i, o, u betűk, mert az ékezetes betűket ékezet nélkül írjuk.
Két szomszédos magánhangzó közötti mássalhangzó-szakaszt külön vizsgálunk, és ebben számoljuk a hangokat.
Először az egymás melletti azonos betűket egy betűnek vesszük, mert a hosszú mássalhangzó egy hang.
Ezután balról jobbra haladva a dzs (3 betű), valamint a cs, dz, gy, ly, ny, sz, ty, zs (2 betű) jelöléseket egy-egy hangnak tekintjük, a többi betű külön hang.
A szakasz eredménye a kapott hangok száma, az időigény a szó hosszával arányos.
*/
/*
Hint 1: || Először keresd meg a magánhangzók helyét a szóban (a, e, i, o, u). Csak a két egymás utáni magánhangzó közti részt kell vizsgálnod. ||
Hint 2: || Egy mássalhangzó-szakaszban az egymás melletti azonos betűk (pl. kk, ss) egyetlen hosszú hangot jelölnek, ezért előbb vond őket egy betűvé. ||
Hint 3: || Az összevont szakaszt balról jobbra járd be: a dzs háromkarakteres, a cs, dz, gy, ly, ny, sz, ty, zs kétkarakteres jelölés egy hangot ad, minden más betű külön hangot ad. ||
*/
#include <bits/stdc++.h>
using namespace std;

bool maganhangzo(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

bool ketbetus(const string &t) {
    static const set<string> d = {"cs", "dz", "gy", "ly", "ny", "sz", "ty", "zs"};
    return d.count(t) > 0;
}

int main() {
    string s;
    cin >> s;
    for (char &c : s) c = tolower(static_cast<unsigned char>(c));

    vector<int> poz;
    for (int i = 0; i < (int)s.size(); ++i)
        if (maganhangzo(s[i])) poz.push_back(i);

    vector<int> ans;
    for (size_t k = 0; k + 1 < poz.size(); ++k) {
        string resz = s.substr(poz[k] + 1, poz[k + 1] - poz[k] - 1);

        string egy;
        for (char c : resz)
            if (egy.empty() || egy.back() != c) egy += c;

        int hang = 0;
        size_t i = 0;
        while (i < egy.size()) {
            ++hang;
            if (i + 3 <= egy.size() && egy.substr(i, 3) == "dzs") i += 3;
            else if (i + 2 <= egy.size() && ketbetus(egy.substr(i, 2))) i += 2;
            else i += 1;
        }
        ans.push_back(hang);
    }

    for (size_t i = 0; i < ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
