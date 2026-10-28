/*
Megoldás lényege:
Az origóból nézve egy (x, y, dx, dy) téglalap a [y/(x+dx), (y+dy)/x] meredekség-intervallumú szögtartományt takarja: a legkisebb szög az alsó-jobb sarok (x+dx, y), a legnagyobb a felső-bal sarok (x, y+dy) irányához tartozik. Két épület között takarás van, ha a szögtartományaik átfedik egymást, vagy legalább egy sugáron érintkeznek (a közös sugárra eső két sarok közül az egyik takarja a másikat). Így a feladat a legtöbb olyan intervallum kiválasztása, amelyek közül bármely kettő diszjunkt (érintkezés nélkül). Ezt mohó módszerrel oldjuk meg: a jobb végpont szerint rendezünk, és mindig azt az intervallumot vesszük, amelyik a már kiválasztott utolsó végpont után kezdődik. Az összehasonlítások egész szorzatokkal történnek, így nincs kerekítési hiba. Idő: O(N log N)
*/
/*
Hint 1: || Az origóból nézve egy téglalap szögtartományát az alsó-jobb sarok (x+dx, y) és a felső-bal sarok (x, y+dy) iránya határolja. Két épület pontosan akkor nem takar egymásra, ha ezek a szögtartományok nem metszik egymást. ||
Hint 2: || Ez intervallum-kiválasztás: a legtöbb egymással nem átfedő intervallumot keresed. Erre a klasszikus mohó módszer működik: a végpontok szerint növekvő sorrendben haladj, és mindig vedd azt, amelyik a már választott utolsó végpont után kezdődik. ||
Hint 3: || A meredekségeket ne törtként hasonlítsd össze, hanem keresztbe szorozva (egész számokkal). A szorzatok elérhetik a 10^12 nagyságrendet, ezért érdemes __int128 típust használni. Az egyenlő végpontú intervallumokat rendezd úgy, hogy a rövidebb induljon elöl. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Rect {
    long long x, y, dx, dy;
    int id;
};

static bool rightLess(const Rect& a, const Rect& b) {
    __int128 lhs = (__int128)(a.y + a.dy) * b.x;
    __int128 rhs = (__int128)(b.y + b.dy) * a.x;
    if (lhs != rhs) return lhs < rhs;

    __int128 la = (__int128)a.y * (b.x + b.dx);
    __int128 lb = (__int128)b.y * (a.x + a.dx);
    if (la != lb) return la > lb;

    return a.id < b.id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<Rect> rects(n);
    for (int i = 0; i < n; ++i) {
        cin >> rects[i].x >> rects[i].y >> rects[i].dx >> rects[i].dy;
        rects[i].id = i + 1;
    }

    sort(rects.begin(), rects.end(), rightLess);

    vector<int> chosen;
    chosen.reserve(n);

    bool hasEnd = false;
    long long endNum = 0, endDen = 1;

    for (const auto& r : rects) {
        __int128 leftLhs = (__int128)r.y * endDen;
        __int128 leftRhs = (__int128)endNum * (r.x + r.dx);
        if (!hasEnd || leftLhs > leftRhs) {
            chosen.push_back(r.id);
            hasEnd = true;
            endNum = r.y + r.dy;
            endDen = r.x;
        }
    }

    cout << chosen.size() << '\n';
    for (int i = 0; i < (int)chosen.size(); ++i) {
        if (i) cout << ' ';
        cout << chosen[i];
    }
    cout << '\n';

    return 0;
}
