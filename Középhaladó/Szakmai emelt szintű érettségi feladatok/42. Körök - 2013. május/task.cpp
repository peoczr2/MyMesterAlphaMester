/*
Megoldás lényege:
A bemenet összes körét egy tömbbe olvassuk, és minden részfeladatot egész számokkal, négyzetes összehasonlítással oldunk meg, így nincs pontatlanság a közelítésekből. Egy kör akkor esik egy síknegyedbe, ha teljes egészében a zárt síknegyedben van, azaz az első síknegyedhez x - r >= 0 és y - r >= 0 szükséges, a többi síknegyedhez hasonlóan. A négy síknegyedbe nyúló körök a középpont és a síknegyed legközelebbi pontja közötti távolság alapján döntendők el: ha ez kisebb a sugárnál, a kör belemetsz a nyitott síknegyedbe. A két legtávolabbi kör keresésénél minden körpárra kiszámoljuk a körvonalaik legkisebb távolságát (D - r1 - r2, illetve a beágyazott esetben |r1 - r2| - D, különben 0), és az első maximumot tartjuk meg. Az x-tengely fölötti metsző párok azok, amelyeknél mindkét kör teljesen az x-tengely felett (y - r >= 0) van, és a körvonalak két pontban metszik egymást. Az időigény O(n^2) a körpárokra, n <= 100 esetén ez bőven elég.
*/
/*
Hint 1: || Egy kör akkor esik egy zárt síknegyedbe, ha a középpont koordinátáinak és a sugárnak az összevetése mindkét tengelyre teljesül: például az első síknegyedhez x - r >= 0 és y - r >= 0 kell. ||
Hint 2: || A négy síknegyedbe nyúlást úgy ellenőrizd, hogy a középpontból a síknegyed legközelebbi pontjáig mért távolság négyzetét hasonlítod a sugár négyzetéhez; ez a legközelebbi pont úgy kapható, hogy mindkét koordinátát a 0 felé vágod. A körpárok metszéséhez és távolságához a D négyzetét (egész szám) vesd össze (r1 + r2)^2-tel és (r1 - r2)^2-tel. ||
Hint 3: || Két kör távolsága, ahol D a középpontok távolsága: ha D >= r1 + r2, akkor D - r1 - r2; ha D <= |r1 - r2|, akkor |r1 - r2| - D; minden más esetben 0. Ugyanígy a metszés feltétele: |r1 - r2| < D < r1 + r2. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<long long> X, Y, R;

// Két kör távolsága: a körvonalak legkisebb távolsága.
double circleDist(int i, int j) {
    long long dx = X[i] - X[j], dy = Y[i] - Y[j];
    long long d2 = dx * dx + dy * dy;
    long long s = R[i] + R[j];
    long long df = llabs(R[i] - R[j]);
    if (d2 >= s * s) return sqrt((double)d2) - (double)s;
    if (d2 <= df * df) return (double)df - sqrt((double)d2);
    return 0.0;
}

// Igaz, ha a kör belemetsz a nyitott (sx, sy) síknegyedbe.
bool hitsQuadrant(long long cx, long long cy, long long r, int sx, int sy) {
    long long px = (sx > 0) ? max(cx, 0LL) : min(cx, 0LL);
    long long py = (sy > 0) ? max(cy, 0LL) : min(cy, 0LL);
    long long dx = cx - px, dy = cy - py;
    return dx * dx + dy * dy < r * r;
}

int main() {
    long long x, y, r;
    while (cin >> x >> y >> r) {
        X.push_back(x);
        Y.push_back(y);
        R.push_back(r);
    }
    int n = X.size();

    // 1. részfeladat: síknegyedekben fekvő körök száma
    int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
    for (int i = 0; i < n; i++) {
        if (X[i] - R[i] >= 0 && Y[i] - R[i] >= 0) q1++;
        else if (X[i] + R[i] <= 0 && Y[i] - R[i] >= 0) q2++;
        else if (X[i] + R[i] <= 0 && Y[i] + R[i] <= 0) q3++;
        else if (X[i] - R[i] >= 0 && Y[i] + R[i] <= 0) q4++;
    }
    cout << "#\n" << q1 << ' ' << q2 << ' ' << q3 << ' ' << q4 << '\n';

    // 2. részfeladat: mind a négy síknegyedbe nyúló körök területösszege
    long long sumR2 = 0;
    for (int i = 0; i < n; i++) {
        bool all = true;
        for (int sx = -1; sx <= 1; sx += 2)
            for (int sy = -1; sy <= 1; sy += 2)
                if (!hitsQuadrant(X[i], Y[i], R[i], sx, sy)) all = false;
        if (all) sumR2 += R[i] * R[i];
    }
    cout << "#\n" << fixed << setprecision(2) << sumR2 * acos(-1.0) << '\n';

    // 3. részfeladat: a két legtávolabbi kör (lexikografikusan első)
    int bi = -1, bj = -1;
    double best = -1.0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            double d = circleDist(i, j);
            if (bi < 0 || d > best + 1e-9) {
                best = d;
                bi = i;
                bj = j;
            }
        }
    cout << "#\n" << bi + 1 << ' ' << bj + 1 << ' ' << fixed << setprecision(2) << best << '\n';

    // 4. részfeladat: az x-tengely felett lévő, egymást metsző körpárok
    cout << "#\n";
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            if (Y[i] - R[i] < 0 || Y[j] - R[j] < 0) continue;
            long long dx = X[i] - X[j], dy = Y[i] - Y[j];
            long long d2 = dx * dx + dy * dy;
            long long s = R[i] + R[j];
            long long df = llabs(R[i] - R[j]);
            if (d2 > df * df && d2 < s * s) cout << i + 1 << ' ' << j + 1 << '\n';
        }
    return 0;
}
