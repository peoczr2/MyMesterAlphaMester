/*
Megoldás lényege:
Félfokban számolunk, így minden állás egész szám lesz. Az óramutató óránként 60 félfokot, percenként 1 félfokot lép, ezért az állása 60 * (ORA % 12) + PERC félfok. A percmutató percenként 12 félfokot halad, ezért az állása 12 * PERC félfok. A két állás különbségének abszolút értéke d, és mivel a számlap kör, a bezárt szög a d és a 720 - d közül a kisebbik, így legfeljebb 180 fok. Ezt végül kettővel osztva kapjuk a fokban mért szöget. Az időigény O(1).
*/
/*
Hint 1: || Az óramutató óránként 30 fokot, percenként 0,5 fokot halad, a percmutató pedig percenként 6 fokot. Ha a legkisebb egység a félfok, minden állás egész szám lesz. ||
Hint 2: || Vedd a két állás különbségének abszolút értékét. Ha ez nagyobb, mint 360 félfok (180 fok), a kisebbik szög a teljes körből (720 félfok) való kivonással adódik. Végül a félfokban kapott értéket oszd kettővel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int ora, perc;
    cin >> ora >> perc;

    int oramutato2 = 60 * (ora % 12) + perc;
    int percmutato2 = 12 * perc;
    int kulonbseg2 = abs(oramutato2 - percmutato2);
    int eredmeny2 = min(kulonbseg2, 720 - kulonbseg2);

    cout << eredmeny2 / 2 << '\n';
    return 0;
}
