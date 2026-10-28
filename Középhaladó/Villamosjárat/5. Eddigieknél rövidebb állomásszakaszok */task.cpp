/*
Megoldás lényege:
Az állomásszakasz hossza a két szomszédos megálló távolsága (Ti), nem az idő. Egy szakasz pontosan akkor kerül a listába, ha rövidebb minden előző szakasznál; az első szakasznak nincs korábbi, ezért ő automatikusan bekerül (a példában a 300-as hossz miatt a kimenet 1 1). Egy bejárásban az eddigi legrövidebb hosszt tároljuk (kezdetben egy nagy érték), és ha az aktuális távolság kisebb, a sorszámát eltesszük és frissítjük a minimumot. Mivel a darabszám kerül a sor elejére, a sorszámokat vektorban gyűjtjük. Időigény O(N).
*/
/*
Hint 1: || Az állomásszakasz hosszát a Ti távolság adja, az idők erre nincsenek hatással. Egy szakasz akkor kerül a listába, ha kisebb minden korábbi szakasz távolságánál. ||
Hint 2: || Tarts nyilván egy változót az eddigi legkisebb távolságról (kezdetben legyen nagyon nagy), és minden sornál nézd meg, kisebb-e nála az aktuális távolság. A kiírás előtt számold meg a kiválasztott sorszámokat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int legrovidebb = INT_MAX;
    vector<int> sorszamok;
    for (int i = 1; i <= n; i++) {
        int tav, erk, ind;
        cin >> tav >> erk >> ind;
        if (tav < legrovidebb) {
            sorszamok.push_back(i);
            legrovidebb = tav;
        }
    }
    cout << sorszamok.size();
    for (int s : sorszamok) {
        cout << ' ' << s;
    }
    cout << '\n';
    return 0;
}
