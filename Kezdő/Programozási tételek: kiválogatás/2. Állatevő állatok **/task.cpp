/*
Megoldás lényege:
Állat az az élőlény, amely valamit eszik, azaz szerepel a párok első szavaként; a többi élőlény növény, mert nem eszik semmit.
Először végigolvassuk a párokat, és egy halmazba gyűjtjük az összes evő élőlényt, vagyis az állatokat.
Másodszor a párokat sorban végigjárjuk: ha az evett élőlény állat, akkor az evő is állatot eszik, ezért a nevét felvesszük a válaszba.
Egy evőt csak egyszer írunk ki, ezért a már kiírt neveket egy másik halmazban nyilvántartjuk.
A válaszok a párok első előfordulásának sorrendjében kerülnek ki, az időigény a párok számával arányos.
*/
/*
Hint 1: || Egy élőlény pontosan akkor állat, ha valamit eszik, vagyis szerepel valamelyik párban az első helyen. Aki csak a második helyen szerepel, az nem eszik, tehát növény. ||
Hint 2: || Először gyűjtsd össze egy halmazba az összes első helyen álló nevet. Ezután a párokat még egyszer végigjárva egy halmazban való kereséssel eldöntheted, hogy az evett élőlény állat-e. ||
Hint 3: || Ha egy pár evője a második élőlényt eszi, és az állat, akkor az evőt be kell venni a válaszba. Ugyanazt az evőt csak egyszer írd ki, és a párok sorrendjét tartsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<string, string>> parok(n);
    set<string> evok;
    for (int i = 0; i < n; ++i) {
        cin >> parok[i].first >> parok[i].second;
        evok.insert(parok[i].first);
    }

    vector<string> ans;
    set<string> mar;
    for (const auto &[evo, evett] : parok) {
        if (evok.count(evett) && !mar.count(evo)) {
            mar.insert(evo);
            ans.push_back(evo);
        }
    }

    cout << ans.size() << '\n';
    for (const string &x : ans) cout << x << '\n';
    return 0;
}
