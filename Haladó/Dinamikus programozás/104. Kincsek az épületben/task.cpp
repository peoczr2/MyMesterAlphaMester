/*
Megoldási ötlet:
Szintenként lefelé haladunk, ezért minden szinten csak az számít, hogy a robot a bal vagy a jobb
lépcsőnél áll. Ha egy szinten a kincsek a [L,R] intervallumban vannak, akkor bármely induló és kilépő
lépcsőpár esetén a feladat egy egydimenziós útvonaltervezés: a teljes intervallumot be kell járni.

A DP állapota dpBal és dpJobb: a már feldolgozott szintek után mennyi a minimális idő, ha a következő
szintre a bal, illetve a jobb lépcsőn érkezünk. Egy szinten a vízszintes út hossza képlettel számolható,
ehhez hozzáadjuk a kincsek felszedésének idejét. Az utolsó szinten már nem kell lépcsőhöz visszamenni,
ott bárhol megállhatunk, ezt külön kezeljük.
*/
/*
Hint 1: || Egy szinten csak a bal és jobb lépcső lehet fontos állapot, mert lefelé csak ott lehet továbbmenni. ||
Hint 2: || Ha vannak kincsek, akkor az adott szinten a bal szélső és jobb szélső kincset biztosan érinteni kell. ||
Hint 3: || Az utolsó szint különleges: ott már nem kell kijutni valamelyik lépcsőhöz, elég az összes kincset összeszedni. ||
*/

#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> count(n), first(n, -1), last(n, -1);
    for (int floor = 0; floor < n; ++floor) {
        cin >> count[floor];
        for (int i = 0; i < count[floor]; ++i) {
            int pos;
            cin >> pos;
            if (first[floor] == -1) first[floor] = pos;
            last[floor] = pos;
        }
    }

    const long long inf = numeric_limits<long long>::max() / 4;
    long long dpLeft = 0;
    long long dpRight = inf;

    for (int processed = 0; processed < n; ++processed) {
        int floor = n - 1 - processed;
        int currentCount = count[floor];
        int currentFirst = first[floor];
        int currentLast = last[floor];

        auto traverseBetweenStairs = [&](int startSide, int endSide) -> long long {
            int startPos = (startSide == 0 ? 0 : m + 1);
            int endPos = (endSide == 0 ? 0 : m + 1);
            if (currentCount == 0) return llabs(startPos - endPos);
            long long option1 = llabs(startPos - currentFirst) + (currentLast - currentFirst) + llabs(currentLast - endPos);
            long long option2 = llabs(startPos - currentLast) + (currentLast - currentFirst) + llabs(currentFirst - endPos);
            return min(option1, option2) + currentCount;
        };

        auto finishAnywhere = [&](int startSide) -> long long {
            int startPos = (startSide == 0 ? 0 : m + 1);
            if (currentCount == 0) return 0;
            long long option1 = llabs(startPos - currentFirst) + (currentLast - currentFirst);
            long long option2 = llabs(startPos - currentLast) + (currentLast - currentFirst);
            return min(option1, option2) + currentCount;
        };

        if (processed == n - 1) {
            long long answer = min(dpLeft + finishAnywhere(0), dpRight + finishAnywhere(1));
            cout << answer << '\n';
            return 0;
        }

        long long nextLeft = min(dpLeft + traverseBetweenStairs(0, 0), dpRight + traverseBetweenStairs(1, 0)) + 1;
        long long nextRight = min(dpLeft + traverseBetweenStairs(0, 1), dpRight + traverseBetweenStairs(1, 1)) + 1;
        dpLeft = nextLeft;
        dpRight = nextRight;
    }

    return 0;
}