/*
Megoldás lényege:
A villamos menetideje az az idő, amikor nem áll, vagyis az egyes szakaszok idejének összege. Egy szakasz az előző megálló indulásától a következő megálló érkezéséig tart, az első szakasz a 0. percben indul a 0. állomásról. Ezért egy bejárásban az érkezési idő és az előző indulási idő különbségét összegezzük, a végállomás indulási ideje nem befolyásolja az eredményt. Időigény O(N).
*/
/*
Hint 1: || A villamos akkor mozog, amikor nem áll egy megállóban. Minden szakasz az előző megálló indulásától a következő megálló érkezéséig tart. ||
Hint 2: || Egy bejárásban tartsd nyilván az előző megálló indulási idejét (kezdetben 0), és minden sornál add hozzá az érkezési idő és ez az előző indulási idő különbségét. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    long long menetido = 0;
    long long elozoIndulas = 0;
    for (int i = 0; i < n; i++) {
        long long tav, erk, ind;
        cin >> tav >> erk >> ind;
        menetido += erk - elozoIndulas;
        elozoIndulas = ind;
    }
    cout << menetido << '\n';
    return 0;
}
