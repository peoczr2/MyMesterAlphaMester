/*
Megoldás lényege: a szavakat lexikografikus sorrendben tekintjük, ahol a prefix megelőzi
a kiterjesztéseit. Nem kell rangot számolni (az nagy K-nál túlcsordulna), elég közvetlenül
megkeresni a szomszédos szót. Rákövetkező szó: ha a bemenet lassú és még nem érte el a K
hosszt, a szó végére a legkisebb megengedett betű kerül; egyébként a leghosszabb lassú
prefix végétől visszafelé keressük azt a legkésőbbi pozíciót, ahol a betű az ábécében
megnövelhető, és a prefixet ott vágjuk le. Előző szó: az ilyen pozíción csökkentett betű
után a maradékot K hosszig a legnagyobb megengedett betűkkel töltjük ki; ha nincs ilyen
pozíció, a leghosszabb lassú prefix lesz az előző szó. Az idő O(26 * K), a memória O(K).
*/
/*
Hint 1: || A rákövetkező szó vagy a bemenet végére fűz egy betűt, vagy egy prefixében növel egy betűt. Nem kell a teljes sorrendet bejárni: elég a legkésőbbi jó pozíciót megtalálni. ||
Hint 2: || Keresd meg a leghosszabb lassan változó prefixet. Csak ennek a pozícióin belül változtathatsz: a módosított betűnek a bal szomszédjához kell illeszkednie, és a jobb szélétől visszafelé keresd a legkésőbbi jó pozíciót. ||
Hint 3: || Ha a szó egy pozíción változik, a hosszát K-ig a megengedett szélső betűkkel (a legnagyobbal az előzőhöz, a legkisebbel a következőhöz) töltheted ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

static bool allowed(int a, int b) { return abs(a - b) <= 1; }

static string toText(const vector<int>& w) {
    string t;
    for (int c : w) t.push_back(char('a' + c));
    return t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    string text;
    cin >> K >> text;
    int n = text.size();
    vector<int> s(n);
    for (int i = 0; i < n; ++i) s[i] = text[i] - 'a';

    if (n == 0) {
        cout << "-\na\n";
        return 0;
    }

    // p: a leghosszabb lassan változó prefix hossza
    int p = 1;
    while (p < n && allowed(s[p - 1], s[p])) ++p;

    // Következő szó
    vector<int> nxt;
    bool hasNxt = false;
    if (p == n && n < K) {
        nxt = s;
        nxt.push_back(max(0, s[n - 1] - 1));
        hasNxt = true;
    } else {
        for (int j = min(p, n - 1); j >= 0 && !hasNxt; --j) {
            for (int c = s[j] + 1; c < 26; ++c) {
                if (j == 0 || allowed(c, s[j - 1])) {
                    nxt.assign(s.begin(), s.begin() + j);
                    nxt.push_back(c);
                    hasNxt = true;
                    break;
                }
            }
        }
    }

    // Előző szó
    int M0 = min(p, n - 1);
    int jStar = -1, cStar = -1;
    for (int j = M0; j >= 0 && jStar < 0; --j) {
        for (int c = s[j] - 1; c >= 0; --c) {
            if (j == 0 || allowed(c, s[j - 1])) {
                jStar = j;
                cStar = c;
                break;
            }
        }
    }
    vector<int> prv;
    bool hasPrv = false;
    if (jStar == M0 && jStar >= 0) {
        prv.assign(s.begin(), s.begin() + jStar);
        prv.push_back(cStar);
        while ((int)prv.size() < K) prv.push_back(min(25, prv.back() + 1));
        hasPrv = true;
    } else if (M0 >= 1) {
        prv.assign(s.begin(), s.begin() + M0);
        hasPrv = true;
    }

    cout << (hasPrv ? toText(prv) : string("-")) << '\n';
    cout << (hasNxt ? toText(nxt) : string("-")) << '\n';
    return 0;
}
