/*
Megoldás lényege:
Az új résztvevő x-edik perctől x+P-1-edik percig van jelen, és az i-edik emberrel pontosan akkor találkozik, ha Érki_i - P + 1 <= x <= Távi_i. Minden lehetséges x kezdési időponthoz tehát azoknak az embereknek a száma tartozik, akiknek az intervalluma lefedi x-et. Ezt különbségtömbbel gyűjtjük össze: minden ember x-intervallumának kezdeténél +1, a végénél utána -1 áll, majd a prefixösszeg minden x-re megadja a találkozók számát. A válasz a legkisebb értékű x, a legelső érkezés és az utolsó távozás által kijelölt tartományban. Az időigény O(N + maxTávi), ami 100 000 emberre és 10 000 percre gyors.
*/
/*
Hint 1: || Az új résztvevő x-edik perctől x+P-1-edik percig van jelen. Két ember akkor találkozik, ha a jelenléti perceik legalább egy közös percben átfedik egymást. ||
Hint 2: || Egy meglévő ember [Érki, Távi] intervalluma akkor ütközik az x kezdésű résztvevővel, ha Érki <= x+P-1 és x <= Távi. Ez azt jelenti, hogy minden emberhez az x-eknek egy intervalluma tartozik. ||
Hint 3: || Ne minden x-re külön számold meg az embereket, hanem gyűjtsd össze a lefedéseket különbségtömbbel: az intervallum kezdeténél +1, a végénél utána -1, majd egy prefixösszeggel minden x-re megkapod a találkozók számát. ||
Hint 4: || Az x-eket csak a legelső érkezés és az utolsó távozás által kijelölt tartományban keresd, és a minimumnál a kisebb x-et tartsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, p;
    cin >> n >> p;

    vector<int> erk(n), tav(n);
    int minErk = INT_MAX, maxTav = 0;
    for (int i = 0; i < n; i++) {
        cin >> erk[i] >> tav[i];
        minErk = min(minErk, erk[i]);
        maxTav = max(maxTav, tav[i]);
    }

    // az új érkező x-e: minErk <= x és x + p - 1 <= maxTav
    int utolso = maxTav - p + 1;

    vector<int> kul(maxTav + 2, 0);
    for (int i = 0; i < n; i++) {
        int lo = max(minErk, erk[i] - p + 1);
        int hi = min(utolso, tav[i]);
        if (lo <= hi) {
            kul[lo]++;
            kul[hi + 1]--;
        }
    }

    int legjobbX = minErk, legjobbDb = INT_MAX, akt = 0;
    for (int x = 0; x <= utolso; x++) {
        akt += kul[x];
        if (x >= minErk && akt < legjobbDb) {
            legjobbDb = akt;
            legjobbX = x;
        }
    }

    cout << legjobbX << "\n" << legjobbDb << "\n";
    return 0;
}
