/*
Megoldás lényege:
A három részfeladat mindegyike a szakaszok végpontjainak és színének egyszerű feltételvizsgálata. Az 1. részben a tükörképet úgy kapjuk, hogy az x koordinátát M-1-x-re cseréljük (ez a függőleges középvonalra vonatkozó tükrözés), és ellenőrizzük, hogy a végpontpár (sorrendtől függetlenül) egyezik-e a tükörképével, azonos színnel. A 2. részben függőleges az a szakasz, ahol X1 = X2, vízszintes az, ahol Y1 = Y2; két szakasz akkor csatlakozik, ha pontosan egy végpontjuk közös. Az első megfelelő párt a sorszámok szerinti bejárással találjuk meg. A 3. részben a négyzetes hosszt (dx*dx + dy*dy) egész számként hasonlítjuk össze, így gyökvonás és lebegőpontos hiba nincs, a szigorú összehasonlítás pedig az egyenlőség esetén a kisebb sorszámút tartja meg. Az időigény O(K^2), ahol K legfeljebb 200.
*/
/*
Hint 1: || A tükörkép a kép függőleges középvonalára vonatkozik: egy pixel x koordinátája M-1-x lesz. Egy szakasz akkor tükörkép, ha a végpontjai (sorrendtől függetlenül) pontosan ezekre a pontokra esnek, és a színe is egyezik az elsővel. ||
Hint 2: || A csatlakozás eldöntéséhez számold meg, hány végpont egyezik két szakasz között: pontosan egy közös végpont kell legyen. Függőleges szakasz az, ahol X1 = X2, vízszintes az, ahol Y1 = Y2. Az első függőleges szakaszt a sorszám szerinti bejárással keresd, és a hozzá csatlakozó első vízszintest is így. ||
Hint 3: || A leghosszabb szakasz kereséséhez ne használj gyökvonást: a dx*dx + dy*dy összehasonlítása elegendő. Szigorú > összehasonlítással haladj a sorszámok szerint, így egyenlő hossz esetén a legkisebb sorszám marad meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Seg {
    int x1, y1, x2, y2, r, g, b;
};

bool connected(const Seg &a, const Seg &b) {
    int ax[2] = {a.x1, a.x2}, ay[2] = {a.y1, a.y2};
    int bx[2] = {b.x1, b.x2}, by[2] = {b.y1, b.y2};
    int common = 0;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (ax[i] == bx[j] && ay[i] == by[j]) common++;
    return common == 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n, k;
    cin >> m >> n >> k;
    vector<Seg> s(k);
    for (auto &t : s) cin >> t.x1 >> t.y1 >> t.x2 >> t.y2 >> t.r >> t.g >> t.b;

    // 1. részfeladat: az első szakasz tükörképei, azonos színnel
    const Seg &f = s[0];
    vector<int> mirror;
    for (int i = 0; i < k; i++) {
        const Seg &t = s[i];
        if (t.r != f.r || t.g != f.g || t.b != f.b) continue;
        bool direct = t.x1 == m - 1 - f.x1 && t.y1 == f.y1 && t.x2 == m - 1 - f.x2 && t.y2 == f.y2;
        bool swapped = t.x1 == m - 1 - f.x2 && t.y1 == f.y2 && t.x2 == m - 1 - f.x1 && t.y2 == f.y1;
        if (direct || swapped) mirror.push_back(i + 1);
    }
    cout << "#\n";
    cout << mirror.size();
    for (int id : mirror) cout << ' ' << id;
    cout << "\n";

    // 2. részfeladat: első függőleges szakasz, amelyhez vízszintes csatlakozik
    int vIdx = -1, hIdx = -1;
    for (int i = 0; i < k && vIdx < 0; i++) {
        if (s[i].x1 != s[i].x2) continue;
        for (int j = 0; j < k; j++) {
            if (s[j].y1 != s[j].y2) continue;
            if (connected(s[i], s[j])) {
                vIdx = i + 1;
                hIdx = j + 1;
                break;
            }
        }
    }
    cout << "#\n";
    if (vIdx < 0) cout << "-1\n";
    else cout << vIdx << ' ' << hIdx << "\n";

    // 3. részfeladat: leghosszabb alapszínű szakasz
    int best = -1;
    long long bestLen = -1;
    for (int i = 0; i < k; i++) {
        const Seg &t = s[i];
        bool prim = (t.r == 255 && t.g == 0 && t.b == 0) ||
                    (t.r == 0 && t.g == 255 && t.b == 0) ||
                    (t.r == 0 && t.g == 0 && t.b == 255);
        if (!prim) continue;
        long long dx = t.x1 - t.x2, dy = t.y1 - t.y2;
        long long len = dx * dx + dy * dy;
        if (len > bestLen) {
            bestLen = len;
            best = i + 1;
        }
    }
    cout << "#\n" << best << "\n";
    return 0;
}
