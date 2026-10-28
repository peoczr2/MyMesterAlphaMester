/*
Megoldás lényege:
A lánc körkörös, ezért egy szakasz az utolsó és az első gyöngy között is folytatódhat. Minden i kezdőpontból megszámoljuk, hány egymás utáni azonos színű gyöngy van körben i-től kezdve, az indexeket modulo N kezelve. A legnagyobb hosszt és a hozzá tartozó színt tároljuk; csak szigorúan nagyobb hossz esetén cserélünk, így döntetlennél a bemenetben korábban kezdődő szakasz színe marad. Mivel N ≤ 100, az O(N^2) bejárás bőven belefér az időlimitbe.
*/
/*
Hint 1: || A lánc körkörös: a legutolsó gyöngy után az első következik, ezért a szakasz a lánc végéről az elejére is átnyúlhat. Egy sima lineáris bejárás ezt az esetet kihagyná. ||
Hint 2: || A gyöngyökre körkörös indexeléssel hivatkozz: a kezdőponttól k lépésre álló gyöngy indexe (i + k) mod N. Minden kezdőpontból számold meg, meddig tart az azonos szín. ||
Hint 3: || Elég minden kezdőpontból a futás hosszát megszámolni, és a legnagyobb találatnál megjegyezni a hosszt és a színt. Az N ≤ 100 miatt a teljes bejárás gyors. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    string gyongyok;
    for (int i = 0; i < n; i++) {
        char szin;
        cin >> szin;
        gyongyok += szin;
    }

    int legjobb_hossz = 0;
    char legjobb_szin = gyongyok[0];

    for (int i = 0; i < n; i++) {
        int hossz = 1;
        while (hossz < n && gyongyok[(i + hossz) % n] == gyongyok[i]) {
            hossz++;
        }
        if (hossz > legjobb_hossz) {
            legjobb_hossz = hossz;
            legjobb_szin = gyongyok[i];
        }
    }

    cout << legjobb_hossz << "\n" << legjobb_szin << "\n";
    return 0;
}
