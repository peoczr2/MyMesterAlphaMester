/*
   Következő azonosító: a szabályos azonosító a benne szereplő különböző
   betűk permutációja, ezért a következő szabályos azonosító a következő
   lexikografikus permutáció. A std::next_permutation pontosan ezt adja:
   megkeresi a jobbról első olyan i pozíciót, ahol s[i] < s[i+1], az i utáni
   rész s[i]-nél nagyobb legkisebb betűjével cseréli meg s[i]-t, végül az
   i+1-től kezdődő részt megfordítja. Ha nincs ilyen i, az azonosító már az
   utolsó (csökkenő) permutáció, és a válasz NINCS. Egy azonosítóra az idő O(L),
   ahol L a betűk száma.
*/
/*
Hint 1: || Próbáld ki kézzel: az abcd után az abdc, az abdc után az acbd következik. Jobbról balra haladva keresd az első olyan betűt, amely kisebb a jobb oldali szomszédjánál: az abcd esetén ez a c, az abdc esetén a b. ||
Hint 2: || Az így kiválasztott betű utáni rész csökkenő sorrendű. Keresd meg benne a legkisebb olyan betűt, amely nagyobb a kiválasztott betűnél, cseréld meg vele, majd a kiválasztott pozíciótól jobbra eső részt fordítsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;
    if (next_permutation(s.begin(), s.end())) cout << s << '\n';
    else cout << "NINCS\n";
    return 0;
}