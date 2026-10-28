/*
   Azonosító kód: a megadott betűmultihalmaz következő lexikografikus
   permutációját keressük. Ez pontosan a next_permutation feladat: a
   std::next_permutation az ismétlődő betűket is helyesen kezelve adja a
   következő lexikografikusan nagyobb átrendezést, és false-t ad vissza,
   ha a sorozat már a legnagyobb (csökkenő) átrendezés. A bemenet N kódot
   tartalmaz, mindegyikre külön hívjuk; egy kódra az idő O(L), ahol L <= 100
   a kód hossza, így az összes kódra O(N * L).
*/
/*
Hint 1: || A bemenet első száma a kódok száma, utána minden sorban egy kód áll. Minden kódra külön kell eldönteni, hogy van-e nála nagyobb, ugyanazokból a betűkből álló kód, és ha van, azt kell kiírni. ||
Hint 2: || A kódot jobbról balra végigvizsgálva keresd meg az első olyan i pozíciót, ahol s[i] kisebb, mint s[i+1]. Ha ilyen pozíció nincs, a kód már a legnagyobb, és a válasz NINCS. ||
Hint 3: || Az i pozíció utáni részben keresd meg a legkisebb olyan betűt, amely nagyobb s[i]-nél (a jobb oldali rész csökkenő, ezért ez a legjobbra eső ilyen betű), cseréld meg vele s[i]-t, majd az i+1-től kezdődő részt fordítsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        if (next_permutation(s.begin(), s.end())) cout << s << '\n';
        else cout << "NINCS\n";
    }
    return 0;
}