/*
Megoldás lényege:
Az események időpontját percre váltjuk (óra * 60 + perc), és csak azokat dolgozzuk fel, amelyek legkésőbb X:00-kor történtek, mert ezek már befejeződtek. A bent lévő ügyfeleket kártyaszámukkal azonosítjuk, és halmazban tartjuk: belépéskor beírjuk, kilépéskor kivesszük. A pénzfelvételi és pénzbetéti események nem változtatják a bent lévők számát, ezért figyelmen kívül hagyjuk őket. A válasz a halmaz mérete. Az időigény O(N log N), a memóriaigény O(N), ahol N az események száma.
*/
/*
Hint 1: || Az X óra 0 perckor a fiókban lévőket az határozza meg, hogy X:00-ig (ezt is beleértve) mely belépések és kilépések történtek. Az időt érdemes percekben számolni. ||
Hint 2: || Az ügyfelet a kártyaszáma azonosítja: belépéskor vedd fel egy halmazba, kilépéskor töröld belőle. A pénzfelvételi és pénzbetéti (-2, 2 típusú) eseményeket hagyd figyelmen kívül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    int hatar = x * 60;
    set<int> bent;
    for (int i = 0; i < n; i++) {
        int ora, perc, tipus, sz;
        cin >> ora >> perc >> tipus >> sz;
        int ido = ora * 60 + perc;
        if (ido > hatar) continue;
        if (tipus == 1) bent.insert(sz);
        else if (tipus == -1) bent.erase(sz);
    }
    cout << bent.size() << "\n";
    return 0;
}
