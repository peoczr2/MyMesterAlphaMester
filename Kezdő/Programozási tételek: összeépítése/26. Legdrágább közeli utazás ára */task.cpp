/*
Megoldás lényege:
Egyetlen menetben beolvassuk a városokat, és csak az 1000 kilométernél közelebbi (T < 1000) városok jegyárait vesszük figyelembe.
Ezek közül folyamatosan nyilvántartjuk a legnagyobb árat; a „van” jelző mutatja, történt-e egyáltalán találat.
Ha nincs 1000 kilométernél közelebbi város, a kimenet -1.
Az idő O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Először a feltételt nézd: csak az 1000 kilométernél közelebbi városok jegyárai érdekesek, a többi sort csak be kell olvasni. ||
Hint 2: || Tarts nyilván egy legnagyobb árat és egy jelzőt arról, volt-e már találat; a végén, ha nem volt találat, -1-et írj ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    bool van = false;
    long long legdragabb = 0;
    for (int i = 0; i < n; i++) {
        int tavolsag;
        long long ar;
        cin >> tavolsag >> ar;
        if (tavolsag < 1000 && (!van || ar > legdragabb)) {
            van = true;
            legdragabb = ar;
        }
    }
    if (van) {
        cout << legdragabb << "\n";
    } else {
        cout << -1 << "\n";
    }
    return 0;
}
