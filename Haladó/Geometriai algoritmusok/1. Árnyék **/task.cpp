/*
Megoldás lényege:
A napsugarak párhuzamosak, ezért minden töréspontot egyetlen számmal jellemezhetünk: a g = h - k*x értékkel,
ahol k a sugarak meredeksége (k = cos(alfa) / sin(alfa)). Egy pont akkor van árnyékban, ha a fény felőli oldalon
van olyan töréspont, amelynek g-értéke nagyobb nála. A fény irányában haladva nyilvántartjuk az eddigi
g-maximumot. Egy szakasz teljesen árnyékos, ha egyik végpontjának g-értéke sincs a maximum felett (a sugárral
egy egyenesbe eső szakasz még megvilágított), részben árnyékos, ha a maximum a két végpont g-értéke közé esik.
A kimeneti listákat növekvő sorrendbe rendezzük.

Idő: O(M log M) (a rendezés miatt).
*/
/*
Hint 1: || A sugarak párhuzamosak, ezért minden töréspontot egy szám jellemez: az a magasság, ahol a rajta átmenő
sugár a tengelyt metszi (g = h - k*x). Egy pont pontosan akkor árnyékos, ha a fény felőli töréspontok közül
valamelyiknek nagyobb a g-értéke. ||
Hint 2: || Haladj végig a töréspontokon a fény irányában (alfa < 0: balról jobbra, alfa > 0: jobbról balra), és
közben tartsd nyilván az eddigi legnagyobb g-értéket. Egy szakasz végpontjainak g-értékét ezzel a maximummal
összevetve eldöntheted, hogy a szakasz teljesen vagy csak részben árnyékos-e. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, alpha;
    if (!(cin >> m >> alpha)) {
        return 0;
    }

    vector<long double> x(m + 1), h(m + 1);
    for (int i = 1; i <= m; ++i) {
        cin >> x[i] >> h[i];
    }

    vector<int> fullShadow;
    vector<int> partialShadow;

    if (alpha == 0) {
        cout << "IGEN\n";
        return 0;
    }

    const long double rad = acosl(-1.0L) * static_cast<long double>(alpha) / 180.0L;
    const long double s = sinl(rad);
    const long double c = cosl(rad);
    const long double raySlope = c / s; // slope of sunlight direction
    const long double eps = 1e-12L;

    auto g = [&](int i) -> long double {
        return h[i] - raySlope * x[i];
    };

    auto classifySegment = [&](int segIdx, long double g1, long double g2, long double bestPrev) {
        long double mn = min(g1, g2);
        long double mx = max(g1, g2);

        if (mx <= bestPrev + eps) {
            bool onBoundary1 = fabsl(g1 - bestPrev) <= eps;
            bool onBoundary2 = fabsl(g2 - bestPrev) <= eps;
            if (!(onBoundary1 && onBoundary2)) {
                fullShadow.push_back(segIdx);
            }
            return;
        }

        if (mn < bestPrev - eps && mx > bestPrev + eps) {
            partialShadow.push_back(segIdx);
        }
    };

    if (alpha < 0) {
        long double best = g(1);
        for (int i = 1; i <= m - 1; ++i) {
            long double g1 = g(i);
            long double g2 = g(i + 1);
            classifySegment(i, g1, g2, best);
            best = max(best, max(g1, g2));
        }
    } else {
        long double best = g(m);
        for (int i = m - 1; i >= 1; --i) {
            long double g1 = g(i + 1);
            long double g2 = g(i);
            classifySegment(i, g1, g2, best);
            best = max(best, max(g1, g2));
        }
    }

    if (fullShadow.empty() && partialShadow.empty()) {
        cout << "IGEN\n";
        return 0;
    }

    cout << "NEM\n";
    // A megvilágítás irányából első árnyékos szakasz: az eredeti bejárási sorrend első eleme.
    if (!fullShadow.empty()) {
        cout << fullShadow.front() << "\n";
    } else {
        cout << "0\n";
    }
    // Az alfa > 0 ágban a bejárás csökkenő, ezért a listákat ki írás előtt rendezzük.
    sort(fullShadow.begin(), fullShadow.end());
    sort(partialShadow.begin(), partialShadow.end());

    for (int idx : fullShadow) {
        cout << idx << ' ';
    }
    cout << "\n";

    for (int idx : partialShadow) {
        cout << idx << ' ';
    }
    cout << "\n";

    return 0;
}
