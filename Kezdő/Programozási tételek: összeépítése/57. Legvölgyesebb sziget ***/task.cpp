/*
Megoldás lényege:
A szigetek a nullától különböző mérések egybefüggő szakaszai, határaikat a 0 értékek jelzik.
Egy szigeten belül az egyenlő magasságú, egymás utáni mérések egy futamot alkotnak, és egy futam akkor völgy, ha a bal és a jobb szomszédja is nagyobb nála.
Egy lapos völgyfenék, vagyis egy egyenlő magasságú futam egy völgynek számít, így a völgyeket futamonként számoljuk.
A legtöbb völggyel rendelkező sziget első és utolsó pozitív mérésének sorszámát írjuk ki, ha pedig nincs völgy, a válasz 0.
A megoldás egyetlen bejárással, O(N) időben fut.
*/
/*
Hint 1: || A szigetek a nullától különböző mérések egybefüggő szakaszai: a bejárás során a 0 értékek jelzik a sziget határait. ||
Hint 2: || Egy sziget belsejében az egyenlő magasságú, egymás utáni mérések egy futamot alkotnak; az a futam völgy, amelynek a bal és a jobb szomszédja is magasabb, és ezt futamonként, nem mérésenként számold. ||
Hint 3: || Minden szigetre számold meg a völgyeket, és tartsd nyilván az eddigi legtöbb völgyet tartalmazó sziget határait; csak szigorúan több völgy esetén írd felül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    int bestValleys = 0, bestL = 0, bestR = 0;

    int l = 0;
    while (l < n) {
        if (a[l] == 0) {
            l++;
            continue;
        }
        // a sziget: a [l..r] szakasz, minden eleme pozitív
        int r = l;
        while (r + 1 < n && a[r + 1] > 0) r++;

        int valleys = 0;
        int j = l;
        while (j <= r) {
            // egyenlő magasságú futam: [j..k]
            int k = j;
            while (k + 1 <= r && a[k + 1] == a[j]) k++;
            // völgy: a futamnak van bal és jobb szomszédja a szigeten belül, és mindkettő magasabb
            if (j > l && k < r && a[j - 1] > a[j] && a[k + 1] > a[j]) valleys++;
            j = k + 1;
        }

        if (valleys > bestValleys) {
            bestValleys = valleys;
            bestL = l;
            bestR = r;
        }
        l = r + 1;
    }

    if (bestValleys == 0) cout << 0 << "\n";
    else cout << bestL + 1 << " " << bestR + 1 << "\n";
    return 0;
}
