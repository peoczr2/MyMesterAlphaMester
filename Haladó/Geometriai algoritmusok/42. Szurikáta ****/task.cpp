/*
Megoldás lényege:
A szurikáták közül csak azok válhatnak láthatóvá egy kérés alatt, akik az eredeti állapotban
is láthatók voltak, vagy éppen megnyújtjuk őket. Egy eredetileg nem látható szurikátát egy
későbbi csökkentett meredekség sem tud láthatóvá tenni, mert előtte már volt nála kisebb
eredeti látható szurikáta, és a módosítások csak tovább csökkentik ezeket az értékeket.

Ezért először kiszámítjuk az eredeti látható szurikáták sorozatát. Ez a sorozat balról jobbra
szigorúan csökkenő meredekségű. Egy lekérdezésben a módosított szurikátákat index szerint
beillesztjük ebbe a statikus láncba: két módosított index között az eredeti látható szurikáták
egy összefüggő részszakasza marad, és ebben elég egy bináris kereséssel megtalálni, hány
meredekség kisebb az aktuális minimumtól.

Idő: O((összes módosítás) * log N).
*/

#include <bits/stdc++.h>
using namespace std;

struct Ratio {
    long long num, den;
};

static bool ratioLess(const Ratio& a, const Ratio& b) {
    return (__int128)a.num * b.den < (__int128)b.num * a.den;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    long long P;
    if (!(cin >> N >> P >> Q)) return 0;

    vector<int> x(N + 1);
    vector<long long> baseNum(N + 1);
    for (int i = 1; i <= N; ++i) cin >> x[i];
    for (int i = 1; i <= N; ++i) {
        long long y;
        cin >> y;
        baseNum[i] = P - y;
    }

    vector<int> visPos;
    vector<Ratio> visVal;
    visPos.reserve(N);
    visVal.reserve(N);

    Ratio best{0, 1};
    bool hasBest = false;
    for (int i = 1; i <= N; ++i) {
        Ratio cur{baseNum[i], x[i]};
        if (!hasBest || ratioLess(cur, best)) {
            visPos.push_back(i);
            visVal.push_back(cur);
            best = cur;
            hasBest = true;
        }
    }

    auto processInterval = [&](int leftExclusive, int rightExclusive, long long& answer, bool& hasCurr, Ratio& curr) {
        auto itL = upper_bound(visPos.begin(), visPos.end(), leftExclusive);
        auto itR = lower_bound(visPos.begin(), visPos.end(), rightExclusive);
        if (itL >= itR) return;

        int L = int(itL - visPos.begin());
        int R = int(itR - visPos.begin()) - 1;

        if (!hasCurr) {
            answer += R - L + 1;
            curr = visVal[R];
            hasCurr = true;
            return;
        }

        int lo = L, hi = R + 1;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if (ratioLess(visVal[mid], curr)) hi = mid;
            else lo = mid + 1;
        }

        if (lo <= R) {
            answer += R - lo + 1;
            curr = visVal[R];
        }
    };

    while (Q--) {
        int D;
        cin >> D;

        vector<int> idx(D);
        vector<long long> add(D);
        for (int i = 0; i < D; ++i) cin >> idx[i] >> add[i];

        long long answer = 0;
        bool hasCurr = false;
        Ratio curr{0, 1};

        int prev = 0;
        for (int i = 0; i < D; ++i) {
            processInterval(prev, idx[i], answer, hasCurr, curr);

            Ratio cur{baseNum[idx[i]] - add[i], x[idx[i]]};
            if (!hasCurr || ratioLess(cur, curr)) {
                ++answer;
                curr = cur;
                hasCurr = true;
            }

            prev = idx[i];
        }
        processInterval(prev, N + 1, answer, hasCurr, curr);

        cout << answer;
        if (Q) cout << ' ';
    }
    cout << '\n';

    return 0;
}