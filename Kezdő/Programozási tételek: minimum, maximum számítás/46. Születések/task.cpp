/*
Megoldás lényege:
Az évek száma mindössze 118 (1900 és 2017 között), ezért egy tömbben évenként megszámoljuk a születéseket. A legrövidebb intervallumhoz minden kezdőévből addig bővítjük a végévet, amíg a darabszámok összege el nem éri a felet (2·összeg ≥ N), és az első ilyen végévet vesszük. A legrövidebb hosszt szigorú összehasonlítással tartjuk, így holtverseny esetén a korábbi intervallum marad. A leghosszabb üres időszak az első és az utolsó születési év között van: ezen belül az egymást követő nulla darabszámú évek szakaszait végigjárva a leghosszabbat keressük, ismét a korábbit előnyben részesítve. Az időigény O(N + 118²), a memóriaigény O(118).
*/
/*
Hint 1: || Mivel az évek száma csak 118, elég egy tömbben tárolni, hogy melyik évben hányan születtek. ||
Hint 2: || A legrövidebb intervallumhoz rögzíts egy kezdőévet, és keresd meg mellé a legkisebb végévet, ahol a darabszámok összege már legalább N/2; ezt minden kezdőévre megteheted. ||
Hint 3: || A leghosszabb üres időszakhoz csak az első és az utolsó születési év közti éveket nézd: keresd meg az egymást követő nulla darabszámú éveket, és vedd a leghosszabb ilyen szakaszt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int FIRST = 1900;
    const int LAST = 2017;
    const int YEARS = LAST - FIRST + 1;

    int n;
    cin >> n;

    vector<int> cnt(YEARS, 0);
    for (int i = 0; i < n; i++) {
        int y;
        cin >> y;
        cnt[y - FIRST]++;
    }

    // Legrövidebb intervallum, amely alatt legalább a fele született
    int bestA = -1, bestB = -1, bestLen = INT_MAX;
    for (int a = 0; a < YEARS; a++) {
        int sum = 0;
        for (int b = a; b < YEARS; b++) {
            sum += cnt[b];
            if (2 * sum >= n) {
                if (b - a < bestLen) {
                    bestLen = b - a;
                    bestA = a;
                    bestB = b;
                }
                break;
            }
        }
    }
    cout << bestA + FIRST << " " << bestB + FIRST << "\n";

    // Leghosszabb üres időszak az első és az utolsó születés között
    int first = -1, last = -1;
    for (int y = 0; y < YEARS; y++) {
        if (cnt[y] > 0) {
            if (first < 0) first = y;
            last = y;
        }
    }

    int gapA = -1, gapB = -1, gapLen = -1;
    int y = first;
    while (y <= last) {
        if (cnt[y] > 0) {
            y++;
            continue;
        }
        int start = y;
        while (y <= last && cnt[y] == 0) y++;
        int end = y - 1;
        if (end - start > gapLen) {
            gapLen = end - start;
            gapA = start;
            gapB = end;
        }
    }

    if (gapA < 0) cout << "0 0\n";
    else cout << gapA + FIRST << " " << gapB + FIRST << "\n";
    return 0;
}
