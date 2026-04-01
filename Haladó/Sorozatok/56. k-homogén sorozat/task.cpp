/*
Megoldas lenyege:
Egy intervallum akkor K-homogen, ha van benne olyan ertek, amely legalabb hossz-K alkalommal
szerepel, mert ekkor a tobbi legfeljebb K elem torlese utan csak ez az ertek marad.

Ezert csuszoablakkal keressuk a leghosszabb olyan reszsorozatot, amelyben
ablakhossz - leggyakoribb_ertek_darabszama <= K. Az aktualis maximum gyakorisagot pontosan
tartjuk nyilvan: van egy darabszam minden ertekre, es egy masik tomb, amely megmondja,
hany ertek szerepel eppen adott gyakorisaggal. Igy az ablak bal szelenek mozgatasa utan is
O(1) amortizalt ido alatt tudjuk frissiteni a valodi maximumot.
*/
/*
Hint 1: || Az intervallum jo, ha a leggyakoribb elemen kivul legfeljebb K masik elem marad benne. ||
Hint 2: || Ket mutatoval tartsd fenn, hogy a jobb veg fixalasa mellett a bal veg a legkisebb jo helyen legyen. ||
Hint 3: || A maximum gyakorisagot nemcsak novekedeskor, hanem csokkeneskor is pontosan kell kovetni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    vector<int> countByValue(m + 1, 0);
    vector<int> countOfCount(n + 1, 0);

    int left = 0;
    int currentMaxFreq = 0;
    int bestLen = 0;
    int bestPos = 1;

    for (int right = 0; right < n; ++right) {
        int value = a[right];
        int oldCount = countByValue[value];
        if (oldCount > 0) --countOfCount[oldCount];
        int newCount = ++countByValue[value];
        ++countOfCount[newCount];
        currentMaxFreq = max(currentMaxFreq, newCount);

        while (right - left + 1 - currentMaxFreq > k) {
            int removeValue = a[left++];
            int oldRemoveCount = countByValue[removeValue];
            --countOfCount[oldRemoveCount];
            int newRemoveCount = --countByValue[removeValue];
            if (newRemoveCount > 0) ++countOfCount[newRemoveCount];
            while (currentMaxFreq > 0 && countOfCount[currentMaxFreq] == 0) {
                --currentMaxFreq;
            }
        }

        int len = right - left + 1;
        if (len > bestLen) {
            bestLen = len;
            bestPos = left + 1;
        }
    }

    cout << bestLen << '\n' << bestPos << '\n';
    return 0;
}