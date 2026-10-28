/*
Megoldás lényege:
Minden lefelé lépés (0, 1, 2) eggyel növeli, a felfelé lépés (3) eggyel csökkenti a sor sorszámát, a vízszintes lépések (4, 5) pedig nem változtatják. Mivel a sorszám lépésenként csak eggyel változik, a célba d-edik sorban érkezve bármely út hossza legalább d, és a d hosszú út csak lefelé lépésekből állhat. Ilyen út pontosan egy van: a cél vízszintes indexének d jegyű hármas számrendszerbeli alakja adja a lépéseket, ahol a jegy értéke a lépés száma. Mivel az index akár 100 jegyű is lehet, a jegyeket tömbben tároljuk, a vízszintes lépéseket pedig hármas számrendszerű +1 és -1 művelettel követjük. Az időigény O(K*d), vagyis legfeljebb 10 000 lépés.
*/
/*
Hint 1: || Figyeld meg, mely lépések változtatják a sor sorszámát: csak a 0, 1, 2 lefelé lépés növeli, a 3 csökkenti, a vízszintes lépések pedig egyáltalán nem. Mi a legkevesebb lépés, amellyel a célsorba lehet jutni? ||
Hint 2: || Ha a cél d-edik sorban van, a legrövidebb út legalább d lépés, és d lépés pontosan akkor elég, ha csak lefelé lépünk. Egy csúcs gyerekei a sorukban a 3*p, 3*p+1, 3*p+2 indexű csúcsok, így a lefelé lépések jegyei egyértelműen adják az utat. ||
Hint 3: || Mivel az index akár 100 hármas jegyű is lehet, int-ben nem tárolható. Tárold a jegyeket vektorban: lefelé lépésnél írd a végére a lépés számát, felfelé lépésnél töröld az utolsó jegyet, a vízszintes lépéseknél pedig hármas számrendszerben végezz +1, illetve -1 műveletet átvitellel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int k;
    cin >> k;

    // a csúcs helyét a gyökértől lefelé vett jegyei adják: a lefelé lépés jegyet fűz a végére,
    // a felfelé lépés az utolsó jegyet törli, a vízszintes lépés hármas számrendszerben +1 vagy -1
    vector<int> jegy;
    for (int i = 0; i < k; i++) {
        int lepes;
        cin >> lepes;
        if (lepes <= 2) {
            jegy.push_back(lepes);
        } else if (lepes == 3) {
            jegy.pop_back();
        } else if (lepes == 4) {            // balra: -1
            int j = (int)jegy.size() - 1;
            while (jegy[j] == 0) jegy[j--] = 2;
            jegy[j]--;
        } else {                            // jobbra: +1
            int j = (int)jegy.size() - 1;
            while (jegy[j] == 2) jegy[j--] = 0;
            jegy[j]++;
        }
    }

    // a legrövidebb út a célhoz vezető lefelé lépések sorozata
    cout << jegy.size() << "\n";
    for (size_t i = 0; i < jegy.size(); i++) {
        if (i) cout << ' ';
        cout << jegy[i];
    }
    cout << "\n";
    return 0;
}
