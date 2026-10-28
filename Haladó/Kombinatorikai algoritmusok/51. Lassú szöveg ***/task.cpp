/*
Megoldás lényege:
A lassan változó szavak lexikografikus sorrendjében a szomszédok a szó végén dőlnek el. Az előző szót úgy kapjuk, hogy a szó utolsó betűjét a nála kisebb szomszédjára cseréljük (ha lehet), majd a szót a lehető legnagyobb szomszédos betűkkel K hosszúra egészítjük ki; ha a csere nem lehetséges, az előző szó a szó egy betűvel rövidebb prefixe. A következő szó: ha a szó rövidebb K-nál, a végére a legkisebb szomszédos betű kerül; különben a jobbról első olyan helyet keressük, ahol a betű nagyobb szomszédra cserélhető, a szót ott levágjuk, és a cserélt betűt írjuk a végére. Minden lépés O(K) munka, ezért nem kell a szavak sorszámát (rangját) kiszámolni, ami K = 10 000 esetén messze nem férne el egy 64 bites számban. A megoldás O(K) időben fut.
*/
/*
Hint 1: || A szavak lexikografikus sorrendjében egy szó közvetlen szomszédja általában a szó végéhez közel áll, ezért először az utolsó betű lecserélését próbáld meg. ||
Hint 2: || Az előző szónál a legutolsó betűt a nála kisebb szomszédjára cseréld (ha van ilyen), majd a szót a lehető legnagyobb szomszédos betűkkel K hosszúra egészítsd ki. Ha nincs ilyen csere, az előző szó a szó egy betűvel rövidebb prefixe. ||
Hint 3: || A következő szónál: ha a szó rövidebb K-nál, a végére a legkisebb szomszédos betű kerül. Ha a szó már K hosszú, keresd meg a jobbról első olyan pozíciót, ahol a betű nagyobb szomszédra cserélhető: a szót ott levágva, a cserélt betűvel kapod a következő szót. ||
*/
#include <bits/stdc++.h>
using namespace std;

int K;

// A legnagyobb, legfeljebb K hosszú szó, amely a p prefixszel kezdődik (p érvényes).
string largestWithPrefix(string p) {
    while ((int)p.size() < K) {
        int last = p.back() - 'a';
        p.push_back(char('a' + (last < 25 ? last + 1 : last - 1)));
    }
    return p;
}

// Az előző szó (üres szót nem számolunk), vagy "-", ha nincs.
string previousWord(const string& s) {
    int n = (int)s.size();
    if (n == 0) return "-";
    int cur = s[n - 1] - 'a';
    int prv = n >= 2 ? s[n - 2] - 'a' : -1;
    for (int c = cur - 1; c >= 0; --c) {
        if (prv == -1 || abs(c - prv) == 1) {
            return largestWithPrefix(s.substr(0, n - 1) + char('a' + c));
        }
    }
    return n >= 2 ? s.substr(0, n - 1) : "-";
}

// A következő szó, vagy "-", ha nincs.
string nextWord(const string& s) {
    int n = (int)s.size();
    if (n == 0) return "a";
    if (n < K) {
        int last = s[n - 1] - 'a';
        return s + char('a' + (last == 0 ? 1 : last - 1));
    }
    for (int j = n - 1; j >= 0; --j) {
        int cur = s[j] - 'a';
        int prv = j >= 1 ? s[j - 1] - 'a' : -1;
        for (int c = cur + 1; c < 26; ++c) {
            if (prv == -1 || abs(c - prv) == 1) {
                return s.substr(0, j) + char('a' + c);
            }
        }
    }
    return "-";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> K >> s;
    cout << previousWord(s) << '\n' << nextWord(s) << '\n';
    return 0;
}
