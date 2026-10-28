/*
Megoldás lényege:
A számot négy helyiértékre bontjuk: ezresekre, százasokra, tízesekre és egyesekre, osztással és maradékképzéssel. Az egyjegyű számneveket tömbben tároljuk, és minden nem nulla helyiértékhez a megfelelő szavakat gyűjtjük sorrendben. A szorzó szavak (mil, cent, dek) 1-es számjegy esetén egyedül állnak, egyébként a számjegy neve elé kerülnek, összeragasztva, például tricent. A szavakat szóközzel elválasztva írjuk ki. Mivel a bemenet legfeljebb négyjegyű, a program állandó idejű.
*/
/*
Hint 1: || Bontsd a számot négy részre: ezresekre, százasokra, tízesekre és egyesekre, osztással és maradékképzéssel. Minden nem nulla rész kiírandó szavakat ad. ||
Hint 2: || Az 1-es helyiértéknél csak a szorzó szó (mil, cent, dek) áll, például 1000 esetén „mil”. Más számjegynél a számjegy nevét a szorzó szóval összeragasztva írd ki, például „tricent”. A 10–19 közötti számoknál a tízes szó mindig „dek”, utána jön az egyes. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    string egyjegy[10] = {"", "unu", "du", "tri", "kvar", "kvin", "ses", "sep", "ok", "nau"};

    int ezer = n / 1000;
    int szaz = n / 100 % 10;
    int tiz = n / 10 % 10;
    int egy = n % 10;

    vector<string> szavak;
    if (ezer > 0) szavak.push_back(ezer == 1 ? "mil" : egyjegy[ezer] + "mil");
    if (szaz > 0) szavak.push_back(szaz == 1 ? "cent" : egyjegy[szaz] + "cent");
    if (tiz > 0) szavak.push_back(tiz == 1 ? "dek" : egyjegy[tiz] + "dek");
    if (egy > 0) szavak.push_back(egyjegy[egy]);

    for (size_t i = 0; i < szavak.size(); i++) {
        if (i > 0) cout << ' ';
        cout << szavak[i];
    }
    cout << '\n';
    return 0;
}
