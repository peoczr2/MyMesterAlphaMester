/*
Megoldás lényege:
A magánhangzók az a, e, i, o, u betűk, a többi betű mássalhangzó.
A szót balról jobbra egyszer végigjárjuk, és egy számlálóval mérjük az egymás után álló mássalhangzókat.
Amikor magánhangzóhoz érünk, a számlálót (ha nem nulla) eltesszük a listába, majd nullázzuk.
A szó végén a maradék mássalhangzó-sorozatot is el kell tenni, mert a szó mássalhangzóval is végződhet.
Az időigény a szó hosszával arányos, ami a legfeljebb 255 karakter miatt bőven belefér.
*/
/*
Hint 1: || Egy mássalhangzó-sorozat a szónak olyan összefüggő része, amelyben csak mássalhangzók állnak egymás mellett. A szó elején és végén lévő sorozatot is ki kell írni. ||
Hint 2: || Balról jobbra haladva egy számlálóval mérheted az aktuális mássalhangzó-sorozat hosszát. Magánhangzónál zárd le a sorozatot, és csak a nem nulla hosszúságúakat írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    vector<int> futam;
    int hossz = 0;
    for (char c : s) {
        c = tolower(static_cast<unsigned char>(c));
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            if (hossz > 0) futam.push_back(hossz);
            hossz = 0;
        } else {
            ++hossz;
        }
    }
    if (hossz > 0) futam.push_back(hossz);

    for (size_t i = 0; i < futam.size(); ++i) {
        if (i) cout << ' ';
        cout << futam[i];
    }
    cout << '\n';
    return 0;
}
