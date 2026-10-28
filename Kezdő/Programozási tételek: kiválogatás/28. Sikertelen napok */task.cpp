/*
Megoldás lényege:
Egyetlen bejárással végigmegyünk a napokon, és minden napnál megnézzük, hány halat fogott az illető.
Ha a fogott halak száma 5-nél kevesebb, a nap sikertelen, ezért a sorszámát egy vektorba tesszük.
Mivel a napokat sorrendben dolgozzuk fel, a vektorban a sorszámok már növekvő sorrendben vannak.
A kiírásnál először a sikertelen napok darabszáma következik, utána a sorszámok, egy-egy szóközzel elválasztva.
Az időigény N-nel arányos, ami legfeljebb 100 lépés, így a korlátok mellett bőven belefér.
*/
/*
Hint 1: || Minden naphoz elég egyetlen dolgot megnézni: hány halat fogott aznap. A döntés után a fogott halak számára már nincs szükség. ||
Hint 2: || Gyűjtsd egy vektorba a sikertelen napok sorszámát, majd kiírásnál előbb a vektor méretét, utána a sorszámokat írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> bad;
    for (int i = 1; i <= n; ++i) {
        int fish;
        cin >> fish;
        if (fish < 5) bad.push_back(i);
    }

    cout << bad.size();
    for (int day : bad) cout << ' ' << day;
    cout << '\n';
    return 0;
}
