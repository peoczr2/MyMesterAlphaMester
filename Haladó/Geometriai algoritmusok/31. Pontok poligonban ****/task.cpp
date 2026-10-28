/*
Megoldás lényege:
Minden kérdésnél a kiválasztott K pont alkotta sokszögre külön-külön eldöntjük, hogy a többi (kimaradt) pont benne van-e. A benne-van döntést sugaras (ray casting) módszerrel végezzük: a pontból vízszintes félegyenest húzunk jobbra, és megszámoljuk, hány sokszög-élt metsz. Páratlan metszésszám esetén a pont belül van. Az éleket féligzárt intervallum-szabállyal választjuk ki (a végpontok y-koordinátáját a ">" összehasonlítással vizsgáljuk), így egy csúcson átmenő sugár nem számolódik kétszer. Mivel nincs három egy egyenesre eső pont, pont sosem esik élre, a döntés egyértelmű. A metszés-vizsgálatot egész számokkal, osztás nélkül végezzük. Egy kérdés költsége O(N·K); a csúcsok összege a bemenetben legfeljebb 100 000, így az összes kérdés együtt nagyjából N·100 000 = 10^8 művelet.
*/
/*
Hint 1: || Egy pont akkor van a sokszög belsejében, ha egy tetszőleges irányú félegyenes a sokszög éleit páratlan számszor metszi. Erre a vízszintes, jobbra induló félegyenes a legkényelmesebb. ||
Hint 2: || Egy élt csak akkor kell figyelembe venni, ha végpontjai a pont y-koordinátájának ellentétes oldalán vannak. Ilyenkor a metszéspont x-koordinátáját kell összehasonlítani a pont x-koordinátájával. ||
Hint 3: || A kimaradt pontokat úgy kezeld, hogy a kiválasztott pontokat előre megjelölöd, és csak a többi pontot vizsgálod. Az x-összehasonlítást osztás nélkül, egész számokkal végezd: a metszéspont-képletet szorozd át az él y-irányú különbségével, és figyelj ennek előjelére. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
};

static bool insidePolygon(const vector<Pt>& poly, const Pt& p) {
    bool inside = false;
    int n = (int)poly.size();
    for (int i = 0, j = n - 1; i < n; j = i++) {
        const Pt& a = poly[j];
        const Pt& b = poly[i];
        // Az él metszi a vízszintes félegyenest, ha végpontjai a p.y különböző oldalán vannak.
        bool straddles = (a.y > p.y) != (b.y > p.y);
        // A metszéspont x-koordinátája > p.x  <=>  num / dy > 0, egész számokkal (osztás és elágazás nélkül).
        long long dy = b.y - a.y;
        long long num = (a.x - p.x) * dy + (b.x - a.x) * (p.y - a.y);
        bool crosses = ((num > 0) & (dy > 0)) | ((num < 0) & (dy < 0));
        inside ^= (straddles & crosses);
    }
    return inside;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Pt> pts(n + 1);
    for (int i = 1; i <= n; ++i) cin >> pts[i].x >> pts[i].y;

    vector<int> mark(n + 1, 0);
    vector<int> polyIds;
    polyIds.reserve(n);

    while (m--) {
        int k;
        cin >> k;
        vector<int> ids(k);
        vector<Pt> poly(k);
        for (int i = 0; i < k; ++i) {
            cin >> ids[i];
            poly[i] = pts[ids[i]];
            mark[ids[i]] = 1;
        }

        int answer = 0;
        for (int i = 1; i <= n; ++i) {
            if (mark[i]) continue;
            if (insidePolygon(poly, pts[i])) ++answer;
        }

        cout << answer << '\n';

        for (int id : ids) mark[id] = 0;
    }

    return 0;
}