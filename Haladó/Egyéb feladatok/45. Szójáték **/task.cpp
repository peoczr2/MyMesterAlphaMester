/*
Megoldás lényege:
A keresett szó a szövegnek részsorozata (nem összefüggő részszöveg), és a legrövidebb olyan szövegrészt kérjük, amelyben a szó részsorozatként megtalálható. Minden i pozícióra a legrövidebb i-nél végződő ablak a legnagyobb kezdőindexből adódik, ahonnan a szó még részsorozatként illeszkedik. Ezt a st[j] tömbbel követjük: st[j] az a legnagyobb kezdőindex, ahonnan a szó első j karaktere az eddigi szövegben részsorozatként megtalálható. Ha a szó j-edik karaktere egyezik az aktuális szövegkarakterrel, st[j+1] a régi st[j] értékét kapja (j = 0 esetén az aktuális i-t), egyébként marad; a frissítést egy másik tömbbe végezzük, hogy a régi értékek ne keveredjenek. Ha az aktuális karakter a szó utolsó betűje, az ablak hossza i - st[M] + 1, és a szigorúan rövidebb ablakot megtartva az első legrövidebb ablak (a legkisebb kezdőindexszel) marad meg. Az idő O(N·M), a memória a szövegen kívül O(M·|Σ|), ahol |Σ| a szóban szereplő különböző karakterek száma.
*/
/*
Hint 1: || A szó nem összefüggő részszövegként, hanem részsorozatként szerepel a szövegben. Minden szövegpozícióra azt érdemes meghatározni, hogy legkésőbb honnan kezdve lehet a szó első j karakterét megtalálni úgy, hogy az i-edik karakterig minden a helyén legyen. ||
Hint 2: || Egy tömbben tartsd nyilván, hogy a szó első j karaktere legkésőbb melyik kezdőindextől illeszthető be az eddig feldolgozott szövegbe. Egy szövegkarakternél csak a szó azon indexeit frissítsd, ahol ugyanaz a karakter áll, és a régi értékeket használd. ||
Hint 3: || Ha a szó utolsó karaktere egyezik az i-edik szövegkarakterrel, az ablak hossza i - (a legkésőbbi kezdőindex) + 1. A legrövidebb ablakot a végpont szerint növekvő sorrendben vizsgáld, és csak szigorúan rövidebbnél írd felül az eredményt, így a legkisebb kezdőindexet kapod. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    string word, text;
    cin >> m >> word >> n >> text;

    // A szóban szereplő karakterek sorszáma (id), és eq[r*m + j] = 1, ha word[j] az r-edik karakter.
    vector<int> id(256, -1);
    int R = 0;
    for (char ch : word) {
        unsigned char u = (unsigned char)ch;
        if (id[u] < 0) id[u] = R++;
    }
    vector<int> eq((size_t)R * m, 0);
    for (int j = 0; j < m; ++j) eq[(size_t)id[(unsigned char)word[j]] * m + j] = 1;

    // st[j]: a legnagyobb kezdőindex, ahonnan word[0..j-1] részsorozatként megtalálható (-1: nincs).
    vector<int> st(m + 1, -1), nst(m + 1, -1);
    int bestLen = INT_MAX;
    int bestStart = -1;

    for (int i = 0; i < n; ++i) {
        int r = id[(unsigned char)text[i]];
        if (r < 0) continue;  // a szóban nem szereplő karakter nem változtat semmit

        const int* e = &eq[(size_t)r * m];
        const int* A = st.data();
        int* B = nst.data();
        B[1] = e[0] ? i : A[1];
        for (int j = 1; j < m; ++j) B[j + 1] = e[j] ? A[j] : A[j + 1];
        swap(st, nst);

        if (e[m - 1] && st[m] != -1) {
            int len = i - st[m] + 1;
            if (len < bestLen) {
                bestLen = len;
                bestStart = st[m];
            }
        }
    }

    if (bestStart == -1) {
        cout << "0 0\n";
    } else {
        cout << bestStart + 1 << ' ' << bestLen << '\n';
    }
    return 0;
}
