/*
Megoldás lényege:
Egy elfogadott megrendelés 2 buznyákot ér, ha a székblokk pontosan az igényelt, egyébként 1-et, így a feladat: legfeljebb N darab diszjunkt, L hosszú székblokk közül kell a legnagyobb összértékű halmazt választani. Az optimális érték a blokkszám konkáv függvénye (a feltétel-mátrix intervallum-mátrix, ezért az LP egész), ezért egy egész λ büntetéssel (darabonként λ levonásával) végzett O(M)-es DP-vel megkereshető az a λ, amelynél a T = min(N, szabad optimum) darabszám optimális. Ehhez a DP-ben (érték, darabszám) páron lexikografikusan optimalizálunk, így megkapjuk a legkevesebb és a legtöbb darabból álló optimális megoldást. Ezek átfedő blokk-komponensei mentén, sorban cserélve (a komponensek darabszám-különbsége -1, 0 vagy 1) pontosan T darabos optimális megoldás áll elő. A szerelők (megrendelések) kiosztása ezután: minden pontosan illeszkedő blokkhoz a megfelelő megrendelés, a többi blokkhoz tetszőleges fennmaradó megrendelés kell. Az időigény O(M log M), a memóriaigény O(M + N).
*/
/*
Hint 1: || Minden elfogadott megrendelés legalább 1 buznyákot ér, a pontos egyezés 2-t. A feladat tehát: legfeljebb N darab, egymást nem fedő L hosszú blokk közül a legnagyobb összértékű választás kell. ||
Hint 2: || Ha minden blokkot λ értékkel "megadóztatsz", a darabszám-korlát nélküli optimum egy egyszerű prefix-DP-vel megkapható a székek sorrendjében. A λ-t bináris kereséssel állítsd be úgy, hogy az optimum darabszáma pontosan T legyen. ||
Hint 3: || A DP-ben a (érték, darabszám) párt lexikografikusan optimalizáld, így megkapod a legkevesebb és a legtöbb darabos optimumot. Ezek blokkjait a közös fedésű komponensek mentén összefésülve (sorban egy-egy komponens cseréjével) elérhető, hogy a darabszám pontosan T legyen, az érték változatlanul maximális. ||
*/
#include <bits/stdc++.h>
using namespace std;

int M, L, N;
vector<int> wgt;  // wgt[y]: 2, ha a y-tól kezdődő blokk pontosan igényelt, különben 1

struct Res {
    long long val;
    int cnt;
    vector<int> starts;
};

// Prefix-DP a székeken; a (büntetett érték, darabszám) párt lexikografikusan optimalizálja.
// maxCnt = true: legtöbb darabos optimum, false: legkevesebb darabos optimum.
Res solveDP(long long lam, bool maxCnt) {
    vector<long long> fv(M + 1, 0);
    vector<int> fc(M + 1, 0);
    vector<char> take(M + 1, 0);
    for (int s = 1; s <= M; s++) {
        long long bv = fv[s - 1];
        int bc = fc[s - 1];
        char t = 0;
        if (s >= L) {
            int y = s - L + 1;
            long long cv = fv[s - L] + wgt[y] - lam;
            int cc = fc[s - L] + 1;
            if (cv > bv || (cv == bv && (maxCnt ? cc > bc : cc < bc))) {
                bv = cv;
                bc = cc;
                t = 1;
            }
        }
        fv[s] = bv;
        fc[s] = bc;
        take[s] = t;
    }
    Res r;
    r.val = fv[M];
    r.cnt = fc[M];
    int s = M;
    while (s > 0) {
        if (take[s]) {
            r.starts.push_back(s - L + 1);
            s -= L;
        } else {
            s--;
        }
    }
    reverse(r.starts.begin(), r.starts.end());
    return r;
}

struct Comp {
    vector<int> a, b;  // a: a legkevesebb darabos megoldás blokkjai, b: a legtöbb darabosé
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> M >> L >> N;
    vector<int> z(N + 1);
    for (int i = 1; i <= N; i++) cin >> z[i];

    int P = M - L + 1;  // a blokk kezdő széke: 1..P
    wgt.assign(P + 2, 1);
    vector<int> ordOf(P + 2, 0);  // a pontosan igényelt blokkhoz tartozó első megrendelés
    for (int i = 1; i <= N; i++) {
        int y = z[i];
        if (ordOf[y] == 0) ordOf[y] = i;
        wgt[y] = 2;
    }

    // Darabszám-korlát nélküli optimum darabszáma; ennél többet nem érdemes használni.
    int hi0 = solveDP(0, true).cnt;
    int T = min(N, hi0);

    // Legnagyobb egész λ, amelynél a legtöbb darabos optimum még legalább T darabos.
    long long Lb = -(long long)M - 5, Rb = 3;
    while (Rb - Lb > 1) {
        long long mid = Lb + (Rb - Lb) / 2;
        if (solveDP(mid, true).cnt >= T)
            Lb = mid;
        else
            Rb = mid;
    }
    long long lam = Lb;

    Res A = solveDP(lam, false);
    Res B = solveDP(lam, true);

    // A és B blokkjainak átfedő komponensei (intervallum-uniók).
    vector<pair<int, int>> items;
    for (int y : A.starts) items.push_back({y, 0});
    for (int y : B.starts) items.push_back({y, 1});
    sort(items.begin(), items.end());

    vector<Comp> comps;
    long long curEnd = LLONG_MIN;
    for (auto [s, t] : items) {
        if (comps.empty() || s > curEnd) {
            comps.push_back(Comp());
            curEnd = LLONG_MIN;
        }
        if (t == 0)
            comps.back().a.push_back(s);
        else
            comps.back().b.push_back(s);
        curEnd = max(curEnd, (long long)s + L - 1);
    }

    // Komponensenként cserélünk A-ról B-re, amíg a darabszám el nem éri T-t.
    int need = T - A.cnt;
    long long cum = 0;
    vector<int> fin;
    for (auto &c : comps) {
        if (cum == need) {
            for (int y : c.a) fin.push_back(y);
        } else {
            for (int y : c.b) fin.push_back(y);
            cum += (long long)c.b.size() - (long long)c.a.size();
        }
    }
    sort(fin.begin(), fin.end());

    long long revenue = 0;
    for (int y : fin) revenue += wgt[y];

    // Megrendelések kiosztása: a pontosan illeszkedő blokkhoz az adott megrendelés,
    // a többi blokkhoz a még szabad megrendelések közül.
    vector<char> used(N + 1, 0);
    vector<int> ord(fin.size(), 0);
    for (size_t i = 0; i < fin.size(); i++) {
        if (wgt[fin[i]] == 2) {
            ord[i] = ordOf[fin[i]];
            used[ord[i]] = 1;
        }
    }
    int ptr = 1;
    for (size_t i = 0; i < fin.size(); i++) {
        if (wgt[fin[i]] == 1) {
            while (used[ptr]) ptr++;
            ord[i] = ptr;
            used[ptr] = 1;
        }
    }

    cout << revenue << '\n';
    cout << fin.size() << '\n';
    for (size_t i = 0; i < fin.size(); i++) {
        cout << ord[i] << ' ' << fin[i] << '\n';
    }
    return 0;
}
