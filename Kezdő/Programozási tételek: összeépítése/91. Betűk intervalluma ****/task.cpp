/*
Jobb végpontonként (a szöveg r-edik karakterénél) megnézzük, meddig nyúlhat vissza a bal végpont úgy, hogy az intervallum még tartalmazza az R-beli összes betűt. Ez a legnagyobb bal végpont: az R-beli betűk utolsó előfordulásainak minimuma. Az utolsó előfordulásokat egy 26 elemű tömbben tartjuk nyilván, így minden karakter állandó munkával feldolgozható. Az összes jobb végpontra kapott intervallumok közül a legrövidebbet tartjuk meg; egyenlő hossz esetén a később kapott (jobb végű) intervallumot, ahogy a minta is várja. Az időigény O(26·H), a memóriaigény O(H).
*/
/*
Hint 1: || A nagy- és kisbetűk egyenlők, ezért mindent kisbetűként kezelj. A szöveg minden karakterének a sorszámát számon kell tartani, de csak az R-beli betűk érdekesek. ||
Hint 2: || Tartsd nyilván minden betű utolsó előfordulását. Egy r jobb végponthoz a legjobb bal végpont az R-beli betűk utolsó előfordulásainak minimuma, és az ilyen [bal, r] intervallumok közül a legrövidebbet keresd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string fejlec;
    getline(cin, fejlec); // a szöveg hossza, a feldolgozáshoz nem kell
    string szoveg, betuk;
    getline(cin, szoveg);
    getline(cin, betuk);

    while (!szoveg.empty() && szoveg.back() == '\r') szoveg.pop_back();
    while (!betuk.empty() && betuk.back() == '\r') betuk.pop_back();

    bool kell[26] = {false};
    int kellDb = 0;
    for (char ch : betuk) {
        if (isalpha((unsigned char)ch)) {
            int idx = tolower((unsigned char)ch) - 'a';
            if (!kell[idx]) {
                kell[idx] = true;
                kellDb++;
            }
        }
    }
    if (kellDb == 0) {
        cout << -1 << "\n";
        return 0;
    }

    vector<int> utolso(26, -1); // az egyes betűk utolsó előfordulása (0-tól számozva)
    int legrovidebb = INT_MAX, bal = -1, jobb = -1;
    for (int r = 0; r < (int)szoveg.size(); r++) {
        unsigned char ch = szoveg[r];
        if (isalpha(ch)) utolso[tolower(ch) - 'a'] = r;

        bool mind = true;
        int legkorabbi = INT_MAX;
        for (int c = 0; c < 26 && mind; c++) {
            if (!kell[c]) continue;
            if (utolso[c] < 0) mind = false;
            else legkorabbi = min(legkorabbi, utolso[c]);
        }
        if (!mind) continue;

        int hossz = r - legkorabbi + 1;
        if (hossz <= legrovidebb) {
            legrovidebb = hossz;
            bal = legkorabbi;
            jobb = r;
        }
    }

    if (bal < 0) cout << -1 << "\n";
    else cout << bal + 1 << " " << jobb + 1 << "\n";
    return 0;
}
