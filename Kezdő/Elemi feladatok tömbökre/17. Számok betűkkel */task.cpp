/*
Megoldás lényege:
A szám 1 és 100 közötti, ezért a szöveges alak néhány szótárból áll össze: az egyesek (1–9), a tízesek (10, 20, …, 90) és a 10–19 közötti szavak, a 100 pedig külön eset („szaz”). A 11–19 közötti számoknál a „tizen” előtag után jön az egyes neve, a 10 pedig „tiz”. A 21–29 közötti számoknál a „husz” helyett „huszon” áll. Az ékezetes karaktereket már a szótárban az ékezet nélküli párjukkal írjuk, így a kimenet csak ASCII karaktereket tartalmaz. A megoldás egyetlen beolvasás és néhány elágazás, ezért konstans időigényű.
*/
/*
Hint 1: || Két esetet különíts el: a 100 fix szó, minden más számot a tízes és az egyes helyiértékéből állíts össze. ||
Hint 2: || Az egyesek nevei (1–9) és a tízesek nevei (10, 20, …, 90) legyenek táblázatban; 11–19 között a „tizen” előtag után az egyes neve áll, 21–29 között pedig „huszon”. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    // Az egyesek neve (ékezet nélkül), a 0 üres
    const string egyes[] = {"", "egy", "ketto", "harom", "negy", "ot", "hat", "het", "nyolc", "kilenc"};
    // A tízesek neve (ékezet nélkül), a 0 üres
    const string tizes[] = {"", "tiz", "husz", "harminc", "negyven", "otven", "hatvan", "hetven", "nyolcvan", "kilencven"};

    string szoveg;
    if (n == 100) {
        szoveg = "szaz";
    } else {
        int t = n / 10;
        int e = n % 10;
        if (t == 1 && e > 0) {
            szoveg = "tizen" + egyes[e];
        } else if (t == 2 && e > 0) {
            szoveg = "huszon" + egyes[e];
        } else {
            szoveg = tizes[t] + egyes[e];
        }
    }

    cout << szoveg << "\n";
    return 0;
}
