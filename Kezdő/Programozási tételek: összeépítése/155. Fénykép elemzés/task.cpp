/*
Megoldás lényege:
Két képpont akkor kerül egy osztályba, ha fényességük különbsége legfeljebb 1. Mivel a tranzitivitás miatt az azonos fényességű pontok is egy osztályba esnek, az osztályok a képen előforduló fényesség-értékekre nézve állnak: egy osztály a fényességek olyan maximális szakasza, ahol minden egész érték előfordul a képen.
Ezért értékenként elég nyilvántartani a darabszámot és a legkisebb/legnagyobb sor- és oszlopindexet. A fényességek 1..100000 tartományban vannak, így egy menetben végigmehetünk az értékeken, az egymást követő előforduló értékeket egy osztályba vonjuk össze. Az időigény O(N·M + 100000).
*/
/*
Hint 1: || Két képpont akkor tartozik egy osztályba, ha az értékeik különbsége legfeljebb 1. A képen szomszédos pixelek nem számítanak, csak a fényesség értéke. Gondold végig, mely értékek kerülnek egy osztályba. ||
Hint 2: || Tömbben tárold értékenként a darabszámot és a legkisebb/legnagyobb sor- és oszlopindexet. Az egymást követő, mind előforduló értékek egy osztályt alkotnak; ezeken a szakaszokon összegezd a darabszámot és a téglalap határait. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAXV = 100000;
    int n, m;
    cin >> n >> m;

    vector<int> cnt(MAXV + 2, 0), r1(MAXV + 2, INT_MAX), c1(MAXV + 2, INT_MAX), r2(MAXV + 2, 0), c2(MAXV + 2, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int f;
            cin >> f;
            cnt[f]++;
            r1[f] = min(r1[f], i);
            c1[f] = min(c1[f], j);
            r2[f] = max(r2[f], i);
            c2[f] = max(c2[f], j);
        }
    }

    int classes = 0;
    long long best = 0;
    int br1 = 0, bc1 = 0, br2 = 0, bc2 = 0;
    int v = 1;
    while (v <= MAXV) {
        if (cnt[v] == 0) {
            v++;
            continue;
        }
        // egy osztály: egymást követő, mind előforduló fényesség-értékek
        long long size = 0;
        int R1 = INT_MAX, C1 = INT_MAX, R2 = 0, C2 = 0;
        while (v <= MAXV && cnt[v] > 0) {
            size += cnt[v];
            R1 = min(R1, r1[v]);
            C1 = min(C1, c1[v]);
            R2 = max(R2, r2[v]);
            C2 = max(C2, c2[v]);
            v++;
        }
        classes++;
        if (size > best) {
            best = size;
            br1 = R1;
            bc1 = C1;
            br2 = R2;
            bc2 = C2;
        }
    }

    cout << classes << "\n"
         << best << "\n"
         << br1 << " " << bc1 << " " << br2 << " " << bc2 << "\n";
    return 0;
}
