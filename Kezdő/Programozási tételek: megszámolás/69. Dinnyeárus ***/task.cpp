/*
Megoldás lényege:
Minden napra két számot kell megadni: hány korábbi napon volt az ár olcsóbb, és hány későbbi napon volt drágább.
Mivel az árak 1 és 100 közötti egészek, elég egy 101 elemű számláló tömb: balról jobbra haladva az eddigi napok áraiból számoljuk a nála kisebbeket,
jobbról balra haladva pedig a nála nagyobbakat. Egy naphoz így O(100) munka kell, az összidő O(N·100), ami N ≤ 20 000 mellett kb. 2·10^6 művelet.
*/
/*
Hint 1: || Minden napra két külön kérdés van: hány korábbi nap ára volt kisebb, és hány későbbi nap ára volt nagyobb. Ez a két szám egymástól független, külön-külön számolható. ||
Hint 2: || Mivel az árak legfeljebb 100 különböző értéket vehetnek fel, tarthatsz egy számláló tömböt, ami azt mutatja, hány korábbi nap volt az egyes árakon. Egy napnál az ennél kisebb árak darabszámát kell összegezni. ||
Hint 3: || A jobbról balra haladó bejárás ugyanígy működik fordított irányban: a későbbi napok számlálójából a nála nagyobb árakat összegezd. Egy N² méretű páros ellenőrzés a 20 000 napra már túl lassú volna. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> d(n);
    for (int i = 0; i < n; i++) cin >> d[i];

    vector<int> before(n), after(n);
    vector<int> cntBefore(101, 0), cntAfter(101, 0);

    // balról jobbra: az i-edik nap előtt hány nap volt olcsóbb
    for (int i = 0; i < n; i++) {
        int s = 0;
        for (int p = 1; p < d[i]; p++) s += cntBefore[p];
        before[i] = s;
        cntBefore[d[i]]++;
    }

    // jobbról balra: az i-edik nap után hány nap volt drágább
    for (int i = n - 1; i >= 0; i--) {
        int s = 0;
        for (int p = d[i] + 1; p <= 100; p++) s += cntAfter[p];
        after[i] = s;
        cntAfter[d[i]]++;
    }

    for (int i = 0; i < n; i++) {
        cout << before[i] << " " << after[i] << "\n";
    }
    return 0;
}
