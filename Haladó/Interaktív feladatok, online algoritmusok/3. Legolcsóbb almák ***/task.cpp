/*
Megoldás lényege:
Az eddigi napok közül a K legolcsóbbat (ár, sorszám) párként tartjuk nyilván egy rendezett halmazban. Új nap érkezésekor
beszúrjuk, és ha így K+1 elem lenne, a legnagyobb párt (a legdrágább napot, egyenlő árnál a későbbit) eldobjuk. Így
mindig az lesz a halmazban, amely a lexikografikusan legkisebb sorozatot adja. A kiíráshoz a halmaz napjait növekvő
sorrendben egy jelölőtömb végigjárásával adjuk át az olcsobbak eljárásnak. Időigény: O(N log N + N·K).
*/
/*
Hint 1: || Minden nap után a legolcsóbb K nap halmazát kell ismerned. Egy új nap csak úgy kerülhet be, ha a halmaz legdrágább elemét kiszorítja. ||
Hint 2: || Tárold az eddigi legolcsóbb napokat (ár, sorszám) párként rendezett halmazban: beszúrás és a legnagyobb elem eldobása O(log N). A sorszám második kulcs, így egyenlő árnál a korábbi nap marad. ||
Hint 3: || Az X tömböt növekvő sorszámú napokból építsd fel: egy jelölőtömbbel minden nap után 1-től az aktuális napig végigmész, és a jelölt napokat sorban beírod X-be. ||
*/
#include "alma.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = getN();
    int k = getK();
    set<pair<int, int>> chosen;  // az eddigi K legolcsóbb nap: (ár, sorszám)
    vector<char> inSet(n + 1, 0);
    static int X[maxn];
    for (int i = 1; i <= n; i++) {
        int p = ar();
        chosen.insert({p, i});
        inSet[i] = 1;
        if ((int)chosen.size() > k) {
            auto worst = *chosen.rbegin();
            chosen.erase(prev(chosen.end()));
            inSet[worst.second] = 0;
        }
        if (i >= k) {
            int cnt = 0;
            for (int j = 1; j <= i; j++)
                if (inSet[j]) X[cnt++] = j;
            olcsobbak(X);
        }
    }
    return 0;
}
