/*
Megoldás lényege:
Kétmutatós (csúszóablakos) technikát használunk: a jobb végpontot balról jobbra léptetjük, és
figyeljük, hány R-beli betű fordul elő már az ablakban (kis- és nagybetű egyenlő, ezért
mindent kisbetűre alakítunk). Amint az ablak tartalmazza az R összes betűjét, a bal végpontot
addig léptetjük előre, amíg a feltétel még teljesül, és minden ilyen ablak hosszát
összehasonlítjuk a legrövidebbel. Minden karaktert legfeljebb kétszer érintünk, ezért az
időigény O(H), a memóriaigény pedig konstans (26 elemű tömb). Azonos hosszúságú megoldások
esetén a szövegben elsőként előforduló szakaszt írjuk ki.
*/
/*
Hint 1: || A feladat olyan legrövidebb szakaszt keres, amely tartalmazza az R betűinek mindegyikét; a jobb végpontot növelve, a bal végpontot pedig a feltétel megtartása mellett léptetve érdemes végigmenni a szövegen. ||
Hint 2: || Egy 26 elemű tömbben tartsd nyilván, hogy az aktuális szakaszban az egyes betűkből hány darab van, és külön számlálóban azt, hogy az R-ből hány betű szerepel már legalább egyszer; a kis- és nagybetűket a tolower segítségével egyesítsd. ||
Hint 3: || Ha az aktuális szakasz teljesíti a feltételt, mentsd el a hosszát, ha az rövidebb a korábbinál; utána a bal oldali karaktert kivéve addig szűkíts, amíg már nem teljesül. A kiírandó sorszámok az első és az utolsó karakter helye, 1-től számozva. ||
*/
#include <bits/stdc++.h>
using namespace std;

int code(char ch) {
    if (!isalpha(static_cast<unsigned char>(ch))) return -1;
    return tolower(static_cast<unsigned char>(ch)) - 'a';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line, text, letters;
    getline(cin, line);      // a szöveg hossza (nem szükséges)
    getline(cin, text);      // a szöveg
    getline(cin, letters);   // az R betűhalmaz

    if (!text.empty() && text.back() == '\r') text.pop_back();
    if (!letters.empty() && letters.back() == '\r') letters.pop_back();

    bool need[26] = {false};
    int needCnt = 0;
    for (char ch : letters) {
        int k = code(ch);
        if (k >= 0 && !need[k]) {
            need[k] = true;
            needCnt++;
        }
    }

    int n = text.size();
    vector<int> cnt(26, 0);
    int have = 0;
    int bestLen = INT_MAX, bl = -1, br = -1;
    int l = 0;

    for (int r = 0; r < n; r++) {
        int k = code(text[r]);
        if (k >= 0 && need[k] && cnt[k]++ == 0) have++;

        while (have == needCnt && l <= r) {
            if (r - l + 1 < bestLen) {
                bestLen = r - l + 1;
                bl = l;
                br = r;
            }
            int kl = code(text[l]);
            if (kl >= 0 && need[kl] && --cnt[kl] == 0) have--;
            l++;
        }
    }

    if (bestLen == INT_MAX)
        cout << -1 << '\n';
    else
        cout << bl + 1 << ' ' << br + 1 << '\n';
    return 0;
}
