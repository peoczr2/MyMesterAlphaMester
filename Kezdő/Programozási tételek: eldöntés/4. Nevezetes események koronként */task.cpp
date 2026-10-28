/*
Megoldás lényege:
Négy logikai jelzőt tartunk nyilván: volt-e ókori, középkori, újkori és modernkori esemény. Minden esemény évszámát egyszer megvizsgáljuk, és a határok alapján (476, 1492, 1642) a megfelelő jelzőt igazra állítjuk: a legfeljebb 476-os évek az ókoriak, a 476-nál későbbi, de legfeljebb 1492-es évek a középkoriak, az 1492-nél későbbi, de legfeljebb 1642-es évek az újkoriak, az 1642-nél későbbiek pedig a modernkoriak. Az eseményleírás szóközt is tartalmazhat, ezért a kategória után a teljes sort beolvassuk, de a kategóriák és az év-intervallum a kérdés szempontjából nem számítanak. Az időigény N-nel arányos.
*/
/*
Hint 1: || Az esemény kategóriája, szövege, az év-intervallum és a kategórianevek nem befolyásolják a kérdést, csak az évszámokra kell figyelni. ||
Hint 2: || Korszakonként tarts nyilván egy logikai változót, és minden eseményre az évszám alapján döntsd el, melyik korszakba esik. Az esemény leírása szóközt is tartalmazhat, ezért a kategória után a teljes sort olvasd be, és ne használd a sima cin >> olvasást rá. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, ksz;
    cin >> n >> ksz;

    bool okori = false, kozepkori = false, ujkori = false, modernkori = false;
    for (int i = 0; i < n; i++) {
        int ev, kat;
        string esemeny;
        cin >> ev >> kat;
        getline(cin >> ws, esemeny);

        if (ev <= 476) {
            okori = true;
        } else if (ev <= 1492) {
            kozepkori = true;
        } else if (ev <= 1642) {
            ujkori = true;
        } else {
            modernkori = true;
        }
    }

    cout << (okori ? "IGEN" : "NEM") << ' '
         << (kozepkori ? "IGEN" : "NEM") << ' '
         << (ujkori ? "IGEN" : "NEM") << ' '
         << (modernkori ? "IGEN" : "NEM") << '\n';
    return 0;
}
