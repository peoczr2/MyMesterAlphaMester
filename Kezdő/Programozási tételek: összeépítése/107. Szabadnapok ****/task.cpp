/*
Megoldás lényege: egy a kezdőnapot rögzítve a legkisebb b, ameddig mindenkinek van szabadnapja, úgy kapható meg, hogy minden emberre
kiválasztjuk a legkisebb olyan szabadnapját, amely nem kisebb a-nál, és ezek maximuma adja b-t.
Az embereket egyenként dolgozzuk fel: egy ember napjait egy mutatóval végigsöpörve kiszámoljuk az egész [1..M] tartományra ezt az értéket,
és egy közös tömbben vesszük a maximumot. Így a memória O(M).
Végül a [a, b] párok közül a legrövidebbet keressük; döntetlennél a kisebb a-t írjuk ki.
Időigény: O(K*M + az összes szabadnap), memóriaigény: O(M).
*/
/*
Hint 1: || Rögzíts egy a kezdőnapot! Az [a, b] intervallumban pontosan akkor van mindenkinek szabadnapja, ha minden emberre b legalább az a-nál nem kisebb első szabadnapja. ||
Hint 2: || Az embereket egymás után dolgozhatod fel: egy közös tömbben minden a-hoz tartsd az eddigi emberek maximumát. Egy ember napjai rendezettek, így egy mutató elég. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, m;
    cin >> k >> m;

    const int INF = m + 1;             // jelzi, hogy nincs több szabadnap
    vector<int> need(m + 2, 1);        // need[a] = max_p (p legkisebb, a-nál nem kisebb szabadnapja)
    vector<int> days;

    for (int p = 0; p < k; p++) {
        int s;
        cin >> s;
        days.resize(s);
        for (int j = 0; j < s; j++) cin >> days[j];

        int j = 0;
        for (int a = 1; a <= m; a++) {
            while (j < s && days[j] < a) j++;
            int nf = (j < s) ? days[j] : INF;
            need[a] = max(need[a], nf);
        }
    }

    int bestA = -1, bestB = -1;
    for (int a = 1; a <= m; a++) {
        if (need[a] > m) continue;  // ehhez a kezdőnaphoz nincs megoldás
        if (bestA < 0 || need[a] - a < bestB - bestA) {
            bestA = a;
            bestB = need[a];
        }
    }
    cout << bestA << " " << bestB << "\n";
    return 0;
}
