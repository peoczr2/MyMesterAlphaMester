/*
Megoldás lényege:
Minden észlelés idejét egyetlen egész számra alakítjuk: a percet 60-nal szorozzuk, és hozzáadjuk a másodperceket, így az idő összehasonlítható egy számmal. Ezeket a számokat rendezzük növekvő sorrendbe. Az első részfeladatban a rendezett listát írjuk ki, minden időt visszaalakítva perc és másodperc párra (perc = idő / 60, másodperc = idő % 60). A második részfeladatban az i-edik észlelést akkor követi két újabb észlelés 3 másodpercen belül, ha a rendezett listában az (i+2)-edik elem ideje legfeljebb 3 másodperccel nagyobb az i-edikénél, mert a rendezés miatt az i+1-edik ettől is korábbi vagy egyenlő. Az első ilyen i-t keressük, így a legkorábbi találat sorszáma adódik, különben 0. Az időigény O(N log N), a rendezés miatt.
*/
/*
Hint 1: || Az észleléseket először az idejük szerint kell sorba rendezni, de a percet és a másodpercet egy számként is kezelheted: a percet szorozd 60-nal és add hozzá a másodperceket. ||
Hint 2: || Egy i-edik észlelés után két újabb akkor érkezik 3 másodpercen belül, ha a rendezett listában az (i+2)-edik időpont legfeljebb 3-mal nagyobb az i-edik időpontnál. Ezt csak az i-edik elemtől kezdve kell ellenőrizned, az utolsó két elemet már nem. ||
Hint 3: || A kiírásnál a perc a szám 60-as egész osztása, a másodperc a 60-as maradéka. Az első találatnál megállhatsz, a sorszámozás 1-től indul. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> ido(n);
    for (int i = 0; i < n; i++) {
        int perc, mp;
        cin >> perc >> mp;
        ido[i] = perc * 60 + mp;
    }

    sort(ido.begin(), ido.end());

    // 1. részfeladat: a rendezett észlelések (perc és másodperc)
    cout << "#\n";
    for (int t : ido) {
        cout << t / 60 << " " << t % 60 << "\n";
    }

    // 2. részfeladat: a legkorábbi észlelés sorszáma, amelyet 3 másodpercen belül két újabb követ
    cout << "#\n";
    int eredmeny = 0;
    for (int i = 0; i + 2 < n; i++) {
        if (ido[i + 2] - ido[i] <= 3) {
            eredmeny = i + 1;
            break;
        }
    }
    cout << eredmeny << "\n";

    return 0;
}
