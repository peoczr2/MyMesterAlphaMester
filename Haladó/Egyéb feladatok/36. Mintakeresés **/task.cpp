/*
Megoldás lényege:
Minden j szövegpozícióra azt kell tudni, melyik a legkésőbbi kezdőindex, ahonnan a minta valamely prefixe
részsorozatként még megvan úgy, hogy a j-edik karakterrel végződik. Ez egy M hosszú tömbben tárolható:
st[k] a minta első k+1 karakterének legkésőbbi kezdőindexe. Ha a szöveg j-edik karaktere egyezik a minta
k-adik karakterével, st[k] az st[k-1] értékre frissül (a magasabb k-kat lefelé haladva, hogy ugyanaz a
karakter ne kerüljön kétszer felhasználásra). Ha st[M-1] érvényes, a [st[M-1], j] ablak tartalmazza a mintát,
és ez a j-re nézve a legrövidebb. A legrövidebb ablakot szigorú összehasonlítással tartjuk meg, így azonos
hosszúság esetén a korábban záródó, vagyis kisebb kezdetű ablak marad. A szöveg UTF-8 kódolású, ezért
a karaktereket kódpontonként (nem bájtonként) számoljuk. Az idő O(N * M).
*/
/*
Hint 1: || Gondolkodj azon, hogy minden jobb végpontra melyik a legkésőbbi kezdőpont, ahonnan a minta még részsorozatként megtalálható. ||
Hint 2: || Tárolj egy M hosszú tömböt: minden k-ra azt az indexet, ahol a minta első k+1 karaktere legkésőbb kezdődik. A szöveget karakterenként bejárva frissítsd, a magasabb indexektől indulva lefelé. ||
Hint 3: || Ha a legrövidebb ablakból több is van, a korábban záródó ablak kezdete kisebb, ezért a szigorú összehasonlítás (<) elég. A "nincs ilyen" esetet külön kell kezelni. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Levágja a sor végi kocsivissza és újsor karaktereket.
string sorVege(string s) {
    while (!s.empty() && (s.back() == '\r' || s.back() == '\n')) s.pop_back();
    return s;
}

// A UTF-8 szöveg karaktereit (kódpontjait) adja vissza; a többbájtos betűk (pl. ő, á) egy karakternek számítanak.
vector<unsigned> kodpontok(const string& s) {
    vector<unsigned> ki;
    size_t i = 0, n = s.size();
    while (i < n) {
        unsigned char b = s[i];
        size_t len = 1;
        unsigned cp = b;
        if (b >= 0xF0 && b <= 0xF7) { len = 4; cp = b & 0x07; }
        else if (b >= 0xE0 && b <= 0xEF) { len = 3; cp = b & 0x0F; }
        else if (b >= 0xC2 && b <= 0xDF) { len = 2; cp = b & 0x1F; }
        bool jo = i + len <= n;
        for (size_t t = 1; jo && t < len; t++) {
            unsigned char cb = s[i + t];
            if ((cb & 0xC0) != 0x80) jo = false;
            else cp = (cp << 6) | (cb & 0x3F);
        }
        if (!jo) {
            len = 1;
            cp = b;
        }
        ki.push_back(cp);
        i += len;
    }
    return ki;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string sor;
    getline(cin, sor);                  // a minta hossza (nem kell, a szövegből számoljuk)
    string minta;
    getline(cin, minta);
    getline(cin, sor);                  // a szöveg hossza (nem kell)
    string szoveg;
    getline(cin, szoveg);
    vector<unsigned> mk = kodpontok(sorVege(minta));
    vector<unsigned> sk = kodpontok(sorVege(szoveg));

    int M = mk.size();
    int N = sk.size();

    // st[k]: a minta első k+1 karakterének legkésőbbi kezdőindexe, -1 ha még nincs ilyen.
    vector<int> st(M, -1);
    int legrovidebb = INT_MAX, bal = -1, jobb = -1;

    for (int j = 0; j < N; j++) {
        for (int k = M - 1; k >= 0; k--) {
            if (sk[j] != mk[k]) continue;
            if (k == 0) st[0] = j;
            else if (st[k - 1] != -1) st[k] = st[k - 1];
        }
        if (M > 0 && st[M - 1] != -1) {
            int hossz = j - st[M - 1] + 1;
            if (hossz < legrovidebb) {
                legrovidebb = hossz;
                bal = st[M - 1];
                jobb = j;
            }
        }
    }

    if (bal == -1) cout << "0 0\n";
    else cout << bal + 1 << " " << jobb + 1 << "\n";
    return 0;
}
