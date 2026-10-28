/*
Megoldás lényege:
A mutatók állását félfokos egységben számoljuk, így a 0,5 fokos lépések is egész számok lesznek. Egy óra 60 egység (30 fok), az óramutató egy perc alatt 1 egységet (0,5 fok) halad, a percmutató egy perc alatt 12 egységet (6 fok). A két állás különbségének abszolút értéke adja a szöget. Ha ez 360 egységnél (180 foknál) nagyobb, a kisebb szög a 720 egységből kivonva adódik. A végén visszaosztunk kettővel. Az időigény állandó.
*/
/*
Hint 1: || Az óramutató állása nemcsak az órától, hanem a perctől is függ, mert percenként is halad. A percmutató egy percenként 6 fokot fordul. ||
Hint 2: || Számold ki mindkét mutató állását a 12 órás számlapon, a különbség abszolút értékét vedd. Ha ez 180 foknál nagyobb, a kisebb szöget 360 fokból kapod. Félfokos egységben a számolás egész marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int ora, perc;
    cin >> ora >> perc;

    // Félfokos egységben: az óramutató 60 egység óránként, és 1 egység percenként;
    // a percmutató percenként 12 egység.
    int oraSzog = (ora % 12) * 60 + perc;
    int percSzog = perc * 12;

    int kulonbseg = abs(oraSzog - percSzog);  // 0..660
    if (kulonbseg > 360) kulonbseg = 720 - kulonbseg;  // a kisebbik szög

    cout << kulonbseg / 2 << '\n';
    return 0;
}
